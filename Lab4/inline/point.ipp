#include "point.hpp"

template<scalar T>
Point<T>::Point(): x(0), y(0) {}

template<scalar T>
Point<T>::Point(T other_x, T other_y)
    : x(other_x)
    , y(other_y)
    {}

template<scalar T>
Point<T>::Point(const Point<T>& other)
    : x(other.x)
    , y(other.y)
    {}

template<scalar T>
Point<T>::Point(Point<T>&& other)
    : x(other.x)
    , y(other.y)
    {}

template<scalar T>
Point<T>& Point<T>::operator=(const Point<T>& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template<scalar T>
bool operator==(const Point<T>& point_one, const Point<T>& point_two) {
    return (point_one.x == point_two.x) && (point_one.y == point_two.y);
}

template<scalar T>
bool operator!=(const Point<T>& point_one, const Point<T>& point_two) {
    return !(point_one == point_two);
}

template<scalar T>
std::istream& operator>>(std::istream& input, Point<T>& point) {
    input >> point.x >> point.y;
    return input;
}

template<scalar T>
std::ostream& operator<<(std::ostream& output, const Point<T>& point) {
    output << "(" << point.x << "; " << point.y << ")";
    return output;
}