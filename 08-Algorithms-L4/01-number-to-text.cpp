#include <iostream>
#include "my-lib.h"

void printBelowThousand(int number)
{
    std::string ones[] = {
        "", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine"
    };

    std::string teens[] = {
        "ten", "eleven", "twelve", "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    std::string tens[] = {
        "", "", "twenty", "thirty", "forty",
        "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    if (number >= 100)
    {
        std::cout << ones[number / 100] << " hundred ";
        number %= 100;
    }

    if (number >= 10 && number < 20)
    {
        std::cout << teens[number - 10] << " ";
        return;
    }

    if (number >= 20)
    {
        std::cout << tens[number / 10] << " ";
        number %= 10;
    }

    if (number > 0)
    {
        std::cout << ones[number] << " ";
    }
}


void printNumberToWords(int number)
{
    if (number >= 1000000000)
    {
        printBelowThousand(number / 1000000000);
        std::cout << " Billion ";
        number %= 1000000000;
    }

    if (number >= 1000000)
    {
        printBelowThousand(number / 1000000);
        std::cout << " Million ";
        number %= 1000000;
    }

    if (number >= 1000)
    {
        printBelowThousand(number / 1000);
        std::cout << " Thousand ";
        number %= 1000;
    }

    if (number > 0)
    {
        printBelowThousand(number);
    }
}

int main()
{
    int number = mylib::readValidInteger("Please enter a number: ");
    printNumberToWords(number);
}

