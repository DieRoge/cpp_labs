#include <new>
#include <utility>

template <typename T>
Queue<T>::Queue(std::size_t capacity, std::pmr::memory_resource* mr)
    : alloc_(mr)
    , data_(nullptr)
    , head_(0)
    , tail_(0)
    , size_(0)
    , capacity_(capacity)
{
    if (capacity_ == 0) {
        throw std::invalid_argument("Queue capacity must be > 0");
    }
    data_ = static_cast<T**>(std::malloc(sizeof(T*) * capacity_));
    if (!data_) {
        throw std::bad_alloc();
    }
    for (std::size_t i = 0; i < capacity_; ++i) {
        data_[i] = nullptr;
    }
}

template <typename T>
Queue<T>::~Queue() noexcept {
    clear();
    if (data_) {
        std::free(data_);
        data_ = nullptr;
    }
}

template <typename T>
template <typename... Args>
void Queue<T>::push(Args&&... args) {
    if (size_ >= capacity_) {
        throw std::runtime_error("Queue capacity exceeded");
    }

    T* element = alloc_.allocate(1);
    try {
        ::new (static_cast<void*>(element)) T(std::forward<Args>(args)...);
    } catch (...) {
        alloc_.deallocate(element, 1);
        throw;
    }

    data_[tail_] = element;
    tail_ = (tail_ + 1) % capacity_;
    ++size_;
}

template <typename T>
void Queue<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Queue is empty");
    }

    T* elem = data_[head_];
    elem->~T();
    alloc_.deallocate(elem, 1);
    data_[head_] = nullptr;

    head_ = (head_ + 1) % capacity_;
    --size_;
}

template <typename T>
T& Queue<T>::front() {
    if (empty()) throw std::runtime_error("Queue is empty");
    return *data_[head_];
}

template <typename T>
const T& Queue<T>::front() const {
    if (empty()) throw std::runtime_error("Queue is empty");
    return *data_[head_];
}

template <typename T>
bool Queue<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
std::size_t Queue<T>::size() const noexcept {
    return size_;
}

template <typename T>
std::size_t Queue<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
void Queue<T>::clear() noexcept {
    while (!empty()) {
        T* elem = data_[head_];
        if (elem) {
            elem->~T();
            try {
                alloc_.deallocate(elem, 1);
            } catch (...) {
            }
            data_[head_] = nullptr;
        }
        head_ = (head_ + 1) % capacity_;
        --size_;
    }
    head_ = tail_ = 0;
}

template <typename T>
Queue<T>::iterator::iterator() noexcept
    : q_(nullptr), pos_(0), iterated_(0) {}

template <typename T>
Queue<T>::iterator::iterator(const Queue<T>* q, std::size_t pos, std::size_t iterated) noexcept
    : q_(q), pos_(pos), iterated_(iterated) {}

template <typename T>
typename Queue<T>::iterator::reference Queue<T>::iterator::operator*() const {
    return *q_->data_[pos_];
}

template <typename T>
typename Queue<T>::iterator::pointer Queue<T>::iterator::operator->() const {
    return q_->data_[pos_];
}

template <typename T>
typename Queue<T>::iterator& Queue<T>::iterator::operator++() {
    if (q_ == nullptr) return *this;
    pos_ = (pos_ + 1) % q_->capacity_;
    ++iterated_;
    return *this;
}

template <typename T>
typename Queue<T>::iterator Queue<T>::iterator::operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
bool Queue<T>::iterator::operator==(const iterator& other) const noexcept {
    return q_ == other.q_ && iterated_ == other.iterated_;
}

template <typename T>
bool Queue<T>::iterator::operator!=(const iterator& other) const noexcept {
    return !(*this == other);
}

template <typename T>
typename Queue<T>::iterator Queue<T>::begin() const noexcept {
    return iterator(this, head_, 0);
}

template <typename T>
typename Queue<T>::iterator Queue<T>::end() const noexcept {
    return iterator(this, tail_, size_);
}
