#pragma once

#include "figure.h"

class Triangle : public Figure
{
public:
    Triangle();
    ~Triangle() override;
    Triangle(Point, Point, Point);
    long double Area() const override;
    Point Center() const override;
};