#include "shapes.h"

#include <iostream>
#include <cmath>

namespace {
const double PI = 3.141592653589793;
}

namespace shapes {

Circle::Circle(int radius)
    : radius_(radius) {}

void Circle::printArea() {
    std::cout << "Area of the circle = " << getArea() << std::endl;
}

double Circle::getArea() {
    return PI * pow(radius_, 2);
}

uint32_t Circle::getRadius() const {
    return radius_;
}


Square::Square(int a)
    : a_(a) {
}

void Square::printArea() {
    std::cout << "Area of the square = " << getArea() << std::endl;
}

double Square::getArea() {
    return pow(a_, 2);
}

uint32_t Square::getSide() const {
    return a_;
}

} // namespace shapes
