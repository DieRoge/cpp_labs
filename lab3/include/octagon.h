#pragma once

#include "figure.h"

class Octagon : public Figure
{
public:
    Octagon();
    ~Octagon() override;
    Octagon(Point, Point, Point, Point, Point, Point, Point, Point);
    long double Area() const override;
    Point Center() const override;
};