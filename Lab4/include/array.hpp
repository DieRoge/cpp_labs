#pragma once

#include <iostream>
#include <memory>

template <class T>
class Array {
public:
    Array();
    Array(size_t init_size);
    Array(const std::initializer_list<T> &init_list);
    Array(const Array<T> &other);
    Array(Array<T> &&other) noexcept;
    Array &operator=(const Array<T> &other);
    ~Array() = default;

    void pop();
    void push(const T &value);
    void insertAt(size_t index, const T &value);
    void removeAt(size_t index);
    size_t getSize() const;
    size_t getCapacity() const;
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    void resize(size_t new_size);
    void reallocate(size_t new_capacity);

private:
    std::shared_ptr<T[]> data;
    size_t size;
    size_t capacity;
};

#include "array.ipp"