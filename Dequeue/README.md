Dequeue
=======

A C++98 dynamically resizing double-ended queue template `Dequeue<T>` implemented without STL containers. Supports pushing/popping at both ends with contiguous storage managed as a circular buffer.

Implemented
----------
- Abstract DS: Double-ended queue for `T` (push/pop at both ends, random access by index).
- Implementation: Circular buffer over a heap array with logical `head_`, `size_`, and `capacity_`. Elements are accessed by mapping logical index to physical via `(head_ + index) % capacity_`.
- Growth policy: Doubles capacity when full (from 0→1, then ×2) on `push_front()`/`push_back()` or `resize()` growth; re-linearizes storage so `head_ = 0` after reallocation.
- Shrink policy: Halves capacity when `size() <= capacity()/4`, never below 16, and never below `size()`; re-linearizes with `head_ = 0`.
- Copy semantics: Deep copy via copy constructor and assignment (`operator=`) using copy-and-swap; elements copied in logical order.
- APIs: `size()`, `capacity()`, `empty()`, `reserve()`, `resize()`, `front()`, `back()`, `push_front()`, `push_back()`, `pop_front()`, `pop_back()`, element access `operator[]`, `at()`.

Complexity (Typical)
--------------------
- `push_front()` / `push_back()` / `pop_front()` / `pop_back()`: Amortized O(1); O(n) when resizing.
- Access (`[]`, `at`, `front`, `back`): O(1).
- `reserve(n)`: O(n) copy when increasing capacity.
- `resize(n)`: O(n) when growing to initialize new elements; O(1) when shrinking.

Files
-----
- header: [Dequeue/Dequeue.h](Dequeue/Dequeue.h)
- Interactive driver with main function: [Dequeue/kattis_dequeue_template.cpp](Dequeue/kattis_dequeue_template.cpp)
- Makefile: [Dequeue/Makefile](Dequeue/Makefile)

Build & Run Locally (C++98)
---------------------------
From the `Dequeue/` folder:

```bash
make
# Run with your own input file or via stdin
./bin/dequeue < your_input.txt
```

Driver Input Format
-------------------
The driver manages up to 1000 instances. Each command begins with `instanceId` (1..1000), then an operation token:
- `a otherId`: assignment `dq[id] = dq[other]`
- `+f value`: `push_front(value)`
- `+b value`: `push_back(value)`
- `-f`: `pop_front()`
- `-b`: `pop_back()`
- `f`: print `front()`
- `b`: print `back()`
- `s`: print `size()`

Tests
-----
tests are on Kattis. This README focuses on local compilation and running the interactive driver with inputs.

Notes
-----
- C++98-only; uses raw arrays and `<cassert>`.
- Doubling growth and quarter-based shrink (with a 16-element floor) balance speed and memory.
- `resize()` growing default-initializes new elements via `T()` at the logical tail.
