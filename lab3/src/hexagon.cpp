#include "hexagon.h"

Hexagon::Hexagon()
{
    // Default: a compact, regular-like hexagon (integer approximation)
    v.push(Point(0, 1));
    v.push(Point(1, 0));
    v.push(Point(2, 0));
    v.push(Point(3, 1));
    v.push(Point(2, 2));
    v.push(Point(1, 2));
}

Hexagon::Hexagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6)
{
    v.push(p1);
    v.push(p2);
    v.push(p3);
    v.push(p4);
    v.push(p5);
    v.push(p6);
}

long double Hexagon::Area() const
{
    return CalcArea(v);
}

Point Hexagon::Center() const
{
    return CalcCenter(v);
}

Hexagon::~Hexagon() {}
