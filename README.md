# PA2 – Data Structures (C++98)

This repository contains a small data-structure library implemented for Reykjavík University’s **PA2 – Data Structures** assignment.

> **Status:** This README currently documents the **DoublyLinkedList** only (more structures can be added later).

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

## How to compile and run (DoublyLinkedList / Kattis template)

Because `DoublyLinkedList` is templated, you typically only need `DoublyLinkedList.h`.

If your submission includes a Makefile (recommended for the final ZIP), you can expose a target for this test program, e.g.:

```bash
make dll_test
./dll_test < input.txt
```

Otherwise, compile directly using the course-provided Kattis template.

1) Put `DoublyLinkedList.h` next to the provided Kattis template file (usually named `kattis_dll_template.cpp`).

2) Compile:

```bash
g++ -std=c++98 -Wall -Wextra -pedantic -O2 kattis_dll_template.cpp -o dll_test
```

3) Run:

```bash
./dll_test < input.txt
```

To verify against the sample from the PDF, put the sample input into `input.txt` and check that the output matches exactly.

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

