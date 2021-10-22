#include "../day5/shape.h"

template <typename T1> //Add typename T2 if you want to compare different types
void isBigger(T1 a, T1 b) {
    if (a == b) {
        std::cout << "a is equal to b" << std::endl;
    } 
    if (a > b) {
        std::cout << "a is bigger than b" << std::endl;
    }
    if (a < b) {
        std::cout << "b is bigger than a" << std::endl;
    }
}

int main() {
    // sum<Shape>(A(2,3),A(1,4));
    Circle c1 = Circle(1);
    Triangle t1 = Triangle(3,3);
    Shape *s1 = &c1;
    Shape *s2 = &t1;

    isBigger(s1,s2);

    // delete c1, c2;
    return 0;
}