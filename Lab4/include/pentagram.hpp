#pragma once

#include <iostream>

#include "figure.hpp"


template<class T>
class Pentagram : public Figure<T> {
    public:
    Pentagram();
    Pentagram(const std::initializer_list<Point<T>>& vertices);
    ~Pentagram() = default;

    size_t VerticesCount() const override;

    private:
    const size_t vertices_count = 5;
};

#include "pentagram.ipp"
