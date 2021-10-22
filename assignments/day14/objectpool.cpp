/* COPYRIGHT
 * 
*/

#include <type_traits>
#include <iostream>
#include <memory>

template<class T, size_t Size>
class ObjectPool final {
 public:
    using value_type = T;
    using pointer = value_type *;

    ObjectPool() {
        for (auto i = 1; i < Size; ++i)
            mPool[i - 1].mNext = &mPool[i];

        mNextFree = &mPool[0];
    }

    ObjectPool(const ObjectPool&) = delete;

    ObjectPool(ObjectPool&& other) noexcept
        : mPool{ std::move(other.mPool) }
        , mNextFree{ other.mNextFree } {
        other.mNextFree = nullptr;
    }

    ~ObjectPool() = default;

    [[nodiscard]] pointer allocate() {
        if (mNextFree == nullptr)
            throw std::bad_alloc{};

        const auto item = mNextFree;
        mNextFree = item->mNext;

        return reinterpret_cast<pointer>(&item->mStorage);
    }

    void deallocate(pointer p) noexcept {
        const auto item = reinterpret_cast<Item*>(p);

        item->mNext = mNextFree;
        mNextFree = item;
    }

    template<class ...Args>
    [[nodiscard]] pointer construct(Args&& ...args) {
        return new (allocate()) value_type(std::forward<Args>(args)...);
    }

    void destroy(pointer p) noexcept {
        if (p == nullptr)
            return;

        p->~value_type();
        deallocate(p);
    }

    ObjectPool& operator =(const ObjectPool&) = delete;

    ObjectPool& operator =(ObjectPool&& other) noexcept {
        if (this == &other)
            return *this;

        mPool = std::move(other.mPool);
        mNextFree = other.mNextFree;

        other.mNextFree = nullptr;

        return *this;
    }

 private:
    union Item {
        std::aligned_storage_t<sizeof(value_type),
            alignof(value_type)> mStorage;
        Item* mNext;
    };

    std::unique_ptr<Item[]> mPool = std::make_unique<Item[]>(Size);
    Item* mNextFree = nullptr;
};

int main() {
    ObjectPool<int, 100> pool;
    for (auto i = 0; i < 100000; ++i)
        pool.destroy(pool.construct());
    return 0;
}