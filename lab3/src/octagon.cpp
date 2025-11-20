#include "octagon.h"

Octagon::Octagon()
{
    // Default compact octagon (integer approximation)
    v.push(Point(0, 1));
    v.push(Point(1, 0));
    v.push(Point(3, 0));
    v.push(Point(4, 1));
    v.push(Point(4, 2));
    v.push(Point(3, 3));
    v.push(Point(1, 3));
    v.push(Point(0, 2));
}

Octagon::Octagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8)
{
    v.push(p1);
    v.push(p2);
    v.push(p3);
    v.push(p4);
    v.push(p5);
    v.push(p6);
    v.push(p7);
    v.push(p8);
}

long double Octagon::Area() const
{
    return CalcArea(v);
}

Point Octagon::Center() const
{
    return CalcCenter(v);
}

Octagon::~Octagon() {}
