#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

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
    T array_;
    int size_ = 0;

    int getLargestChildIndex(int index) {
        int leftIndex = 2 * index + 1;
        int rightIndex = leftIndex + 1;
        if (rightIndex < size_ && array_[leftIndex] < array_[rightIndex]) {
            return rightIndex; // Right child is larger
        } else {
            return leftIndex; // Left child is larger (or is an only child)
        }
    }

    void heapify(int index) {
        int examined = array_[index];
        // Only heapify non-leaf nodes
        while (index < size_ / 2) {
            int largestChildIndex = getLargestChildIndex(index);
            if (examined >= array_[largestChildIndex]) {
                break; // Heap property is satisfied
            } else {
                // Overwrite the current node with the value of its largest
                // child.
                array_[index] = array_[largestChildIndex];
                // Move the index to the largest child to continue the process
                // down the tree.
                index = largestChildIndex;
            }
        }
        // Place the original root value at the final position determined by
        // the last iteration.
        array_[index] = examined;
    }

  public:
    // [ ] Constructor

    // [ ] Copy Constructor

    // [ ] Assignment operator

    // [ ] Push - must insert an element to the heap.

    // [ ] Pop - must remove the smallest element from the heap.

    // [ ] Peek - must provide access to the smallest element in the heap.

    // [x] Size - must provide the size of the heap. You must avoid any memory
    // leaks or other memory errors in your implementation.
    int size() const {
        return size_;
    }
};

#endif