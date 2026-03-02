#include <iostream>
#include "my-lib.h"
#include <iomanip>

bool isLeapYear(int year)
{
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

short totalDaysInMonth(int year, short month)
{
    if (month < 1 || month > 12)
        return 0;

    const short daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (month == 2 && isLeapYear(year)) ? 29 : daysPerMonth[month - 1];
}

short calculateTotalDaysFromBeginningOfYear(short year, short month, short day) {
    if (month < 1 || month > 12)
        return 0;

    int maxDays = totalDaysInMonth(year, month);

    if (day < 1 || day > maxDays)
        return 0;

    short total = 0;
    for (short i = 1; i < month; i++) {
        total += totalDaysInMonth(year, i);
    }
    total += day;
    return total;
}

std::string getDateFromDayOrderInYear(short dayOrder, short year) {
    for (short month = 1; month <= 12; month++) {
        short daysInMonth = totalDaysInMonth(year, month);
        if ((dayOrder - daysInMonth) > 0) {
            dayOrder -= daysInMonth;
        }
        else {
            return std::to_string(dayOrder) + "/" + std::to_string(month) + "/" + std::to_string(year);
        }
    }
    return "Invalid";
}

void printDaysFromBeginningOfYearWithDate(short year, short month, short day) {
    short total = calculateTotalDaysFromBeginningOfYear(year, month, day);
    std::cout << "Total days From Beginning of the year: " << total << std::endl;

    std::cout << "Date Is: " << getDateFromDayOrderInYear(total, year);

}


int main()
{
    int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter a month (e.g., 2): ");
    int day = mylib::readValidInteger("Please enter a day (e.g., 2): ");
    printDaysFromBeginningOfYearWithDate(year, month, day);
}