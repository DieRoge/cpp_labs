#include "figure.hpp"

template<class T>
Figure<T>::Figure() : vertices() {}

template<class T>
Figure<T>::Figure(const Array<Point<T>>& points) : vertices(points) {}

template<class T>
Figure<T>::Figure(const Figure<T>& other) : vertices(other.vertices) {}

template<class T>
Figure<T>::Figure(size_t vertices_count) {
    for (size_t i = 0; i < vertices_count; ++i) {
        vertices.push(Point<T>{});
    }
}

template<class T>
Figure<T>::Figure(Figure<T>&& other) noexcept : vertices(std::move(other.vertices)) {}

template<class T>
Figure<T>& Figure<T>::operator=(const Figure<T>& other) {
    if (this != &other) {
        vertices = other.vertices;
    }
    return *this;
}

template<class T>
long double Figure<T>::getArea() const {
    return findArea();
}

template<class T>
Point<T> Figure<T>::getCenter() const {
    return findCenter();
}

template<class T>
void Figure<T>::readVertices(std::istream& input) {
    for (size_t i = 0; i < VerticesCount(); ++i) {
        input >> vertices[i];
    }
}

template<class T>
void Figure<T>::printVertices(std::ostream& output) const {
    for (size_t i = 0; i < VerticesCount(); ++i) {
        output << vertices[i] << " ";
    }
    output << "\n";
}

template<class T>
long double Figure<T>::findArea() const {
    long double area = 0.0;
    size_t n = VerticesCount();
    for (size_t i = 0; i < n; ++i) {
        const Point<T>& p1 = vertices[i];
        const Point<T>& p2 = vertices[(i + 1) % n];
        area += static_cast<long double>(p1.x) * static_cast<long double>(p2.y);
        area -= static_cast<long double>(p2.x) * static_cast<long double>(p1.y);
    }
    return std::abs(area) / 2.0;
}

template<class T>
Point<T> Figure<T>::findCenter() const {
    long double sum_x = 0.0;
    long double sum_y = 0.0;
    size_t n = VerticesCount();
    for (size_t i = 0; i < n; ++i) {
        sum_x += static_cast<long double>(vertices[i].x);
        sum_y += static_cast<long double>(vertices[i].y);
    }
    return Point<T>(static_cast<T>(sum_x / n), static_cast<T>(sum_y / n));
}

template<class T>
bool operator==(const Figure<T>& figure_one, const Figure<T>& figure_two) {
    if (figure_one.VerticesCount() != figure_two.VerticesCount()) {
        return false;
    }
    for (size_t i = 0; i < figure_one.VerticesCount(); ++i) {
        if (figure_one.vertices[i] != figure_two.vertices[i]) {
            return false;
        }
    }
    return true;
}

template<class T>
bool operator!=(const Figure<T>& figure_one, const Figure<T>& figure_two) {
    return !(figure_one == figure_two);
}

template<class T>
std::istream& operator>>(std::istream& input, Figure<T>& figure) {
    figure.readVertices(input);
    return input;
}

template<class T>
std::ostream& operator<<(std::ostream& output, const Figure<T>& figure) {
    figure.printVertices(output);
    return output;
}