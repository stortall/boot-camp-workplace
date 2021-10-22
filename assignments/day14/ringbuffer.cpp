/* COPYRIGHT
 * 
*/

#include <iostream>
#include <array>

template <typename T, size_t SIZE>
class RingBuffer {
 private:
    std::array<T, SIZE> buffer;
    size_t read_index = 0;
    size_t write_index = 0;
    bool is_full = false;

 public:
    T read() {
        if (isEmpty() == true) {
            return T();
        }
        T itm = buffer[read_index];
        read_index = (read_index + 1) % SIZE;
        is_full = false;
        return itm;
    }
    void write(T itm) {
        buffer[write_index] = itm;
        write_index = (write_index + 1) % SIZE;
        // if buffer is full, oldest is overwritten
        if (is_full) {
            read_index = (read_index + 1) % SIZE;
        }
        is_full = write_index == read_index;
    }
    bool isFull() const {
        return is_full;
    }
    bool isEmpty() const {
        return (is_full == false && read_index == write_index);
    }
    size_t capacity() const {
        return SIZE;
    }
    size_t size() const {
        if (is_full) {
            return SIZE;
        }
        int diff = write_index - read_index;
        return write_index >= read_index?diff:SIZE+diff;
    }
};


int main(void) {
    RingBuffer<int, 4> rb;
    rb.write(2);
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';
    rb.write(3);
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';
    rb.write(4);
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';
    rb.write(5);
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';
    rb.write(6);
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';

    std::cout << rb.read() << ' ';
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';

    std::cout << rb.read() << ' ';
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';

    std::cout << rb.read() << ' ';
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';

    std::cout << rb.read() << ' ';
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';

    std::cout << rb.read() << ' ';
    std::cout << rb.size() << ' ';
    std::cout << rb.capacity() << ' ';
    std::cout << rb.isFull() << ' ';
    std::cout << rb.isEmpty() << '\n';
    return 0;
}