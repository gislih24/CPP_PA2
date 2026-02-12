#ifndef DEQUEUE_H
#define DEQUEUE_H

// C++98-only, no STL containers. Header defines templated implementation.
#include <cassert>

/**
 * Dequeue
 * a dynamically resizing double-ended queue for type T.
 * Invariants:
 *  - size_ >= 0
 *  - capacity_ >= size_
 *  - data_ points to an array of capacity_ Ts, or is 0 when capacity_ == 0
 */
template <typename T> struct Dequeue {
  private:
    T* data_;
    int size_;
    int capacity_;
    int head_;

    /**
     * @brief Frees the buffer and resets to an empty state.
     */
    void free_buffer() {
        delete[] data_;
        data_ = 0;
        size_ = 0;
        capacity_ = 0;
        head_ = 0;
    }

    /**
     * @brief Copies contents from another array.
     *
     * @param other is the array to copy from.
     */
    void copy_from_other(Dequeue const& other) {
        // Ensure capacity can hold the other's elements; preserve other's
        // capacity
        if (other.capacity_ > capacity_) {
            reserve(other.capacity_);
        }
        for (int i = 0; i < other.size_; ++i) {
            int phys = (other.head_ + i) %
                       (other.capacity_ == 0 ? 1 : other.capacity_);
            data_[i] = other.data_[phys];
        }
        size_ = other.size_;
        head_ = 0;
    }

    /**
     * @brief Shrinks capacity when size_ is down to a quarter of capacity_.
     *        Uses halving to avoid thrashing; ensures capacity_ >= size_.
     */
    void shrink_if_needed() {
        // Don't shrink below 16 to avoid "thrashing" on small sizes.
        if (capacity_ <= 16) {
            return;
        }
        // Only shrink if size_ is down to a quarter of capacity_ or less.
        if (size_ > capacity_ / 4) {
            return;
        }

        int new_cap = capacity_ / 2;
        // Don't shrink below 16.
        if (new_cap < 16) {
            new_cap = 16;
        }
        // Ensure new_cap is at least size_ to maintain invariants.
        if (new_cap < size_) {
            new_cap = size_;
        }

        T* new_data =
            new T[new_cap]; // Allocate new array with smaller capacity
        // Copy existing elements in logical order starting at head_
        for (int i = 0; i < size_; ++i) {
            int phys = (head_ + i) % (capacity_ == 0 ? 1 : capacity_);
            new_data[i] = data_[phys];
        }
        // Free old array and update pointers and capacity
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
        head_ = 0;
    }

    /**
     * @brief Swaps the contents of this array with another array.
     *
     * @param other The array to swap with.
     */
    void swap(Dequeue& other) {
        T* t_data = data_;
        data_ = other.data_;
        other.data_ = t_data;

        int t_size = size_;
        size_ = other.size_;
        other.size_ = t_size;

        int t_cap = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = t_cap;

        int t_head = head_;
        head_ = other.head_;
        other.head_ = t_head;
    }

  public:
    // Constructor: empty array
    Dequeue() : data_(0), size_(0), capacity_(0), head_(0) {}

    // Deep copy
    Dequeue(Dequeue const& other) : data_(0), size_(0), capacity_(0), head_(0) {
        copy_from_other(other);
    }

    // Assignment operator: deep copy
    Dequeue& operator=(Dequeue const& other) {
        if (this != &other) {
            // Use copy-and-swap idiom for strong exception safety: copy first,
            // then swap.
            Dequeue tmp(other);
            // Swap the contents of `this` with the temporary copy.
            // If the copy constructor throws an error, we won't have modified
            // `this` at all.
            // If it succeeds, we swap the new data into this and let tmp's
            // destructor clean up the old data.
            swap(tmp);
        }
        return *this;
    }

    // Destructor
    ~Dequeue() {
        free_buffer();
    }

    // Size and capacity
    int size() const {
        return size_;
    }
    int capacity() const {
        return capacity_;
    }
    // front accessors
    T& front() {
        assert(size_ > 0);
        return data_[head_];
    }
    // const version of front()
    T const& front() const {
        assert(size_ > 0);
        return data_[head_];
    }

    // back() accessors
    T& back() {
        assert(size_ > 0);
        int phys = (head_ + size_ - 1) % (capacity_ == 0 ? 1 : capacity_);
        return data_[phys];
    }
    // const version of back()
    T const& back() const {
        assert(size_ > 0);
        int phys = (head_ + size_ - 1) % (capacity_ == 0 ? 1 : capacity_);
        return data_[phys];
    }
    bool empty() const {
        return size_ == 0;
    }

    // Element access
    T& operator[](int index) {
        assert(index >= 0 && index < size_);
        int phys = (head_ + index) % (capacity_ == 0 ? 1 : capacity_);
        return data_[phys];
    }
    // const version of operator[]
    T const& operator[](int index) const {
        assert(index >= 0 && index < size_);
        int phys = (head_ + index) % (capacity_ == 0 ? 1 : capacity_);
        return data_[phys];
    }

    // Alternative element accessors with bounds checking and front/back access

    // at() accessors with bounds checking.
    T& at(int index) {
        assert(index >= 0 && index < size_);
        int phys = (head_ + index) % (capacity_ == 0 ? 1 : capacity_);
        return data_[phys];
    }
    // const version of at()
    T const& at(int index) const {
        assert(index >= 0 && index < size_);
        int phys = (head_ + index) % (capacity_ == 0 ? 1 : capacity_);
        return data_[phys];
    }

    /**
     * @brief Reserves capacity for at least new_capacity elements. Does not
     * change size_. If new_capacity <= capacity_, does nothing.
     *
     * @param new_capacity Desired capacity (>= 0).
     */
    void reserve(int new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        T* new_data = new T[new_capacity];
        // Copy existing elements in logical order starting at head_
        for (int i = 0; i < size_; ++i) {
            int phys = (head_ + i) % (capacity_ == 0 ? 1 : capacity_);
            new_data[i] = data_[phys];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
        head_ = 0;
    }

    /**
     * @brief Append value to end. Grows capacity if needed.
     *
     * @param value Element to append.
     */
    void push_back(T const& value) {
        if (size_ == capacity_) {
            int new_cap = (capacity_ == 0) ? 1 : (capacity_ * 2);
            reserve(new_cap);
        }
        int phys = (head_ + size_) % capacity_;
        data_[phys] = value;
        ++size_;
    }

    /**
     * @brief Append value to front. Grows capacity if needed.
     *
     * @param value Element to add.
     */
    void push_front(T const& value) {
        if (size_ == capacity_) {
            int new_cap = (capacity_ == 0) ? 1 : (capacity_ * 2);
            reserve(new_cap);
        }
        head_ = (head_ - 1 + capacity_) % capacity_;
        data_[head_] = value;
        ++size_;
    }

    /**
     * @brief Remove last element. Does not change capacity, but may shrink if
     *        size_ is down to a quarter of capacity_.
     */
    void pop_back() {
        assert(size_ > 0);
        --size_;
        shrink_if_needed();
    }

    /**
     * @brief Remove first element. Does not change capacity, but may shrink if
     *        size_ is down to a quarter of capacity_.
     */
    void pop_front() {
        assert(size_ > 0);
        head_ = (head_ + 1) % capacity_;
        --size_;
        shrink_if_needed();
    }

    // /**
    //  * @brief Insert value at index, shifting elements to the right.
    //  *        Maintains relative order of existing elements.
    //  * @param index Position in [0, size_] where value will be inserted.
    //  * @param value Element to insert.
    //  */
    // void insert(int index, T const& value) {
    //     assert(index >= 0 && index <= size_);
    //     if (size_ == capacity_) {
    //         int new_cap = (capacity_ == 0) ? 1 : (capacity_ * 2);
    //         reserve(new_cap);
    //     }
    //     // Shift right from end to index
    //     for (int i = size_; i > index; --i) {
    //         data_[i] = data_[i - 1];
    //     }
    //     data_[index] = value;
    //     ++size_;
    // }

    // /**
    //  * @brief Erase element at index, shifting remaining elements left.
    //  *        Maintains relative order and no gaps.
    //  * @param index Position in [0, size_ - 1] to erase.
    //  */
    // void erase(int index) {
    //     assert(index >= 0 && index < size_);
    //     // Shift left from index+1 to end
    //     for (int i = index; i < size_ - 1; ++i) {
    //         data_[i] = data_[i + 1];
    //     }
    //     --size_;
    //     shrink_if_needed();
    // }

    /**
     * @brief Resize to new_size. If growing, fill new slots with default
     * values. Capacity may grow to accommodate, but is otherwise unchanged.
     *
     * @param new_size Desired size (>= 0).
     */
    void resize(int new_size) {
        assert(new_size >= 0);
        if (new_size <= size_) {
            size_ = new_size;
            shrink_if_needed();
            return;
        }
        // Need to grow; ensure capacity
        if (new_size > capacity_) {
            // Grow to at least new_size; doubling strategy
            int new_cap = (capacity_ == 0) ? 1 : capacity_;
            while (new_cap < new_size) {
                new_cap *= 2;
            }
            reserve(new_cap);
        }
        // Default-initialize new elements in logical order
        for (int i = size_; i < new_size; ++i) {
            int phys = (head_ + i) % capacity_;
            data_[phys] = T();
        }
        size_ = new_size;
    }

    //     /**
    //      * @brief Clear all elements, resetting to empty state. May shrink
    //      capacity
    //      * if size_ is down to a quarter of capacity_.
    //      */
    //     void clear() {
    //         size_ = 0;
    //         shrink_if_needed();
    //     }
};

#endif // DEQUEUE_H