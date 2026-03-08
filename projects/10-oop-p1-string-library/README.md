# StringLib (Header-Only)

This project is a small C++ header-only utility library built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).  
The main goal of this exercise was to practice object-oriented design, specifically encapsulation, abstraction, and building reusable components.

Instead of relying on existing helper libraries, the project implements a set of common string operations from scratch.

## Overview

StringLib wraps a `std::string` value and exposes both:

- Static utility functions that operate on external strings.
- Instance methods that operate on the object's internal value.

This design allows the same algorithms to be reused either as standalone utilities or as operations on an object.

The class hides the internal string state and exposes a controlled API for manipulating and analyzing text.

## Features

### Text transformation

- Convert text to uppercase or lowercase
- Invert character case
- Capitalize or decapitalize words

### Text analysis

- String length
- Word counting
- Vowel counting
- Uppercase / lowercase character counting
- Specific character counting

### Text manipulation

- Split text using a delimiter
- Join strings with a delimiter
- Replace words
- Reverse word order
- Remove punctuation

### Whitespace handling

- Trim left
- Trim right
- Trim both sides

## Design Notes

### Header-Only Library
All implementations are defined inline in the header file, so the library can be used without separate compilation.

### Encapsulation
The internal string value is stored inside the class and accessed only through public methods like `setValue()` and `getValue()`.

### Abstraction
Users interact with high-level operations such as `countWords()` or `replace()` without needing to know how the underlying logic works.

### Reusable Algorithms
Most features follow a two-layer structure:

- A static function implementing the core logic.
- A member function that applies that logic to the object's internal value.

Example:

```cpp
StringLib::toUpper(text);   // utility function
myString.toUpper();         // modifies internal value
```

## Example

```cpp
#include "StringLib.h"
#include <iostream>

int main() {

    StringLib text("Hello World from StringLib");

    std::cout << "Original: " << text.getValue() << std::endl;

    text.toUpper();
    std::cout << "Uppercase: " << text.getValue() << std::endl;

    std::cout << "Word count: " << text.countWords() << std::endl;

    std::vector<std::string> words = text.split(" ");

    for (const auto& w : words) {
        std::cout << w << std::endl;
    }

    return 0;
}
```

## How to Use

Since the library is header-only, simply include the header in your project.

```cpp
#include "StringLib.h"
```

Then compile normally using any standard C++ compiler.

```bash
g++ main.cpp -o example
./example
```