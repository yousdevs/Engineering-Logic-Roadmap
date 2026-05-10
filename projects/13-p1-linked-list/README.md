# DoublyLinkedList (Header-Only)

This project is a doubly linked list implemented from scratch in C++, built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).

The goal was to implement a feature-rich educational implementation linked list data structure following a step-by-step roadmap that modeled after STL container design principles — starting from the node internals and working up through iterators, modifiers, and algorithms.

The implementation covers the full lifecycle of the data structure: construction, iteration, insertion, deletion, and list algorithms including an in-place merge sort.

## Overview

`DoublyLinkedList<T>` is a generic doubly linked list template class that manages its own memory, supports bidirectional iteration, and provides a clean public API modeled after `std::list`.

The class owns all its nodes and frees them on destruction. No external allocator is used. All pointer surgery is centralized inside two private helpers, keeping the public methods thin and the invariants easy to reason about.

## Features

### Construction
- Default construction (empty list)
- Copy construction (deep copy)
- Move construction (ownership transfer)
- Initializer list construction
- Copy and move assignment operators
- Initializer list assignment

### Element Access
- Access the first and last element by reference
- Const-qualified overloads for both

### Iteration
- Mutable bidirectional iterator
- Const bidirectional iterator with implicit conversion from mutable
- `begin`, `end`, `cbegin`, `cend`
- Compatible with range-based for loops

### Modifiers
- Push and pop from both ends
- Insert a single element before a given iterator position
- Erase a single element or a range
- Clear the entire list

### Algorithms
- Reverse the list in-place
- Remove all elements matching a value
- Remove all elements satisfying a predicate
- Sort ascending (default)
- Sort with a custom comparator (merge sort, no extra allocation)

## Design Notes

### Header-Only

Only the header needs to be included by callers.

No standard library containers or algorithms are used internally. Includes are limited to `<cstddef>`, `<iterator>`, `<utility>`, and `<initializer_list>`.

### Centralized Pointer Surgery

All node wiring goes through two private helpers:

- `_insertBefore(next, newNode)` — links a new node in before a given node, handling the empty list, head, tail, and middle cases
- `_unlink(node)` — detaches a node from the list without deleting it, handling the same four cases

Every public modifier delegates to one of these two. This means the pointer invariants are maintained in exactly one place.

### Merge Sort

`sort()` runs an in-place merge sort on the node pointers directly, without allocating additional nodes or auxiliary containers. A slow/fast pointer split divides the list into halves, and a merge step rebuilds `prev`/`next` links as it goes. The sort accepts a custom comparator following strict weak ordering.

### Unified Assignment

The copy and move assignment operators are collapsed into a single operator that takes its argument by value. This gets copy-or-move for free depending on what the caller passes, and delegates cleanup to `swap`.

## Example

```cpp
#include "doubly_linked_list.hpp"
#include <iostream>

int main() {
    DoublyLinkedList<int> list = {3, 1, 4, 1, 5, 9};

    list.sort();

    for (const auto& v : list)
        std::cout << v << " ";
    // 1 1 3 4 5 9

    list.remove(1);
    std::cout << list.front() << "\n";  // 3
    std::cout << list.size()  << "\n";  // 4

    DoublyLinkedList<int> copy = list;
    copy.reverse();
    std::cout << copy.front() << "\n";  // 9

    return 0;
}
```

## Project Structure

```
doubly-linked-list/
├── CMakeLists.txt
├── include/
│   ├── doubly_linked_list.hpp
└── tests/
    ├── CMakeLists.txt
    └── test_doubly_linked_list.cpp
```

## How to Build and Test

The project uses CMake with GoogleTest pulled in via `FetchContent`. No manual installation needed.

```bash
# Configure
cmake -S . -B build

# Build
cmake --build build

# Run tests
ctest --test-dir build --output-on-failure
```

To build without tests:

```bash
cmake -S . -B build -DBUILD_TESTS=OFF
cmake --build build
```

## How to Use

Since the library is header-only, drop the `include/` folder into your project and include the header:

```cpp
#include "doubly_linked_list.hpp"
```

Then compile normally with any C++17-compatible compiler.