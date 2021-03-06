#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include <iterator>
#include <memory>
#include <functional>

namespace jade {

template <typename T>
class vector {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef std::size_t size_type;
    typedef std::size_t difference_type;

    class iterator {
    public:
        iterator() : pos_(0) {}
        explicit iterator(std::reference_wrapper<vector> data) : data_(data), pos_(0) {}
        iterator(std::reference_wrapper<vector> data, size_type pos) : data_(data), pos_(pos) {}
        iterator(const iterator& other) : data_(other.data_), pos_(other.pos_) {}
        ~iterator() {}

        iterator& operator=(const iterator& other) {
            this->data_ = other.data_;
            this->pos_ = other.pos_;
            return *this;
        }
        bool operator==(const iterator& other) const { return &this->data_.get() == &other.data_.get() && this->pos_ == other.pos_; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
        iterator& operator++() {
            pos_++;
            return *this;
        }
        reference operator*() const { return *(data_.get().data_ + pos_); }
        pointer operator->() const { return data_.get().data_ + pos_; }

        difference_type operator-(iterator itr) const {
            return pos_ - itr.pos_;
        }

    private:
        std::reference_wrapper<vector> data_;
        size_type pos_;
    };

    class const_iterator {
    public:
        const_iterator() : pos_(0) {}
        explicit const_iterator(std::reference_wrapper<const vector> data) : data_(data), pos_(0) {}
        const_iterator(std::reference_wrapper<const vector> data, size_type pos) : data_(data), pos_(pos) {}
        const_iterator(const const_iterator& other) : data_(other.data_), pos_(other.pos_) {}
        ~const_iterator() {}

        const_iterator& operator=(const const_iterator& other) {
            this->data_ = other.data_;
            this->pos_ = other.pos_;
            return *this;
        }
        bool operator==(const const_iterator& other) const { return &this->data_.get() == &other.data_.get() && this->pos_ == other.pos_; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }
        const_iterator& operator++() {
            pos_++;
            return *this;
        }
        const_reference operator*() const { return *(data_.get().data_ + pos_); }
        const_pointer operator->() const { return data_.get().data_ + pos_; }

        difference_type operator-(const_iterator itr) const {
            return pos_ - itr.pos_;
        }

    private:
        std::reference_wrapper<const vector> data_;
        size_type pos_;
    };

    class reverse_iterator {
    public:
        reverse_iterator() : pos_(0) {}
        explicit reverse_iterator(std::reference_wrapper<vector> data) : data_(data), pos_(0) {}
        reverse_iterator(std::reference_wrapper<vector> data, size_type pos) : data_(data), pos_(pos) {}
        reverse_iterator(const reverse_iterator& other) : data_(other.data_), pos_(other.pos_) {}
        ~reverse_iterator() {}

        reverse_iterator& operator=(const reverse_iterator& other) {
            this->data_ = other.data_;
            this->pos_ = other.pos_;
            return *this;
        }
        bool operator==(const reverse_iterator& other) const { return &this->data_.get() == &other.data_.get() && this->pos_ == other.pos_; }
        bool operator!=(const reverse_iterator& other) const { return !(*this == other); }
        reverse_iterator& operator++() {
            pos_--;
            return *this;
        }
        reference operator*() const { return *(data_.get().data_ + pos_); }
        pointer operator->() const { return data_.get().data_ + pos_; }

        difference_type operator-(reverse_iterator itr) const {
            return pos_ - itr.pos_;
        }

    private:
        std::reference_wrapper<vector> data_;
        size_type pos_;
    };

    class const_reverse_iterator {
    public:
        const_reverse_iterator() : pos_(0) {}
        explicit const_reverse_iterator(std::reference_wrapper<const vector> data) : data_(data), pos_(0) {}
        const_reverse_iterator(std::reference_wrapper<const vector> data, size_type pos) : data_(data), pos_(pos) {}
        const_reverse_iterator(const const_reverse_iterator& other) : data_(other.data_), pos_(other.pos_) {}
        ~const_reverse_iterator() {}

        const_reverse_iterator& operator=(const const_reverse_iterator& other) {
            this->data_ = other.data_;
            this->pos_ = other.pos_;
            return *this;
        }
        bool operator==(const const_reverse_iterator& other) const { return &this->data_.get() == &other.data_.get() && this->pos_ == other.pos_; }
        bool operator!=(const const_reverse_iterator& other) const { return !(*this == other); }
        const_reverse_iterator& operator++() {
            pos_--;
            return *this;
        }
        const_reference operator*() const { return *(data_.get().data_ + pos_); }
        const_pointer operator->() const { return data_.get().data_ + pos_; }

        difference_type operator-(const_reverse_iterator itr) const {
            return pos_ - itr.pos_;
        }

    private:
        std::reference_wrapper<const vector> data_;
        size_type pos_;
    };

    vector() : data_(nullptr), capacity_(0), size_(0) {}

    explicit vector(size_type count) : vector() {
        reserve(count);
        for (size_type i = 0; i < count; ++i) {
            push_back(T());
        }
    }

    vector(size_type count, const T& value) : vector() {
        reserve(count);
        for (size_type i = 0; i < count; ++i) {
            push_back(value);
        }
    }

