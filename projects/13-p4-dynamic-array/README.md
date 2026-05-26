# DynamicArray (Header-Only)

This project is a manual memory managed contiguous container implemented from scratch in C++, built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).

The goal was to learn how a growable array works under the hood — managing a raw buffer directly, separating capacity from size, and handling object lifetimes manually through placement new and explicit destructor calls.

## Overview

`DynamicArray<T>` is a generic contiguous sequence that owns a single raw buffer, grows it on demand, and manages object lifetimes inside it manually. It separates capacity from size — the buffer can hold more elements than currently exist, and the caller has direct control over both through `reserve`, `resize`, and `shrink_to_fit`.

## Features

### Construction
- Default construction (no allocation)
- Count construction with default or fill value
- Initializer list construction
- Deep copy construction
- Move construction (ownership transfer, no allocation)
- Copy and move assignment
- Initializer list assignment

### Element Access
- `operator[]` — unchecked, O(1)
- `at` — bounds-checked, throws `std::out_of_range`
- `front` and `back` — with empty-guard
- `data` — raw pointer to the underlying buffer

### Iteration
- Mutable and const random access iterators
- Full arithmetic: `+`, `-`, `+=`, `-=`, `[]`
- Full comparison: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Iterator distance via `operator-`
- Compatible with range-based for loops

### Capacity
- `size`, `capacity`, `empty`
- `reserve` — grow buffer without constructing elements
- `shrink_to_fit` — release excess capacity
- `resize` — shrink or grow with default or fill value

### Modifiers
- `push_back` by copy and move
- `emplace_back` — construct in-place at end
- `pop_back`
- `insert` — single element, move overload, and fill count
- `emplace` — construct in-place at arbitrary position
- `erase` — single element or range, with element shifting
- `clear` — destroy all elements, keep capacity
- `swap`

## Design Notes

### Raw Buffer Management

The array uses `::operator new` for allocation rather than `new T[n]`, which would default-construct every element immediately. This gives an uninitialized buffer with no live objects. Elements are then born individually via placement new and destroyed via explicit destructor calls. This mirrors the core lifetime-management model used by `std::vector` implementations, though real implementations go further with allocators, `allocator_traits`, and uninitialized algorithms from `<memory>`.

### Exception-Safe Reallocation

`_reallocate` allocates a fresh buffer, tracks how many elements have been successfully move-constructed into it, and on any exception destroys the partial construction, frees the new buffer, and rethrows — leaving the original buffer untouched. `std::move_if_noexcept` is used during the transfer: if the element's move constructor can throw, it falls back to copy.

### Trivial Destructor Optimization

`_destroyRange` skips explicit destructor calls for types where `std::is_trivially_destructible_v<T>` is true, evaluated at compile time via `if constexpr`. For `int`, `float`, and similar types this means the destroy path is a no-op.

### Growth Strategy

Capacity doubles on each reallocation (`_GROWTH_FACTOR = 2`), making `push_back` amortized O(1). The growth factor is a `static constexpr` — it applies uniformly to all instances and adds no per-object overhead. Real implementations use more sophisticated policies; this is a fixed starting point chosen for simplicity.

## Example

```cpp
#include "dynamic_array.hpp"
#include <iostream>

int main() {
    DynamicArray<int> arr = {3, 1, 4, 1, 5};

    arr.push_back(9);
    arr.reserve(20);

    std::cout << arr.size()     << "\n";  // 6
    std::cout << arr.capacity() << "\n";  // 20

    arr.insert(arr.cbegin(), 0);
    std::cout << arr.front() << "\n";   // 0

    arr.erase(arr.cbegin() + 1, arr.cbegin() + 3);
    std::cout << arr.size() << "\n";    // 4

    arr.shrink_to_fit();
    std::cout << arr.capacity() << "\n";  // 4

    return 0;
}
```

## Project Structure

```
13-p4-dynamic-array/
├── CMakeLists.txt
├── include/
│   └── array.hpp
└── tests/
    ├── CMakeLists.txt
    └── test_array.cpp
```

## How to Build and Test

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## How to Use

Include the header directly:

```cpp
#include "dynamic_array.hpp"
```

Compile with any C++17-compatible compiler.