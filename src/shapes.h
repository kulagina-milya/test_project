#pragma once
#include <cstdint>

namespace shapes {

class Shape {
public:
    virtual void printArea() = 0;

    virtual double getArea() = 0;

    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    Circle(int radius);

    void printArea() override;

    double getArea() override;

    uint32_t getRadius() const;

private:
    uint32_t radius_;
};

class Square : public Shape {
public:
    Square(int a);

    void printArea() override;

    double getArea() override;

    uint32_t getSide() const;

private:
    uint32_t a_;
};

} // namespace shapes

