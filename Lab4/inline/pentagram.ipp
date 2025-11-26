#include "pentagram.hpp"

template<class T>
Pentagram<T>::Pentagram() : Figure<T>(5) {}

template<class T>
Pentagram<T>::Pentagram(const std::initializer_list<Point<T>>& vertices)
    : Figure<T>(Array<Point<T>>(vertices)) {}

template<class T>
size_t Pentagram<T>::VerticesCount() const {
    return vertices_count;
}


