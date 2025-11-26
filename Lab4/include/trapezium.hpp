#pragma once

#include <iostream>

#include "figure.hpp"


template<class T>
class Trapezium : public Figure<T> {
    public:
    Trapezium();
    Trapezium(const std::initializer_list<Point<T>>& vertices);
    ~Trapezium() = default;

    size_t VerticesCount() const override;

    private:
    const size_t vertices_count = 4;
};

#include "trapezium.ipp"