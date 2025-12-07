template<class T>
Array<T>::Array()
    : data(std::shared_ptr<T[]>(new T[1]))
    , size(0)
    , capacity(1)
    {}

template<class T>
Array<T>::Array(size_t init_size)
    : data(std::shared_ptr<T[]>(new T[init_size * 2]))
    , size(init_size)
    , capacity(init_size * 2)
    {}

template<class T>
Array<T>::Array(const std::initializer_list<T>& init_list)
    : data(std::shared_ptr<T[]>(new T[init_list.size() * 2]))
    , size(0)
    , capacity(init_list.size() * 2)
{
    size_t index = 0;
    for (const T& item : init_list) {
        push(item);
    }
}

template<class T>
Array<T>::Array(const Array<T>& other)
    : data(std::shared_ptr<T[]>(new T[other.capacity]))
    , size(other.size)
    , capacity(other.capacity)
{
    std::copy(other.data.get(), other.data.get() + other.size, data.get());
}

template<class T>
Array<T>::Array(Array<T>&& other) noexcept
    : data(std::move(other.data))
    , size(other.size)
    , capacity(other.capacity)
{
    other.data = nullptr;
    other.size = 0;
    other.capacity = 0;
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        data = std::shared_ptr<T[]>(new T[other.capacity]);
        size = other.size;
        capacity = other.capacity;
        std::copy(other.data.get(), other.data.get() + other.size, data.get());
    }
    return *this;
}

template<class T>
void Array<T>::pop() {
    if (size == 0) {
        throw std::out_of_range("Array is empty");
    }
    --size;
}

template<class T>
void Array<T>::push(const T& value) {
    if (size >= capacity) {
        reallocate(capacity * 2);
    }
    data[size] = value;
    size++;
}

template<class T>
void Array<T>::insertAt(size_t index, const T& value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    if (size >= capacity) {
        reallocate(capacity * 2);
    }
    for (size_t i = index; i < size; ++i) {
        data[i + 1] = data[i];
    }
    data[index] = value;
    size++;
}

template<class T>
void Array<T>::removeAt(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

template<class T>
size_t Array<T>::getSize() const {
    return size;
}

template<class T>
size_t Array<T>::getCapacity() const {
    return capacity;
}

template<class T>
T& Array<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<class T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<class T>
void Array<T>::resize(size_t new_size) {
    if (new_size > capacity) {
        reallocate(new_size * 2);
    }
    size = new_size;
}

template<class T>
void Array<T>::reallocate(size_t new_capacity) {
    std::shared_ptr<T[]> new_data(new T[new_capacity]);
    size_t elements_to_copy = (size < new_capacity) ? size : new_capacity;
    std::copy(data.get(), data.get() + elements_to_copy, new_data.get());
    data = new_data;
    capacity = new_capacity;
    if (size > capacity) {
        size = capacity;
    }
}