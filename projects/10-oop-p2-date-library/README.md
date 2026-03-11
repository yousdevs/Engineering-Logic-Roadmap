# CalendarDate (Header-Only)

This project is a small C++ header-only date utility library built as part of the [Engineering Logic Roadmap](https://github.com/yousdevs/Engineering-Logic-Roadmap).  
The goal of this exercise was to practice object-oriented design, date calculations, and building reusable components without relying on existing date libraries.

Instead of using frameworks like `<chrono>`, the project implements common calendar and date operations from scratch.

## Overview

CalendarDate represents a calendar date (`day`, `month`, `year`) and exposes both:

- Static utility functions that operate on external dates.
- Instance methods that operate on the object's internal value.

This design allows the same algorithms to be used either as standalone utilities or as operations on a date object.

The class hides its internal state and provides a clear API for performing date calculations and comparisons.

## Features

### Calendar mechanics

- Leap year detection
- Number of days in a month or year
- Day order in year
- Day of week calculation
- Month and weekday names

### Date arithmetic

- Add or subtract days
- Increase or decrease dates by days, weeks, months, or years
- Calculate difference between two dates

### Comparisons

- Check if a date is before or after another
- Equality comparison
- Structured comparison using `CompareResult`

### Utilities

- Generate a formatted month calendar
- Swap dates
- Validate dates
- Get the current system date

## Design Notes

### Header-Only Library
All implementations are defined inline inside the header file, so the library can be used without separate compilation.

### Encapsulation
The date values are stored inside the class and accessed through controlled getters and setters.

### Abstraction
Users interact with high-level operations like `addDays()` or `getDifferenceInDays()` without needing to know how the underlying calculations work.

### Reusable Algorithms
Most features follow the same structure:

- A static function implementing the core logic.
- A member function that applies that logic to the object's internal value.

Example:

```cpp
CalendarDate::isLeapYear(2024);   // utility function
date.isLeapYear();                // instance method
```

## Example

```cpp
#include "CalendarDate.h"
#include <iostream>

int main() {

    CalendarDate today(10, 3, 2026);
    CalendarDate future = CalendarDate::addDays(today, 10);

    std::cout << "Today: "
              << today.getDay() << "/"
              << today.getMonth() << "/"
              << today.getYear() << std::endl;

    std::cout << "Future date: "
              << future.getDay() << "/"
              << future.getMonth() << "/"
              << future.getYear() << std::endl;

    std::cout << "Difference in days: "
              << CalendarDate::getDifferenceInDays(today, future)
              << std::endl;

    return 0;
}
```

## How to Use

Since the library is header-only, simply include the header in your project.

```cpp
#include "CalendarDate.h"
```

Then compile normally using any standard C++ compiler.

```bash
g++ main.cpp -o example
./example
```