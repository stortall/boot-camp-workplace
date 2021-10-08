#include<math.h>

class Shape {
    protected:
        int width;
    public:
        Shape(int _width) {
            width = _width;
        }
        virtual int area() = 0;
};

class Circle: public Shape {
    public:
        int area() {
            return pow(width / 2, 2);
        }
};

class Triangle: public Shape {
    protected:
        int height;
    public:
        int area() {
            return width * height / 2;
        }
};

class Rectangle: public Shape {
    protected:
        int height;
    public:
        int area() {
            return width * height;
        }
};

class Square: public Rectangle {
    public:

};

main() {
    Circle c;
    

}