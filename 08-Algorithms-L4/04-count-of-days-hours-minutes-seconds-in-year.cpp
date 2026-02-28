#include <iostream>
#include "my-lib.h"
#include <iomanip>

bool isLeapYear(int year)
{
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

short totalDaysInYear(int year) {
    return (isLeapYear(year)) ? 366 : 365;
}
short totalHoursInYear(int year) {
    return 24 * totalDaysInYear(year);
}
int totalMinutesInYear(int year) {
    return 60 * totalHoursInYear(year);
}
int totalSecondsInYear(int year) {
    return 60 * totalMinutesInYear(year);
}

struct YearTimeBreakdown
{
    unsigned short totalDays = 0;
    unsigned short totalHours = 0;
    unsigned int totalMinutes = 0;
    unsigned int totalSeconds = 0;
};

YearTimeBreakdown calculateYearTimeBreakdown(int year)
{
    YearTimeBreakdown breakdown{};

    breakdown.totalDays = totalDaysInYear(year);
    breakdown.totalHours = breakdown.totalDays * 24;
    breakdown.totalMinutes = breakdown.totalHours * 60;
    breakdown.totalSeconds = breakdown.totalMinutes * 60;

    return breakdown;
}

void printYearTimeBreakdown(int year)
{
    YearTimeBreakdown breakdown = calculateYearTimeBreakdown(year);

    std::cout << std::setw(30) << "Total Days in [" << year << "] is: "
        << std::setw(8) << breakdown.totalDays << std::endl;

    std::cout << std::setw(30) << "Total Hours in [" << year << "] is: "
        << std::setw(8) << breakdown.totalHours << std::endl;

    std::cout << std::setw(30) << "Total Minutes in [" << year << "] is: "
        << std::setw(8) << breakdown.totalMinutes << std::endl;

    std::cout << std::setw(30) << "Total Seconds in [" << year << "] is: "
        << std::setw(8) << breakdown.totalSeconds << std::endl;
}

int main()
{
    int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    printYearTimeBreakdown(year);
}