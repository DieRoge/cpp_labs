#include "trapezium.hpp"

template<class T>
Trapezium<T>::Trapezium() : Figure<T>(4) {}

template<class T>
Trapezium<T>::Trapezium(const std::initializer_list<Point<T>>& vertices)
    : Figure<T>(Array<Point<T>>(vertices)) {}

template<class T>
size_t Trapezium<T>::VerticesCount() const {
    return vertices_count;
}