# PA2 – Data Structures (C++98)

This repository contains a small data-structure library implemented for Reykjavík University’s **PA2 – Data Structures** assignment.

> **Status:** This README documents **DoublyLinkedList**, **DynamicallySizedArray**, and **Dequeue**.

## Authors

- Haukur Ingi Tómasson
- Gísli Hrafn Halldórsson

## Implemented data structures

### 1) DoublyLinkedList

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

### 2) DynamicallySizedArray

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

## How to compile and run (DoublyLinkedList)

From the `DoublyLinkedList/` folder (uses its Makefile):

```bash
make
./bin/dll < sample1.txt
./bin/dll < sample2.txt
```

## How to compile and run (DynamicallySizedArray)

From the `DynamicallySizedArray/` folder (uses its Makefile):

```bash
make
./bin/dsa < sample1.txt
./bin/dsa < sample2.txt
./bin/dsa < sample3.txt
```

## How to compile and run (Dequeue)

From the `Dequeue/` folder (uses its Makefile):

```bash
make
./bin/dequeue < your_input.txt
```

## Helpful debugging commands

**gdb**
```bash
g++ -std=c++98 -Wall -Wextra -pedantic -g kattis_dll_template.cpp -o dll_test
gdb ./dll_test
```

**valgrind** (memory leaks / invalid accesses)
```bash
valgrind --leak-check=full --show-leak-kinds=all ./dll_test < input.txt
```

