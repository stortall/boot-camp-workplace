#ifndef SHAPES_H
#define SHAPES_H
#include<iostream>
#include<cmath>

class Shape {
    public:
        // Constructors 
        // Note that the constructors are overloaded
        // Shape() = default is almost same as Shape(){}
        Shape() = default;
        // After colon is the initialisation list. Important because
        // const attributes cant be assigned otherwise
        // Shape(const int &_p, const int &_a):Perimiter(_p),Area(_a){}
        Shape(const int &_p, const int &_a);
        // Destructor
        virtual ~Shape() = 0;

        bool operator <(const Shape &s);
        bool operator >(const Shape &s);
        bool operator ==(const Shape &s);
        void print() {
            std::cout << Perimiter << " " << Area << std::endl;
        }
    private:
        int Perimiter = 0;
        int Area = 0;
};

class Circle : public Shape {
    public:
        Circle(const int &radius):Shape((2*radius*3),std::pow(radius,2)){}
        ~Circle() = default;
};

class Rectangle : public Shape {
    public:
        Rectangle(const int &height,const int &width):Shape((2*height)+(2*width),(height*width)){}
        ~Rectangle() = default;
};

class Triangle : public Shape {
    public:
        Triangle(const int &width,const int &height):Shape(3*width,height*width/2){}
        ~Triangle() = default;
};

#endif // SHAPES_H