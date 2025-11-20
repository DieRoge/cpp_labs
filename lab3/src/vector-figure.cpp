#include "vector-figure.h"

#include <algorithm>

#include "figure.h"

VectorFigure::VectorFigure() : size(0), capacity(1), v(new Figure*[capacity]) {}

VectorFigure::VectorFigure(const VectorFigure& other)
    : size(other.size), capacity(other.capacity), v(new Figure*[capacity])
{
    std::copy(other.v, other.v + size, v);
}

VectorFigure::VectorFigure(VectorFigure&& other) noexcept
    : size(other.size), capacity(other.capacity), v(other.v)
{
    other.clear();
}

VectorFigure::~VectorFigure()
{
    for (size_t i = 0; i < size; ++i)
    {
        delete v[i];
    }
    delete[] v;
}

void VectorFigure::resize(size_t newsize)
{
    capacity = newsize;
    Figure** t = new Figure*[capacity];
    std::copy(v, v + size, t);
    delete[] v;
    v = t;
}

void VectorFigure::erase(size_t index)
{
    if (index >= size) return;

    delete v[index];

    for (size_t i = index; i < size - 1; ++i)
    {
        v[i] = v[i + 1];
    }
    --size;
}

void VectorFigure::push(Figure* c)
{
    if (size >= capacity)
    {
        resize(2 * capacity);
    }
    v[size++] = c;
}

void VectorFigure::pop()
{
    if (size)
    {
        delete v[--size];
    }
}

Figure* VectorFigure::operator[](size_t i) { 
    return v[i]; 
}

size_t VectorFigure::len()
{
    return size;
}

void VectorFigure::clear()
{
    for (size_t i = 0; i < size; ++i)
    {
        delete v[i];
    }
    size = 0;
    capacity = 1;
    delete[] v;
    v = new Figure*[capacity];
}

double VectorFigure::TotalArea()
{
    double total = 0.0;
    for (size_t i = 0; i < size; ++i)
    {
        total += static_cast<double>(*v[i]);
    }
    return total;
}