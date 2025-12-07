#include "rhombus.hpp"

template<class T>
Rhombus<T>::Rhombus() : Figure<T>(4) {}

template<class T>
Rhombus<T>::Rhombus(const std::initializer_list<Point<T>>& vertices)
    : Figure<T>(Array<Point<T>>(vertices)) {}

template<class T>
size_t Rhombus<T>::VerticesCount() const {
    return vertices_count;
}