#pragma once

#include "figure.h"

class Hexagon : public Figure
{
public:
    Hexagon();
    ~Hexagon() override;
    Hexagon(Point, Point, Point, Point, Point, Point);
    long double Area() const override;
    Point Center() const override;
};