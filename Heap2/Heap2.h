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
    // T* array_[1000];
    // We import DSA for code reusability and frankly because it's optimized.
    DynamicallySizedArray<T> array_;

    void heapify(int index) {
        for (int i = (array_.size() / 2) - 1; i > -1; --i) {
            sift_down(i);
        }
    }

    void swap_array_values(int index1, int index2) {
        T tempVar = array_[index1];
        array_[index1] = array_[index2];
        array_[index2] = tempVar;
    }

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
                return;
            }

            swap_array_values(elem_index, smallest);
            elem_index = smallest;
        }
    }

  public:
    // [ ] Constructor
    Heap2() : array_() {}

    // [ ] Copy Constructor
    Heap2(Heap2 const& other) : array_(other.array_) {}

    // [ ] Assignment operator
    Heap2& operator=(Heap2 const& other) {
        if (this == &other) {
            return *this;
        }
        array_ = other.array_;
        return *this;
    }

    // [ ] Desctructor

    // [ ] Push - must insert an element to the heap.
    void push(T value) {
        array_.push_back(value);
        sift_up(array_.size() - 1);
    }

    // [ ] Pop - must remove the smallest element from the heap.
    void pop() {
        if (array_.size() == 1) {
            array_.pop_back();
            return;
        }

        array_[0] = array_.back();
        array_.pop_back();
        sift_down(0);
        return;
    }

    // [ ] Peek - must provide access to the smallest element in the heap.
    T peek() {
        return array_[0];
    }

    // [x] Size - must provide the size of the heap. You must avoid any memory
    // leaks or other memory errors in your implementation.
    int size() const {
        return array_.size();
    }
};

#endif