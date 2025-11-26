#pragma once

#include <iostream>

#include "point.hpp"
#include "array.hpp"

template<class T>
class Figure {
    public:
    Figure();
    Figure(const Array<Point<T>>& points);
    Figure(size_t vertices_count);
    Figure(const Figure<T>& other);
    Figure(Figure<T>&& other) noexcept;
    Figure& operator=(const Figure<T>& other);
    ~Figure() = default;
    
    long double getArea() const;
    Point<T> getCenter() const;

    void readVertices(std::istream& input);
    void printVertices(std::ostream& output) const;
    virtual size_t VerticesCount() const = 0;

    friend bool operator==<T>(const Figure<T>& figure_one, const Figure<T>& figure_two);
    friend bool operator!=<T>(const Figure<T>& figure_one, const Figure<T>& figure_two);

    protected:
    Array<Point<T>> vertices;
    long double findArea() const;
    Point<T> findCenter() const;
};

template<class T>
bool operator==(const Figure<T>& figure_one, const Figure<T>& figure_two);

template<class T>
bool operator!=(const Figure<T>& figure_one, const Figure<T>& figure_two);

template<class T>
std::istream& operator>>(std::istream& input, Figure<T>& figure);

template<class T>
std::ostream& operator<<(std::ostream& output, const Figure<T>& figure);

#include "figure.ipp"