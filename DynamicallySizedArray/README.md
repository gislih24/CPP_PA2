DynamicallySizedArray
=====================

A C++98 dynamically resizing array template `DynamicallySizedArray<T>` implemented without STL containers. Provides contiguous storage with index-based access and low level vector like operations.

What’s Implemented
------------------
- Abstract DS: Dynamically sized array for `T` (contiguous memory, random access).
- Growth policy: Doubles capacity when full (from 0→1, then ×2) on `push_back()`/`insert()` or `resize()` growth.
- Shrink policy: Halves capacity when `size() <= capacity()/4`, never below 16, and never below `size()`.
- Copy semantics: Deep copy via copy constructor and assignment (`operator=`) using copy-and-swap; instances own their buffers.
- APIs: `size()`, `capacity()`, `empty()`, `reserve()`, `resize()`, `clear()`, `push_back()`, `pop_back()`, `insert(i,x)`, `erase(i)`, element access `operator[]`, `at()`, `front()`, `back()`.

Complexity (Typical)
--------------------
- Append `push_back()`: Amortized O(1), O(n) on growth.
- `insert(i,x)` / `erase(i)`: O(n) due to shifting.
- Access (`[]`, `at`, `front`, `back`): O(1).
- `reserve(n)`: O(n) copy when increasing capacity.
- `resize(n)`: O(n) when growing to initialize new elements; O(1) when shrinking.

Files
-----
- header: [DynamicallySizedArray/DynamicallySizedArray.h](DynamicallySizedArray/DynamicallySizedArray.h)
- Interactive driver with main function: [DynamicallySizedArray/kattis_dsa_template.cpp](DynamicallySizedArray/kattis_dsa_template.cpp)
- Makefile: [DynamicallySizedArray/Makefile](DynamicallySizedArray/Makefile)
- Sample inputs: [DynamicallySizedArray/sample1.txt](DynamicallySizedArray/sample1.txt), [DynamicallySizedArray/sample2.txt](DynamicallySizedArray/sample2.txt), [DynamicallySizedArray/sample3.txt](DynamicallySizedArray/sample3.txt)

Build & Run Locally (C++98)
---------------------------
From the `DynamicallySizedArray/` folder:

```bash
make
./bin/dsa < sample1.txt
./bin/dsa < sample2.txt
./bin/dsa < sample3.txt
```

This compiles the interactive driver and runs it with provided samples. works correctly with all operations from the description

Tests
-----
tests are on Kattis. This README focuses on local compilation and running the interactive driver with the sample inputs.

Notes
-----
- C++98-only implementation; uses raw arrays and `<cassert>` for checks.
- Growth doubling and quarter-based shrink (with a 16-element floor) balance throughput and memory usage.
- `resize()` growing default-initializes new elements via `T()`.
