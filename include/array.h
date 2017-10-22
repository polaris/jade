#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <stdexcept>

namespace jade {

template <typename T, std::size_t N>
class array {
public:
    typedef T value_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;

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

    constexpr std::size_t size() const { return N; }
    constexpr bool empty() const noexcept { return begin() == end(); }

    constexpr iterator begin() noexcept { return data_; }
    constexpr const_iterator begin() const noexcept { return data_; }

    constexpr iterator end() noexcept { return data_ + N; }
    constexpr const_iterator end() const noexcept { return data_ + N; }

private:
    T data_[N];
};

}  // namespace jade

#endif  // ARRAY_H
