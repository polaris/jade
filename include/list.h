#ifndef LIST_H
#define LIST_H

#include <cassert>

namespace jade {

template <typename T>
class list {
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::size_t size_type;    

    list() : head_(nullptr), tail_(nullptr) {}
    virtual ~list() { clear(); }

    bool empty() const { return head_ == nullptr; }

    void clear() {
        while (head_) {
            const node* const tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        head_ = nullptr;
        tail_ = nullptr;
    }

    class iterator;
    class const_iterator;

    iterator begin() { return iterator{head_}; }
    const_iterator begin() const { return const_iterator{head_}; }
    iterator end() { return iterator{nullptr}; }
    const_iterator end() const { return const_iterator{nullptr}; }

    void insert(iterator pos, const_reference value) {
        if (pos.current() == head_) {
            push_front(value);
        } else if (pos.current() == nullptr) {
            push_back(value);
        } else {
            assert(head_);
            assert(tail_);
            node* tmp = new node;
            tmp->value = value;
            node* pred = pos.current()->prev;
            pred->next = tmp;
            tmp->prev = pred;
            tmp->next = pos.current();
            pos.current()->prev = tmp;
        }
    }

    void push_front(const_reference value) {
        if (!head_) {
            assert(!tail_);
            head_ = new node;
            head_->value = value;
            tail_ = head_;
        } else {
            assert(tail_);
            node* const new_node = new node;
            new_node->value = value;
            new_node->next = head_;
            head_->prev = new_node;
            head_ = new_node;
        }
    }

    void push_back(const_reference value) {
        if (!head_) {
            assert(!tail_);
            head_ = new node;
            head_->value = value;
            tail_ = head_;
        } else {
            assert(tail_);
            node* const new_node = new node;
            new_node->value = value;
            tail_->next = new_node;
            new_node->prev = tail_;
            tail_ = new_node;
        }
    }

    bool pop_front(reference value) {
        if (head_) {
            assert(tail_);
            value = head_->value;
            const node* const tmp = head_;
            if (head_->next) {
                head_ = head_->next;
                head_->prev = nullptr;
            } else {
                head_ = nullptr;
                tail_ = nullptr;
            }
            delete tmp;
            return true;
        } else {
            assert(!tail_);
            return false;
        }
    }

    bool pop_back(reference value) {
        if (tail_) {
            assert(head_);
            value = tail_->value;
            const node* const tmp = tail_;
            if (tmp->prev) {
                tail_ = tmp->prev;
                tail_->next = nullptr;
            } else {
                head_ = nullptr;
                tail_ = nullptr;
            }
            delete tmp;
            return true;
        } else {
            assert(!head_);
            return false;
        }
    }

private:
    struct node {
        node() : next(nullptr), prev(nullptr), value(){};
        node* next;
        node* prev;
        value_type value;
    };

    node* head_;
    node* tail_;

public:
    class iterator {
    public:
        typedef T& reference;
        typedef T* pointer;

        iterator() : current_(nullptr) {}
        iterator(node* current) : current_(current) {}
        iterator(const iterator& other) : current_(other.current_) {}
        ~iterator() {}

        iterator& operator=(const iterator& other) {
            this->current_ = other.current_;
            return *this;
        }
        bool operator==(const iterator& other) const { return this->current_ == other.current_; }
        bool operator!=(const iterator& other) const { return !(*this == other); }
        iterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        reference operator*() const { return current_->value; }
        pointer operator->() const { return &current_->value; }

        node* current() { return current_; }

    private:
        node* current_;
    };

    class const_iterator {
    public:
        typedef const T& reference;
        typedef const T* pointer;

        const_iterator() {}
        const_iterator(const const_iterator& other) : current_(other.current_) {}
        const_iterator(const iterator& other) : current_(other.current_) {}
        ~const_iterator() {}

        const_iterator& operator=(const const_iterator& other) {
            this->current_ = other.current_;
            return *this;
        }
        bool operator==(const const_iterator& other) const { return this->current_ == other.current_; }
        bool operator!=(const const_iterator& other) const { return !(*this == other); }
        const_iterator& operator++() {
            if (current_) {
                current_->next;
            }
            return *this;
        }
        reference operator*() const { return current_->value; }
        pointer operator->() const { return &current_->value; }
        node* current() { return current_; }

    private:
        node* current_;
    };
};

}  // namespace jade

#endif  // LIST_H
