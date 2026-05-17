# Queue (Container Adapter)

This project is a generic FIFO queue implemented as a container adapter in C++, built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).

It is built on top of the [DoublyLinkedList](https://github.com/yousdevs/Engineering-Logic-Roadmap/tree/main/projects/13-p1-linked-list) implemented in the previous exercise, using it as the default underlying container.

The goal was to practice designing clean adapter abstractions — exposing only what a queue semantically permits, while keeping the underlying container fully hidden from the caller.

## Overview

`Queue<T, Container>` is a generic FIFO adapter that wraps a container and exposes exactly the operations a queue should have. The underlying container is a template parameter, defaulting to `DoublyLinkedList<T>`, and can be swapped out for any container that provides `push_back`, `pop_front`, `front`, `size`, and `empty`.

No iterators. No insert. No erase. The public surface is intentionally minimal — if a caller needs more than what a queue offers, they need a different data structure.

## Features

### Construction
- Default construction (empty queue)
- Seeded construction from an existing container (copy or move)
- Copy and move construction
- copy/move assignment (compiler-generated)

### Element Access
- Inspect the front element — const only, throws if empty

### Capacity
- Check whether the queue is empty
- Query the number of elements

### Modifiers
- Enqueue a value by copy or move
- Dequeue the front element — throws if empty
- Swap the contents of two queues

## Design Notes

### Container Adapter

`Queue<T>` does not implement any data structure logic of its own. It owns a `Container` instance and delegates every operation to it. This means the correctness of the queue depends entirely on the correctness of the underlying container — which in this case was already validated through its own test suite.

### Strict FIFO Surface

The public API exposes exactly five semantic operations: `enqueue`, `dequeue`, `front`, `empty`, and `size`. Nothing else reaches the caller. The underlying container's full interface — iteration, insertion at arbitrary positions, sorting, reversal — is completely hidden behind the `protected` member.

### Container as a Template Parameter

```cpp
template <typename T, typename Container = DoublyLinkedList<T>>
class Queue { ... };
```

The underlying container is not hardcoded. Any container that satisfies the required interface can be substituted without touching the queue logic. A `static_assert` enforces that the container's `value_type` matches `T` at compile time.

### Throwing on Invalid Access

Both `front()` and `dequeue()` throw `std::runtime_error` when called on an empty queue. This is a deliberate choice over undefined behavior — a queue with a silent contract violation is harder to debug than one that fails loudly.

## Example

```cpp
#include "Queue.hpp"
#include <iostream>

int main() {
    Queue<int> q;

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    while (!q.empty()) {
        std::cout << q.front() << "\n";
        q.dequeue();
    }
    // 1
    // 2
    // 3

    // Seed from an existing list
    DoublyLinkedList<int> list = {10, 20, 30};
    Queue<int> seeded(std::move(list));
    std::cout << seeded.front() << "\n";  // 10

    return 0;
}
```

## Project Structure

```
13-p2-queue/
├── CMakeLists.txt
├── include/
│   ├── Queue.hpp
│   └── doubly_linked_list.hpp   (from previous project)
└── tests/
    ├── CMakeLists.txt
    └── test_queue.cpp
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
#include "Queue.hpp"
```

Compile with any C++17-compatible compiler.