#include <iostream>
#include "my-lib.h"

struct Date {
    short day = 0;
    short month = 0;
    short year = 0;
};

Date getDate(short year, short month, short day) {
    //Todo validate
    return { day, month, year };
}

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

short totalDaysInYear(short year) {
    return (isLeapYear(year)) ? 366 : 365;
}

short calculateTotalDaysFromBeginningOfYear(Date date) {
    if (date.month < 1 || date.month > 12)
        return 0;

    int maxDays = totalDaysInMonth(date.year, date.month);

    if (date.day < 1 || date.day > maxDays)
        return 0;

    short total = 0;
    for (short i = 1; i < date.month; i++) {
        total += totalDaysInMonth(date.year, i);
    }
    total += date.day;
    return total;
}

bool isLastDayOfMonth(Date date) {
    return (date.day == totalDaysInMonth(date.year, date.month));
}

bool isLastDayOfYear(Date date) {
    return (calculateTotalDaysFromBeginningOfYear(date) == totalDaysInYear(date.year));
}

bool isLastMonthOfYear(Date date) {
    return (date.year == 12);
}

void printBreakdown(short year, short month, short day) {
    Date date = getDate(year, month, day);
    bool lastDayOfMonth = isLastDayOfMonth(date);
    (lastDayOfMonth) ? std::cout << "Yes, Last Day Of Month"
        : std::cout << "No, Not Last Day of Month";
    std::cout << std::endl;
    bool lastDayOfYear = isLastDayOfYear(date);
    (lastDayOfYear) ? std::cout << "Yes, Last Day Of Year"
        : std::cout << "No, Not Last Day of Year";
    std::cout << std::endl;
    bool lastMonthOfYear = isLastMonthOfYear(date);
    (lastMonthOfYear) ? std::cout << "Yes, Last Month Of Year"
        : std::cout << "No, Not Last Month of Year";
}

int main()
{
    int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter a month  (e.g., 2): ");
    int day = mylib::readValidInteger("Please enter a day (e.g., 2): ");

    printBreakdown(year, month, day);
}