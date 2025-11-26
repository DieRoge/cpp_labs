#pragma once

#include <iostream>

#include "figure.hpp"


template<class T>
class Rhombus : public Figure<T> {
    public:
    Rhombus();
    Rhombus(const std::initializer_list<Point<T>>& vertices);
    ~Rhombus() = default;

    size_t VerticesCount() const override;

    private:
    const size_t vertices_count = 4;
};

#include "rhombus.ipp"