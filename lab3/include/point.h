#pragma once

#include <iostream>

struct Point
{
    int x, y;
    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend std::istream& operator>>(std::istream&, Point&);
    Point();
    Point(int, int);
    friend bool operator==(Point, Point);
    friend bool operator!=(Point, Point);
};