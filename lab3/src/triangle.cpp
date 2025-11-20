#include "triangle.h"

Triangle::Triangle()
{
    v.push(Point(0, 0));
    v.push(Point(1, 0));
    v.push(Point(0, 1));
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    v.push(p1);
    v.push(p2);
    v.push(p3);
}

long double Triangle::Area() const
{
    return CalcArea(v);
}

Point Triangle::Center() const
{
    return CalcCenter(v);
}

Triangle::~Triangle() {}