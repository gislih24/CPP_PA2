#ifndef HEAP_H
#define HEAP_H
#include "DynamicallySizedArray.h"

template <typename T> struct Heap2 {
    /*
    Write your own implementation of a heap, specialized to store 32-bit signed
    integers. Heaps only have a few operations. The data structure should
    support the following operations:

    ◌ Default construction - initializes an empty heap. This is not tested
      explicitly here!
    ◌ Assignment and copy construction - must properly copy the contents of
      another instance of the data structure. Ensure the two instances do not
      share memory afterwards!
    ◌ Push - must insert an element to the heap.
    ◌ Pop - must remove the smallest element from the heap.
    ◌ Peek - must provide access to the smallest element in the heap.
    ◌ Size - must provide the size of the heap. You must avoid any memory leaks
    or other memory errors in your implementation
    */
  private:
    // We import DSA for DRY and frankly because it's optimized.
    DynamicallySizedArray<T> array_;

    /**
     * @brief Heapify the array. This is used in the constructor that takes an
     * array as input.
     *
     * We start from the last non-leaf node and sift down each node until we
     * reach the root. This will ensure that the heap property is maintained for
     * all nodes in the heap.
     */
    void heapify(int index) {
        last_non_leaf_index = (array_.size() / 2) - 1; // For readability
        for (int i = last_non_leaf_index; i > -1; --i) {
            sift_down(i); // Sift down each node until we reach the root
        }
    }

    /**
     * @brief Helper function that swaps the values at the given indices in the
     * array.
     *
     * @param index1 Index of the first value to swap.
     * @param index2 Index of the second value to swap.
     */
    void swap_array_values(int index1, int index2) {
        T tempVar = array_[index1];
        array_[index1] = array_[index2];
        array_[index2] = tempVar;
    }

    /**
     * @brief Sift up the element at the given index to maintain the heap
     * property. This is used in the push() operation.
     *
     * We compare the element with its parent and swap if it's smaller. We
     * repeat this process until we reach the root or the element is no longer
     * smaller than its parent.
     *
     * @param elem_index Index of the element to sift up.
     */
    void sift_up(int elem_index) {
        while (elem_index > 0) {
            int parent_index = (elem_index - 1) / 2;
            if (array_[elem_index] < array_[parent_index]) {
                swap_array_values(elem_index, parent_index);
                elem_index = parent_index;
            } else {
                return;
            }
        }
    }

    /**
     * @brief Sift down the element at the given index to maintain the heap
     * property. This is used in the pop() operation.
     *
     * We compare the element with its children and swap with the smaller child
     * if it's larger. We repeat this process until we reach a leaf or the
     * element is no longer larger than its children.
     *
     * @param elem_index Index of the element to sift down.
     */
    void sift_down(int elem_index) {
        int array_size = array_.size();
        while (true) {
            int left_child_index = 2 * elem_index + 1;
            int right_child_index = left_child_index + 1;
            int smallest = elem_index;

            if (left_child_index < array_size &&
                array_[left_child_index] < array_[smallest]) {
                smallest = left_child_index;
            }
            if (right_child_index < array_size &&
                array_[right_child_index] < array_[smallest]) {
                smallest = right_child_index;
            }

            if (smallest == elem_index) {
                break;
            }

            swap_array_values(elem_index, smallest);
            elem_index = smallest;
        }
    }

  public:
    // Constructor
    Heap2() : array_() {}

    // Copy Constructor
    Heap2(Heap2 const& other) : array_(other.array_) {}

    // Assignment operator
    Heap2& operator=(Heap2 const& other) {
        if (this != &other) {
            array_ = other.array_;
        }
        return *this;
    }

    // Desctructor
    ~Heap2() {} // Pretty redundant here, but included for assignment

    /**
     * @brief Inserts an element into the heap.
     *
     * We push the element to the end of the array and then sift it up to
     * maintain the heap property.
     *
     * @param value The value to insert into the heap.
     */
    void push(T const& value) {
        array_.push_back(value);
        sift_up(array_.size() - 1);
    }

    /**
     * @brief Removes the smallest element from the heap.
     *
     * We swap the root with the last element and pop the last element (which is
     * the smallest). Then we sift down the new root to maintain the heap
     * property.
     *
     * @return The smallest element that was removed from the heap.
     */
    T pop() {
        T minVal = array_[0]; // Store the minimum value to return later
        // If there's only one element, we can just pop it and return
        if (array_.size() == 1) {
            array_.pop_back();
            return minVal;
        }

        T last = array_.back(); // Store last element to move to root after pop
        array_.pop_back();      // Remove the last element from the array
        array_[0] = last;       // Move the last element to the root
        sift_down(0);  // Sift down the new root to maintain the heap property
        return minVal; // Finally, return the min value that we poppped
    }

    /**
     * @brief Provides access to the smallest element in the heap.
     *
     * We simply return the root of the heap, which is the smallest element.
     *
     * @return The smallest element in the heap.
     */
    T const& peek() const {
        return array_[0];
    }

    /**
     * @brief Provides the size of the heap.
     *
     * We return the size of the underlying array, which is the number of
     * elements in the heap.
     *
     * @return The size of the heap.
     */
    int size() const {
        return array_.size();
    }
};

#endif