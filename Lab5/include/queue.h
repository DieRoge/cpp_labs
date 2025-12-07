#pragma once

#include <memory_resource>
#include <cstddef>
#include <stdexcept>
#include <cstdlib>
#include <utility>
#include <iterator>

template <typename T>
class Queue {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    using value_type = T;

    explicit Queue(std::size_t capacity, std::pmr::memory_resource* mr = std::pmr::get_default_resource());
    ~Queue() noexcept;

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    template <typename... Args>
    void push(Args&&... args);

    void pop();
    T& front();
    const T& front() const;

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    void clear() noexcept;

    struct iterator {
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() noexcept;
        iterator(const Queue<T>* q, std::size_t pos, std::size_t iterated) noexcept;

        reference operator*() const;
        pointer operator->() const;
        iterator& operator++();    
        iterator operator++(int);  
        bool operator==(const iterator& other) const noexcept;
        bool operator!=(const iterator& other) const noexcept;

    private:
        const Queue<T>* q_;
        std::size_t pos_;       
        std::size_t iterated_;  
    };

    iterator begin() const noexcept;
    iterator end() const noexcept;

private:
    allocator_type alloc_;
    T** data_;
    std::size_t head_;     
    std::size_t tail_;     
    std::size_t size_;
    std::size_t capacity_;
};
#include "queue.ipp"