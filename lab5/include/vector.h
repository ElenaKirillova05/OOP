#pragma once
#include <memory_resource>
#include <iterator>
#include <stdexcept>

// Итератор для Vector
template<typename T>
class VectorIterator {
private:
    T* ptr;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    explicit VectorIterator(T* ptr) : ptr(ptr) {}

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }

    VectorIterator& operator++() {
        ++ptr;
        return *this;
    }

    VectorIterator operator++(int) {
        VectorIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    bool operator==(const VectorIterator& other) const { return ptr == other.ptr; }
    bool operator!=(const VectorIterator& other) const { return !(*this == other); }
};

// Вектор
template<typename T>
class Vector {
private:
    T* data;
    std::size_t size_;
    std::size_t capacity_;
    std::pmr::polymorphic_allocator<T> allocator;

    void grow() {
        std::size_t new_capacity = capacity_ * 2;
        T* new_data = allocator.allocate(new_capacity);

        for (std::size_t i = 0; i < size_; ++i) {
            allocator.construct(&new_data[i], std::move(data[i]));
            allocator.destroy(&data[i]);
        }
        allocator.deallocate(data, capacity_);
        data = new_data;
        capacity_ = new_capacity;
    }

public:
    using iterator = VectorIterator<T>;

    explicit Vector(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : data(nullptr), size_(0), capacity_(1), allocator(resource) {
        data = allocator.allocate(capacity_);
    }

    ~Vector() {
        clear();
        allocator.deallocate(data, capacity_);
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            grow();
        }
        allocator.construct(&data[size_], value);
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            grow();
        }
        allocator.construct(&data[size_], std::move(value));
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        allocator.destroy(&data[--size_]);
    }

    void clear() {
        for (std::size_t i = 0; i < size_; ++i) {
            allocator.destroy(&data[i]);
        }
        size_ = 0;
    }

    T& operator[](std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    std::size_t size() const { return size_; }

    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data + size_); }
};