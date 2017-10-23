#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

namespace jade {

template <typename T>
class vector {
public:
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef std::size_t size_type;

    vector() : data_(nullptr), capacity_(0), size_(0) {}
    vector(const vector& other) : data_(nullptr), capacity_(other.capacity_), size_(other.size_) {
        data_ = new value_type[capacity_];
        memcpy(data_, other.data_, size_ * sizeof(value_type));
    }
    virtual ~vector() {
        if (data_) {
            assert(capacity_ > 0);
            delete[] data_;
        }
    }

    vector& operator=(vector other) {
        other.swap(*this);
        return *this;
    }

    void swap(vector& other) {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }

    constexpr size_type size() const { return size_; }
    constexpr size_type capacity() const { return capacity_; }

    void push_back(const_reference value) {
        if (size_ == capacity_) {
            if (capacity_ != 0) {
                const size_type new_size = 2 * capacity_;
                pointer data = new value_type[new_size];
                memcpy(data, data_, size_ * sizeof(value_type));
                delete[] data_;
                data_ = data;
                capacity_ = new_size;
            } else {
                capacity_ = 1;
                data_ = new value_type[capacity_];
            }
        }
        data_[size_++] = value;
    }

    constexpr iterator begin() noexcept { return data_; }
    constexpr const_iterator begin() const noexcept { return data_; }

    constexpr iterator end() noexcept { return data_ + size_; }
    constexpr const_iterator end() const noexcept { return data_ + size_; }

private:
    pointer data_;
    size_type capacity_;
    size_type size_;
};

}  // namespace jade

#endif  // VECTOR_H
