# InputValidationLib (Header-Only)

This project is a small C++ header-only input validation library built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).
The goal of this exercise was to practice building reusable console input utilities and validating user input safely.

The library provides simple helpers for validating numeric values and reading safe input from the console.

## Overview

`InputValidationLib` is a static utility class that groups together common validation and input helpers.

All functions are static, so the class does not need to be instantiated.
Functions are accessed directly through the class name.

The library focuses on making console programs more robust by preventing invalid user input and ensuring values are parsed correctly.

## Features

### Numeric validation

* Check whether a number falls within a given range
* Validate whether a string represents an integer
* Validate whether a string represents a floating-point number

### Numeric input

* Read integers from the console
* Read integers within a specified range
* Read floating-point numbers
* Read floating-point numbers within a specified range

### Text input

* Safely read a full line of text from the console

### Yes/No input

* Read simple yes/no responses from the user

## Design Notes

### Header-Only Library

All implementations are defined inline inside the header file, so the library can be used without separate compilation.

### Static Utility Class

The class contains only static methods, which means no objects are required.
Functions are called directly through the class name.

Example:

```cpp
int value = InputValidationLib::readInt();
```

### String-Based Validation

Instead of reading values directly with `std::cin`, input is first read as a string and then validated before conversion.
This avoids common stream errors and makes the input process more reliable.

## Example

```cpp
#include "InputValidationLib.h"
#include <iostream>

int main() {

    std::cout << "Enter an integer: ";
    int number = InputValidationLib::readInt();

    std::cout << "You entered: " << number << std::endl;

    std::cout << "Enter a number between 1 and 10: ";
    int ranged = InputValidationLib::readIntInRange(1, 10);

    std::cout << "Valid number: " << ranged << std::endl;

    std::cout << "Enter your name: ";
    std::string name = InputValidationLib::readLine();

    std::cout << "Hello " << name << std::endl;

    bool result = InputValidationLib::readYesNo("Continue? (y/n): ");

    if (result)
        std::cout << "User chose yes\n";
    else
        std::cout << "User chose no\n";

    return 0;
}
```

## How to Use

Since the library is header-only, simply include the header file in your project.

```cpp
#include "InputValidationLib.h"
```

Then compile normally using any standard C++ compiler.

```bash
g++ main.cpp -o example
./example
```
