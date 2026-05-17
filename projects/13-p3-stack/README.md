# Stack (Container Adapter)

This project is a generic LIFO stack implemented as a container adapter in C++, built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).

It is built on top of the [DoublyLinkedList](https://github.com/yousdevs/Engineering-Logic-Roadmap/tree/main/projects/13-p1-linked-list) implemented in a previous exercise, using it as the default underlying container — the same container used by the [Queue](https://github.com/yousdevs/Engineering-Logic-Roadmap/tree/main/projects/13-p2-queue) adapter.

The goal was to practice the distinction between semantic relationships and implementation reuse. Stack and Queue share a container but do not share a class hierarchy — they are independent adapters with opposing access contracts.

## Overview

`Stack<T, Container>` is a generic LIFO adapter that wraps a container and exposes exactly the operations a stack should have. The underlying container defaults to `DoublyLinkedList<T>` and can be swapped for any container that provides `push_back`, `pop_back`, `back`, `size`, and `empty`.

`push` and `pop` both operate on the back of the container. This is the opposing end from `Queue`, which dequeues from the front — same container, two different access contracts, which is precisely why Stack does not inherit from Queue.

## Features

### Construction
- Default construction (empty stack)
- Seeded construction from an existing container (copy or move)
- Copy and move construction
- Copy and move assignment

### Element Access
- Inspect the top element — const only, throws if empty

### Capacity
- Check whether the stack is empty
- Query the number of elements

### Modifiers
- Push a value by copy or move
- Pop the top element — throws if empty
- Swap the contents of two stacks

## Design Notes

### Why Stack Does Not Inherit Queue

Stack and Queue both adapt `DoublyLinkedList<T>`, but that is an implementation coincidence, not a semantic relationship. A stack is LIFO. A queue is FIFO. Inheriting Queue would mean a caller holding a `Queue&` could call `dequeue()` on a stack and pull from the wrong end — the Liskov Substitution Principle breaks immediately. Both adapters are implemented independently through composition, not through a shared class hierarchy.

### Strict LIFO Surface

The public API exposes exactly five operations: `push`, `pop`, `top`, `empty`, and `size`. The underlying container's full interface is hidden behind the `protected` member. Callers have no access to the front, no iteration, no arbitrary insertion.

### Container as a Template Parameter

```cpp
template <typename T, typename Container = DoublyLinkedList<T>>
class Stack { ... };
```

The underlying container is a template parameter, not hardcoded. A `static_assert` enforces that the container's `value_type` matches `T` at compile time, catching mismatches before any instantiation logic runs.

### Throwing on Invalid Access

Both `top()` and `pop()` throw `std::runtime_error` when called on an empty stack, consistent with the Queue adapter. Silent undefined behavior on empty access is harder to debug and harder to test.

## Example

```cpp
#include "Stack.hpp"
#include <iostream>

int main() {
    Stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);

    while (!s.empty()) {
        std::cout << s.top() << "\n";
        s.pop();
    }
    // 3
    // 2
    // 1

    // Seed from an existing list
    DoublyLinkedList<int> list = {10, 20, 30};
    Stack<int> seeded(std::move(list));
    std::cout << seeded.top() << "\n";  // 30

    return 0;
}
```

## Project Structure

```
stack/
├── CMakeLists.txt
├── include/
│   ├── Stack.hpp
│   └── doubly_linked_list.hpp   (from previous project)
└── tests/
    ├── CMakeLists.txt
    └── test_stack.cpp
```

## How to Build and Test

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## How to Use

Include the header and make sure `doubly_linked_list.hpp` is on your include path:

```cpp
#include "Stack.hpp"
```

Compile with any C++17-compatible compiler.