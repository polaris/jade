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

    explicit vector(size_type count, const T& value = T()) : vector() {
        resize(count);
        for (size_type i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    vector(std::initializer_list<T> c) : vector() {
        resize(c.size());
        std::copy(c.begin(), c.end(), data_);
        size_ = c.size();
    }

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

    void resize(std::size_t count) {
        pointer data = nullptr;
        if (count > 0) {
            data = new value_type[count];
            memcpy(data, data_, size_ * sizeof(value_type));
        }
        size_ = std::min(size_, count);
        capacity_ = count;
        delete[] data_;
        data_ = data;
    }

    void push_back(const_reference value) {
        if (size_ == capacity_) {
            if (capacity_ != 0) {
                const size_type new_size = 2 * capacity_;
                resize(new_size);
            } else {
                capacity_ = 1;
                data_ = new value_type[capacity_];
            }
        }
        data_[size_++] = value;
    }

    reference operator[](size_type pos) { return data_[pos]; }

    constexpr const_reference operator[](size_type pos) const { return data_[pos]; }

    reference at(size_type pos) {
        if (!(pos < size())) {
            throw std::out_of_range("postion out of range");
        }
        return data_[pos];
    }

    constexpr const_reference at(size_type pos) const {
        if (!(pos < size())) {
            throw std::out_of_range("position out of range");
        }
        return data_[pos];
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
