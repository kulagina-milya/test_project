#include "shapes_factory.h"

namespace shapes_factory {

void createShapesAndPrintArea(Factory* f, uint32_t value) {
    Shape* shape = f->create(value);
    shape->printArea();
    delete shape;
}

Shape* CircleFactory::create(uint32_t radius) {
    return new Circle(radius);
}

Shape* SquareFactory::create(uint32_t a) {
    return new Square(a);
}

} // namespace shapes_factory

