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
    void freeBuffer() {
        delete[] data_;
        data_ = 0;
        size_ = 0;
        capacity_ = 0;
    }

    /**
     * @brief Copies contents from another array.
     * @param other is the array to copy from.
     */
    void copyFromOther(DynamicallySizedArray const& other) {
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
    void shrinkIfNeeded() {
        // Repeatedly halve capacity while size_ is at or below quarter.
        while (capacity_ > 0 && size_ <= (capacity_ / 4)) {
            int newCap = capacity_ / 2;
            if (newCap < size_) {
                newCap = size_;
            }
            if (newCap == capacity_) {
                break;
            }
            if (newCap <= 0) {
                // Free all when shrinking to zero
                delete[] data_;
                data_ = 0;
                capacity_ = 0;
                break;
            }
            T* newData = new T[newCap];
            for (int i = 0; i < size_; ++i) {
                newData[i] = data_[i];
            }
            delete[] data_;
            data_ = newData;
            capacity_ = newCap;
        }
    }

  public:
    // Constructor: empty array
    DynamicallySizedArray() : data_(0), size_(0), capacity_(0) {}

    // Deep copy
    DynamicallySizedArray(DynamicallySizedArray const& other)
        : data_(0), size_(0), capacity_(0) {
        copyFromOther(other);
    }

    // Assignment operator: deep copy
    DynamicallySizedArray& operator=(DynamicallySizedArray const& other) {
        if (this == &other)
            return *this;
        freeBuffer();
        copyFromOther(other);
        return *this;
    }

    // Destructor
    ~DynamicallySizedArray() {
        freeBuffer();
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
     * @brief Reserves capacity for at least newCapacity elements. Does not
     * change size_. If newCapacity <= capacity_, does nothing.
     * @param newCapacity Desired capacity (>= 0).
     */
    void reserve(int newCapacity) {
        if (newCapacity <= capacity_)
            return;
        T* newData = new T[newCapacity];
        // Copy assign existing elements
        for (int i = 0; i < size_; ++i) {
            newData[i] = data_[i];
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
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
        data_[size_++] = value;
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
     * @brief Insert value at index, shifting elements to the right.
     *        Maintains relative order of existing elements.
     * @param index Position in [0, size_] where value will be inserted.
     * @param value Element to insert.
     */
    void insert(int index, T const& value) {
        assert(index >= 0 && index <= size_);
        if (size_ == capacity_) {
            int newCap = (capacity_ == 0) ? 1 : (capacity_ * 2);
            reserve(newCap);
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
        shrinkIfNeeded();
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
            shrinkIfNeeded();
            return;
        }
        // Need to grow; ensure capacity
        if (newSize > capacity_) {
            // Grow to at least newSize; doubling strategy
            int newCap = (capacity_ == 0) ? 1 : capacity_;
            while (newCap < newSize)
                newCap *= 2;
            reserve(newCap);
        }
        // Default-initialize new elements
        for (int i = size_; i < newSize; ++i) {
            data_[i] = T();
        }
        size_ = newSize;
    }

    // Clear:  removal of all elements
    void clear() {
        size_ = 0;
        shrinkIfNeeded();
    }
};

#endif // DYNAMICALLYSIZEDARRAY_H