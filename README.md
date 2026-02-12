---
aliases: 
date created: fim. 12. febrúar 2026 kl. 16:02
date modified: fim. 12. febrúar 2026 kl. 16:02
---

# PA2 – Data Structures (C++98)

This repository contains a small data-structure library implemented for the Reykjavík University’s C++ **PA2 – Data Structures** assignment.

## Authors

- Haukur Ingi Tómasson
- Gísli Hrafn Halldórsson

## Implemented data structures

### 1) DynamicallySizedArray

A dynamically resizing array template implemented without STL containers.

**Files**
- `DynamicallySizedArray.h` – templated implementation (all logic lives here).
- `kattis_dsa_template.cpp` – interactive driver used locally and for Kattis.
- `Makefile` (in the `DynamicallySizedArray/` folder) – local build targets.
- Sample inputs: `sample1.txt`, `sample2.txt`, `sample3.txt`

**Data model**
- Contiguous buffer `data_` of `T`
- Integers `size_` and `capacity_`

**Growth / shrink**
- Doubles capacity on growth (0→1, then ×2) during `push_back`, `insert`, or `resize` when needed.
- Halves capacity when `size_ <= capacity_ / 4`, never below 16 and never below `size_` (avoids thrashing).

**API summary**
- Construction / copy / assignment / destructor: deep-copy semantics via copy-and-swap.
- Accessors: `operator[]`, `at()`, `front()`, `back()`, `size()`, `capacity()`, `empty()`.
- Modifiers: `push_back()`, `pop_back()`, `insert(index, value)`, `erase(index)`, `reserve(n)`, `resize(n)`, `clear()`.

**Complexities**
- `operator[]`, `at()`, `front()`, `back()`: $O(1)$
- `push_back()`: amortized $O(1)$; $O(n)$ when growing
- `insert`/`erase`: $O(n)$ (shifts)
- `reserve`: $O(n)$ (reallocation/copy)
- `resize`: $O(n)$ when growing; $O(1)$ when shrinking (plus shrink check)

**Notes / assumptions**
- C++98-only, uses `<cassert>`; bounds are asserted in debug builds.
- `resize()` growing default-initializes new elements with `T()`.

#### How to compile and run (DynamicallySizedArray)

From the `DynamicallySizedArray/` folder (uses its Makefile):

```bash
make
./bin/dsa < sample1.txt
./bin/dsa < sample2.txt
./bin/dsa < sample3.txt
```

### 2) DoublyLinkedList

A doubly linked list implemented as a **circular list with a sentinel node**.

**Files**
- `DoublyLinkedList.h` – templated implementation (all logic lives here).
- `DoublyLinkedList.cpp` – includes the header (kept only for project structure; not required for templates).

**Data model**
- `Node<T>` contains `prev`, `next`, and `data`.
- `DoublyLinkedList<T>` contains:
  - A **sentinel** `Node<T>` stored by value inside the list object.
  - An integer `list_size`.

The sentinel node simplifies edge cases:
- `sentinel.next` is the **front/head** node (or `&sentinel` if empty)
- `sentinel.prev` is the **back/tail** node (or `&sentinel` if empty)

**Cursor semantics (Kattis requirement)**
- The “cursor” is **not stored** inside the list.
- The caller keeps a `Node<T>* cursor`:
  - It starts at the list’s sentinel node.
  - After `insert`, `erase`, `predecessor`, and `successor`, the caller sets the cursor to the **returned node**.
  - After copy/assignment of a list instance, the caller resets its cursor to that instance’s sentinel node.

In this implementation, the sentinel is returned by `back()` (and the alias `sentinel_end_node()`).

**API summary**
- Construction / copy:
  - `DoublyLinkedList()`
  - `DoublyLinkedList(const DoublyLinkedList& other)`
  - `DoublyLinkedList& operator=(const DoublyLinkedList& other)`
  - `~DoublyLinkedList()`
- Cursor/node operations:
  - `Node<T>* front()` – returns the first node (head)
  - `Node<T>* back()` – returns the sentinel node
  - `Node<T>* insert(Node<T>* cursor, const T& data)` – inserts *before* `cursor`, returns new node
  - `Node<T>* erase(Node<T>* cursor)` – removes `cursor`, returns the node after it
  - `Node<T>* predecessor(Node<T>* cursor)` – returns `cursor->prev`
  - `Node<T>* successor(Node<T>* cursor)` – returns `cursor->next`
  - `int size() const`
- Kattis convenience aliases:
  - `begin_node()` (same as `front()`)
  - `sentinel_end_node()` (same as `back()`)

