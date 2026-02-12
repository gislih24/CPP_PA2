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
    void freeBuffer() {
        delete[] data_;
        data_ = 0;
        size_ = 0;
        capacity_ = 0;
        head_ = 0;
    }

    /**
     * @brief Copies contents from another array.
     * @param other is the array to copy from.
     */
    void copyFromOther(Dequeue const& other) {
        // Ensure capacity can hold the other's elements; preserve other's capacity
        if (other.capacity_ > capacity_) {
            reserve(other.capacity_);
        }
        for (int i = 0; i < other.size_; ++i) {
            int phys = (other.head_ + i) % (other.capacity_ == 0 ? 1 : other.capacity_);
            data_[i] = other.data_[phys];
        }
        size_ = other.size_;
        head_ = 0;
    }

    /**
     * @brief Shrinks capacity when size_ is down to a quarter of capacity_.
     *        Uses halving to avoid thrashing; ensures capacity_ >= size_.
     */
    void shrinkIfNeeded() {
        // Don't shrink below 16 to avoid "thrashing" on small sizes.
        if (capacity_ <= 16) {
            return;
        }
        // Only shrink if size_ is down to a quarter of capacity_ or less.
        if (size_ > capacity_ / 4) {
            return;
        }

        int newCap = capacity_ / 2;
        // Don't shrink below 16.
        if (newCap < 16) {
            newCap = 16;
        }
        // Ensure newCap is at least size_ to maintain invariants.
        if (newCap < size_) {
            newCap = size_;
        }

        T* newData = new T[newCap]; // Allocate new array with smaller capacity
        // Copy existing elements in logical order starting at head_
        for (int i = 0; i < size_; ++i) {
            int phys = (head_ + i) % (capacity_ == 0 ? 1 : capacity_);
            newData[i] = data_[phys];
        }
        // Free old array and update pointers and capacity
        delete[] data_;
        data_ = newData;
        capacity_ = newCap;
        head_ = 0;
    }

    /**
     * @brief Swaps the contents of this array with another array.

     * @param other The array to swap with.
     */
    void swap(Dequeue& other) {
        T* tData = data_;
        data_ = other.data_;
        other.data_ = tData;

        int tSize = size_;
        size_ = other.size_;
        other.size_ = tSize;

        int tCap = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = tCap;

        int tHead = head_;
        head_ = other.head_;
        other.head_ = tHead;
    }

  public:
    // Constructor: empty array
    Dequeue() : data_(0), size_(0), capacity_(0), head_(0) {}

    // Deep copy
    Dequeue(Dequeue const& other)
        : data_(0), size_(0), capacity_(0), head_(0) {
        copyFromOther(other);
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
        freeBuffer();
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
     * @brief Reserves capacity for at least newCapacity elements. Does not
     * change size_. If newCapacity <= capacity_, does nothing.
     * @param newCapacity Desired capacity (>= 0).
     */
    void reserve(int newCapacity) {
        if (newCapacity <= capacity_) {
            return;
        }
        T* newData = new T[newCapacity];
        // Copy existing elements in logical order starting at head_
        for (int i = 0; i < size_; ++i) {
            int phys = (head_ + i) % (capacity_ == 0 ? 1 : capacity_);
            newData[i] = data_[phys];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
        head_ = 0;
    }

    /**
     * @brief Append value to end. Grows capacity if needed.
     * @param value Element to append.
     */
    void push_back(T const& value) {
        if (size_ == capacity_) {
            int newCap = (capacity_ == 0) ? 1 : (capacity_ * 2);
            reserve(newCap);
        }
        int phys = (head_ + size_) % capacity_;
        data_[phys] = value;
        ++size_;
    }
    
    /**
     * @brief Append value to front. Grows capacity if needed.
     * @param value Element to add.
     */
    void push_front(T const& value) {
        if (size_ == capacity_) {
            int newCap = (capacity_ == 0) ? 1 : (capacity_ * 2);
            reserve(newCap);
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
        shrinkIfNeeded();
    }
    
    /**
     * @brief Remove first element. Does not change capacity, but may shrink if
     *        size_ is down to a quarter of capacity_.
     */
    void pop_front() {
        assert(size_ > 0);
        head_ = (head_ + 1) % capacity_;
        --size_;
        shrinkIfNeeded();
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
    //         int newCap = (capacity_ == 0) ? 1 : (capacity_ * 2);
    //         reserve(newCap);
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
    //     shrinkIfNeeded();
    // }

    /**
     * @brief Resize to newSize. If growing, fill new slots with default values.
     *        Capacity may grow to accommodate, but is otherwise unchanged.
     * @param newSize Desired size (>= 0).
     */
    void resize(int newSize) {
        assert(newSize >= 0);
        if (newSize <= size_) {
            size_ = newSize;
            shrinkIfNeeded();
            return;
        }
        // Need to grow; ensure capacity
        if (newSize > capacity_) {
            // Grow to at least newSize; doubling strategy
            int newCap = (capacity_ == 0) ? 1 : capacity_;
            while (newCap < newSize) {
                newCap *= 2;
            }
            reserve(newCap);
        }
        // Default-initialize new elements in logical order
        for (int i = size_; i < newSize; ++i) {
            int phys = (head_ + i) % capacity_;
            data_[phys] = T();
        }
        size_ = newSize;
    }

//     /**
//      * @brief Clear all elements, resetting to empty state. May shrink capacity
//      * if size_ is down to a quarter of capacity_.
//      */
//     void clear() {
//         size_ = 0;
//         shrinkIfNeeded();
//     }
};

#endif // DEQUEUE_H