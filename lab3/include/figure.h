#pragma once

#include <iostream>

#include "vector-points.h"

class Figure
{
public:
    virtual ~Figure();
    void ReadPoints(std::istream& is);
    void PrintPoints(std::ostream& os) const;
    virtual long double Area() const = 0;
    virtual Point Center() const = 0;
    friend bool operator==(const Figure&, const Figure&);
    friend bool operator!=(const Figure&, const Figure&);

    virtual explicit operator double() const;

protected:
    Figure();
    VectorPoints v;
    long double CalcArea(const VectorPoints&) const;
    Point CalcCenter(const VectorPoints&) const;
};

std::istream& operator>>(std::istream&, Figure&);
std::ostream& operator<<(std::ostream&, const Figure&);