    template<typename InputIt, typename = typename std::iterator_traits<InputIt>::value_type>
    vector(InputIt first, InputIt last) : vector() {
        reserve(last - first);
        for (; first != last; ++first) {
            push_back(*first);
        }
    }

    vector(const vector& other) : data_(nullptr), capacity_(other.capacity_), size_(other.size_) {
        data_ = new value_type[capacity_];
        memcpy(data_, other.data_, size_ * sizeof(value_type));
    }

    vector(vector&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    vector(std::initializer_list<T> c) : vector() {
        reserve(c.size());
        std::copy(c.begin(), c.end(), data_);
        size_ = c.size();
    }

    virtual ~vector() {
        cleanup();
    }

    vector& operator=(const vector& other) {
        cleanup();
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new value_type[capacity_];
        memcpy(data_, other.data_, size_ * sizeof(value_type));
        return *this;
    }

    vector& operator=(vector&& other) {
        cleanup();
        other.swap(*this);
        return *this;
    }

    vector& operator=(std::initializer_list<T> list) {
        vector tmp(list);
        tmp.swap(*this);
        return *this;
    }

    void assign(size_type count, const T& value) {
        vector tmp(count, value);
        tmp.swap(*this);
    }

    template<typename InputIt, typename = typename std::iterator_traits<InputIt>::value_type>
    void assign(InputIt first, InputIt last) {
        vector tmp(first, last);
        tmp.swap(*this);
    }

    void assign(std::initializer_list<T> list) {
        vector tmp(list);
        tmp.swap(*this);
    }

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

    reference operator[](size_type pos) { return data_[pos]; }

    constexpr const_reference operator[](size_type pos) const { return data_[pos]; }

    reference front() {
        return data_[0];
    }

    const_reference front() const {
        return data_[0];
    }

    reference back() {
        return data_[size_-1];
    }

    const_reference back() const {
        return data_[size_-1];
    }

    T* data() noexcept {
        return data_;
    }

    const T* data() const noexcept {
        return data_;
    }

    constexpr iterator begin() noexcept { return iterator(std::ref(*this)); }

    constexpr const_iterator begin() const noexcept { return const_iterator(std::ref(*this)); }

    constexpr const_iterator cbegin() const noexcept { return const_iterator(std::ref(*this)); }

    constexpr iterator end() noexcept { return iterator(std::ref(*this), size_); }

    constexpr const_iterator end() const noexcept { return const_iterator(std::ref(*this), size_); }

    constexpr const_iterator cend() const noexcept { return const_iterator(std::ref(*this), size_); }

    constexpr reverse_iterator rbegin() noexcept { return reverse_iterator(std::ref(*this), size_ - 1); }

    constexpr const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(std::ref(*this), size_ - 1); }

    constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(std::ref(*this), size_ - 1); }

    constexpr reverse_iterator rend() noexcept { return reverse_iterator(std::ref(*this), -1); }

    constexpr const_reverse_iterator rend() const noexcept { return const_reverse_iterator(std::ref(*this), -1); }

    constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(std::ref(*this), -1); }

    bool empty() const noexcept { return size_ == 0; }

    constexpr size_type size() const noexcept { return size_; }

    // constexpr size_type max_size() const noexcept;

    void reserve(std::size_t count) {
        if (count > capacity_) {
            assert(count > size_);

            auto data = std::unique_ptr<value_type[]>(new value_type[count]);
            std::memcpy(data.get(), data_, size_ * sizeof(value_type));
            capacity_ = count;
            delete[] data_;
            data_ = data.release();
        }
    }

    constexpr size_type capacity() const { return capacity_; }

    void shrink_to_fit() {
        if (size_ > 0 && size_ < capacity_) {
            auto data = std::unique_ptr<value_type[]>(new value_type[size_]);
            std::memcpy(data.get(), data_, size_ * sizeof(value_type));
            capacity_ = size_;
            delete[] data_;
            data_ = data.release();
        }
    }

    void clear() noexcept {
        size_ = 0;
    }

    iterator insert(const_iterator pos, const T& value) {
        expand();
        difference_type dist = pos - cbegin();
        std::size_t i = size_ - 1;
        while (i > dist) {
            data_[i+1] = data_[i];
            i--;
        }
        data_[i+1] = data_[i];
        data_[dist] = value;
        size_ += 1;
        return iterator(*this, dist);
    }

    iterator insert(const_iterator pos, T&& value) {
        expand();
        difference_type dist = pos - cbegin();
        std::size_t i = size_ - 1;
        while (i > dist) {
            data_[i+1] = std::move(data_[i]);
            i--;
        }
        data_[i+1] = data_[i];
        data_[dist] = std::move(value);
        size_ += 1;
        return iterator(*this, dist);
    }

    void swap(vector& other) {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
    }

    void push_back(const_reference value) {
        expand();
        data_[size_++] = value;
    }

private:
    pointer data_;
    size_type capacity_;
    size_type size_;

    void cleanup() {
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
        data_ = nullptr;
    }

    void expand() {
        if (size_ == capacity_) {
            if (capacity_ != 0) {
                const size_type new_size = 2 * capacity_;
                reserve(new_size);
            } else {
                capacity_ = 1;
                data_ = new value_type[capacity_];
            }
        }
    }
};

}  // namespace jade

#endif  // VECTOR_H
