# UtilityLib (Header-Only)

This project is a small C++ header-only utility library built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).
The goal of this exercise was to practice designing reusable helper utilities and organizing related functionality into a clean static class.

The library provides a set of simple tools for random data generation, array manipulation, text formatting, and basic string encryption.

## Overview

`UtilityLib` is a static utility class that groups together commonly used helper functions.

All functions are static, so the class does not need to be instantiated.
This allows the utilities to be accessed directly through the class name.

The library focuses on practical helpers that are often useful when writing small programs or testing logic, such as generating random values or shuffling arrays.

## Features

### Random generation

* Seed the random number generator
* Generate random integers within a range
* Generate random characters (letters, digits, special characters)
* Generate random words
* Generate formatted keys

Example key format:

```
ABCD-EFGH-IJKL-MNOP
```

### Random data utilities

* Fill arrays with random integers
* Fill arrays with random words
* Fill arrays with random keys

### Swap utilities

Overloaded swap functions for multiple types:

* `int`
* `double`
* `bool`
* `char`
* `std::string`

### Array utilities

* Shuffle arrays of integers
* Shuffle arrays of strings

### Formatting

* Generate tab spacing strings for console output

### Simple text encryption

A basic character-shift encryption mechanism:

* `encryptText`
* `decryptText`

This is not intended for security purposes, but rather as a simple exercise in string manipulation.

## Design Notes

### Header-Only Library

All implementations are defined inline inside the header file, so the library can be used without separate compilation.

### Static Utility Class

The class contains only static methods, which means no objects are required.
Functions are called directly through the class name.

Example:

```cpp
int randomNumber = UtilityLib::getRandomInt(1, 100);
```

## Example

```cpp
#include "UtilityLib.h"
#include <iostream>

int main() {

    UtilityLib::seedRandom();

    std::cout << "Random number: "
              << UtilityLib::getRandomInt(1, 10)
              << std::endl;

    std::string key = UtilityLib::generateKey();
    std::cout << "Generated key: " << key << std::endl;

    std::string text = "Hello";
    std::string encrypted = UtilityLib::encryptText(text, 3);

    std::cout << "Encrypted: " << encrypted << std::endl;
    std::cout << "Decrypted: "
              << UtilityLib::decryptText(encrypted, 3)
              << std::endl;

    return 0;
}
```

## How to Use

Since the library is header-only, simply include the header file in your project.

```cpp
#include "UtilityLib.h"
```

Then compile normally using any standard C++ compiler.

```bash
g++ main.cpp -o example
./example
```
