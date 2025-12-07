#pragma once

#include <iostream>
#include <concepts>
#include <type_traits>


template<typename T>
concept scalar = std::is_arithmetic_v<T>;

template<scalar T>
class Point{
    public:
    T x, y;

    Point();
    Point(T other_x, T other_y);
    Point(const Point<T>&);
    Point(Point<T>&& other);
    Point& operator=(const Point<T>&);
    ~Point() = default;
};

template<scalar T>
bool operator==(const Point<T>& point_one, const Point<T>& point_two);

template<scalar T>
bool operator!=(const Point<T>& point_one, const Point<T>& point_two);

template<scalar T>
std::istream& operator>>(std::istream& input, Point<T>& point);

template<scalar T>
std::ostream& operator<<(std::ostream& output, const Point<T>& point);

#include "point.ipp"