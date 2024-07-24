#pragma once

#include "shapes.h"

namespace shapes_factory {

using shapes::Shape;
using shapes::Circle;
using shapes::Square;

class Factory {
public:
    virtual Shape* create(uint32_t) = 0;
    virtual ~Factory() = default;
};

class CircleFactory : public Factory {
public:
    Shape* create(uint32_t radius) override;
};

class SquareFactory : public Factory {
public:
    Shape* create(uint32_t a) override;
};

void createShapesAndPrintArea(Factory* f, uint32_t value);

} // namespace shapes_factory
