#ifndef DYNAMICALLYSIZEDARRAY_H
#define DYNAMICALLYSIZEDARRAY_H

// C++98-only, no STL containers. Header defines templated implementation.
#include <cassert>

/**
 * DynamicallySizedArray
 * a dynamically resizing array for type T.
 * Invariants:
 *  - size_ >= 0
 *  - capacity_ >= size_
 *  - data_ points to an array of capacity_ Ts, or is 0 when capacity_ == 0
 */
template <typename T> struct DynamicallySizedArray {
  private:
    T* data_;
    int size_;
    int capacity_;

    /**
     * @brief Frees the buffer and resets to an empty state.
     */
    void free_buffer() {
        delete[] data_;
        data_ = 0;
        size_ = 0;
        capacity_ = 0;
    }

    /**
     * @brief Copies contents from another array.
     * @param other is the array to copy from.
     */
    void copy_from_other(DynamicallySizedArray const& other) {
        reserve(other.capacity_);
        for (int i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
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
        // Copy assign existing elements to new array
        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        // Free old array and update pointers and capacity
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    /**
     * @brief Swaps the contents of this array with another array.

     * @param other The array to swap with.
     */
    void swap(DynamicallySizedArray& other) {
        T* t_data = data_;
        data_ = other.data_;
        other.data_ = t_data;

        int t_size = size_;
        size_ = other.size_;
        other.size_ = t_size;

        int t_cap = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = t_cap;
    }

  public:
    // Constructor: empty array
    DynamicallySizedArray() : data_(0), size_(0), capacity_(0) {}

    // Deep copy
    DynamicallySizedArray(DynamicallySizedArray const& other)
        : data_(0), size_(0), capacity_(0) {
        copy_from_other(other);
    }

    // Assignment operator: deep copy
    DynamicallySizedArray& operator=(DynamicallySizedArray const& other) {
        if (this != &other) {
            // Use copy-and-swap idiom for strong exception safety: copy first,
            // then swap.
            DynamicallySizedArray tmp(other);
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
    ~DynamicallySizedArray() {
        free_buffer();
    }

    // Size and capacity
    int size() const {
        return size_;
    }
    int capacity() const {
        return capacity_;
    }
    bool empty() const {
        return size_ == 0;
    }

    // Element access
    T& operator[](int index) {
        assert(index >= 0 && index < size_);
        return data_[index];
    }
    // const version of operator[]
    T const& operator[](int index) const {
        assert(index >= 0 && index < size_);
        return data_[index];
    }

    // Alternative element accessors with bounds checking and front/back access

    // at() accessors with bounds checking.
    T& at(int index) {
        assert(index >= 0 && index < size_);
        return data_[index];
    }
    // const version of at()
    T const& at(int index) const {
        assert(index >= 0 && index < size_);
        return data_[index];
    }

    // front accessors
    T& front() {
        assert(size_ > 0);
        return data_[0];
    }
    // const version of front()
    T const& front() const {
        assert(size_ > 0);
        return data_[0];
    }

    // back() accessors
    T& back() {
        assert(size_ > 0);
        return data_[size_ - 1];
    }
    // const version of back()
    T const& back() const {
        assert(size_ > 0);
        return data_[size_ - 1];
    }

    /**
     * @brief Reserves capacity for at least new_capacity elements. Does not
     * change size_. If new_capacity <= capacity_, does nothing.
     * @param new_capacity Desired capacity (>= 0).
     */
    void reserve(int new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        T* new_data = new T[new_capacity];
        // Copy assign existing elements
        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    /**
     * @brief Append value to end. Grows capacity if needed.
     * @param value Element to append.
     */
    void push_back(T const& value) {
        if (size_ == capacity_) {
            int new_cap = (capacity_ == 0) ? 1 : (capacity_ * 2);
            reserve(new_cap);
        }
        data_[size_++] = value;
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
     * @brief Insert value at index, shifting elements to the right.
     *        Maintains relative order of existing elements.
     * @param index Position in [0, size_] where value will be inserted.
     * @param value Element to insert.
     */
    void insert(int index, T const& value) {
        assert(index >= 0 && index <= size_);
        if (size_ == capacity_) {
            int new_cap = (capacity_ == 0) ? 1 : (capacity_ * 2);
            reserve(new_cap);
        }
        // Shift right from end to index
        for (int i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++size_;
    }

    /**
     * @brief Erase element at index, shifting remaining elements left.
     *        Maintains relative order and no gaps.
     * @param index Position in [0, size_ - 1] to erase.
     */
    void erase(int index) {
        assert(index >= 0 && index < size_);
        // Shift left from index+1 to end
        for (int i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
        shrink_if_needed();
    }

    /**
     * @brief Resize to newSize. If growing, fill new slots with default values.
     *        Capacity may grow to accommodate, but is otherwise unchanged.
     * @param newSize Desired size (>= 0).
     */
    void resize(int newSize) {
        assert(newSize >= 0);
        if (newSize <= size_) {
            size_ = newSize;
            shrink_if_needed();
            return;
        }
        // Need to grow; ensure capacity
        if (newSize > capacity_) {
            // Grow to at least newSize; doubling strategy
            int new_cap = (capacity_ == 0) ? 1 : capacity_;
            while (new_cap < newSize) {
                new_cap *= 2;
            }
            reserve(new_cap);
        }
        // Default-initialize new elements
        for (int i = size_; i < newSize; ++i) {
            data_[i] = T();
        }
        size_ = newSize;
    }

    /**
     * @brief Clear all elements, resetting to empty state. May shrink capacity
     * if size_ is down to a quarter of capacity_.
     */
    void clear() {
        size_ = 0;
        shrink_if_needed();
    }
};

#endif // DYNAMICALLYSIZEDARRAY_H