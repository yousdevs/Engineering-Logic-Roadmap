#include <iostream>
#include "my-lib.h"

bool isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 != 0 && year % 4 == 0) return true;
    return false;
}

int main()
{
    int year = mylib::readValidInteger("Please enter a Year(eg: 2000): ");
    bool isLeap = isLeapYear(year);
    (isLeap) ?
        std::cout << "\n Yes, leap year"
        : std::cout << "\n No, not leap year";
}

