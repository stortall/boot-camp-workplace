#include "shape.h"

Shape::Shape(const int &_p, const int &_a) {
    this->Perimiter = _p;
    this->Area = _a;
}

bool Shape::operator <(const Shape &s) {
    bool returnVal = false;
    if ( (this->Area < s.Area) ||
         ( (this->Area == s.Area) && (this->Perimiter < s.Perimiter) ) )
        returnVal = true;    
    return returnVal;
}

bool Shape::operator >(const Shape &s) {
    bool returnVal = false;
    if ( (this->Area > s.Area) ||
         ( (this->Area == s.Area) && (this->Perimiter > s.Perimiter) ) )
        returnVal = true;    
    return returnVal;
}

bool Shape::operator ==(const Shape &s) {
    bool returnVal = false;
    if ( (this->Area == s.Area) && (this->Perimiter == s.Perimiter) ) 
        returnVal = true;    
    return returnVal;
}
Shape::~Shape(){} 