**Complexities**
- `front`, `back`, `insert`, `erase`, `predecessor`, `successor`, `size`: $O(1)$
- Copy constructor / assignment: $O(n)$
- Destructor: $O(n)$

**Memory ownership**
- Each non-sentinel node is allocated with `new` and owned by the list instance.
- Nodes are freed on `erase()` and in `~DoublyLinkedList()` via an internal `clear_list()`.

**Notes / assumptions**
- If the list is empty, `front()` returns the sentinel node (`sentinel.next == &sentinel`).
  - The Kattis input guarantees it won’t request invalid operations (e.g., `get`/`erase` on the sentinel), so this is safe for the intended tests.

#### How to compile and run (DoublyLinkedList)

From the `DoublyLinkedList/` folder (uses its Makefile):

```bash
make
./bin/dll < sample1.txt
./bin/dll < sample2.txt
```

### 3) Dequeue

A dynamically resizing double-ended queue template implemented without STL containers, using a circular buffer.

**Files**
- `Dequeue.h` – templated implementation.
- `kattis_dequeue_template.cpp` – interactive driver for local runs/Kattis.
- `Makefile` (in the `Dequeue/` folder) – local build targets.

**Data model**
- Circular buffer `data_` with `head_` (logical start), `size_`, and `capacity_`
- Logical index maps to physical via `(head_ + index) % capacity_`

**Growth / shrink**
- Doubles capacity on `push_front`/`push_back` when full; data is re-linearized with `head_ = 0`.
- Halves capacity when `size_ <= capacity_ / 4`, never below 16 and never below `size_`; re-linearizes with `head_ = 0`.

**API summary**
- Construction / copy / assignment / destructor: deep-copy via copy-and-swap.
- Accessors: `front()`, `back()`, `operator[]`, `at()`, `size()`, `capacity()`, `empty()`.
- Modifiers: `push_front()`, `push_back()`, `pop_front()`, `pop_back()`, `reserve(n)`, `resize(n)`.

**Complexities**
- `push_front`/`push_back`/`pop_front`/`pop_back`: amortized $O(1)$; $O(n)$ when resizing
- Access (`[]`, `at`, `front`, `back`): $O(1)$
- `reserve`: $O(n)$ reallocation/copy
- `resize`: $O(n)$ when growing; $O(1)$ when shrinking (plus shrink check)

**Notes / assumptions**
- Middle `insert/erase` are not included (focus is end-operations).
- C++98-only, uses `<cassert>`; assertions guard bounds and state.
#### How to compile and run (Dequeue)

From the `Dequeue/` folder (uses its Makefile):

```bash
make
./bin/dequeue < your_input.txt
```

### 4) Heap2

A **min-heap** template (binary heap) used for the Kattis problem **heap2**, intended for **32-bit signed integers**.

**Files**
- `Heap2.h` – templated heap implementation.
- `kattis_heap2_template.cpp` – Kattis-style main used locally and for submission.

**Dependencies**
- Uses `DynamicallySizedArray<T>` as the underlying storage (`#include "DynamicallySizedArray.h"`).

**Data model / invariants**
- Stored as a contiguous array in level-order.
- Index relationships:
  - `parent(i) = (i - 1) / 2`
  - `left(i) = 2*i + 1`, `right(i) = 2*i + 2`
- **Min-heap property:** for every node `i > 0`, `_array[parent(i)] <= _array[i]`.

**API summary**
- Construction / copy:
  - `Heap2()`
  - `Heap2(const Heap2& other)`
  - `Heap2& operator=(const Heap2& other)`
  - `~Heap2()`
- Heap operations:
  - `void push(const T& value)`
  - `T pop()` – removes and returns the smallest element
  - `const T& peek() const` – returns the smallest element
  - `int size() const`

**Complexities**
- `push`: $O(\log n)$ (sift-up)
- `pop`: $O(\log n)$ (sift-down)
- `peek`, `size`: $O(1)$
- Copy constructor / assignment: $O(n)$

**Notes / assumptions**
- The Kattis input guarantees that `pop()`/`peek()` are not called on an empty heap.

#### How to compile and run (Heap2)

From the `Heap2/` folder (uses its Makefile):

```bash
make
./bin/heap2 < sample1.txt
./bin/heap2 < sample2.txt
```


### 3) SelfBalancingBST (Treap)

TODO

#### How to compile and run (SelfBalancingBST (Treap))

From the `SelfBalancingBST/` folder (uses its Makefile):

```bash
make
./bin/bst < sample1.txt
./bin/bst < sample2.txt
./bin/bst < sample3.txt
```
