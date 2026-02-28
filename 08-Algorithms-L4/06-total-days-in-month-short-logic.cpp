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

short totalHoursInMonth(int year, int month) {
    return 24 * totalDaysInMonth(year, month);
}
int totalMinutesInMonth(int year, int month) {
    return 60 * totalHoursInMonth(year, month);
}
int totalSecondsInMonth(int year, int month) {
    return 60 * totalMinutesInMonth(year, month);
}

struct MonthTimeBreakdown
{
    unsigned short totalDays = 0;
    unsigned short totalHours = 0;
    unsigned int totalMinutes = 0;
    unsigned int totalSeconds = 0;
};

MonthTimeBreakdown calculateMonthTimeBreakdown(int year, int month)
{
    MonthTimeBreakdown breakdown{};

    breakdown.totalDays = totalDaysInMonth(year, month);
    breakdown.totalHours = breakdown.totalDays * 24;
    breakdown.totalMinutes = breakdown.totalHours * 60;
    breakdown.totalSeconds = breakdown.totalMinutes * 60;

    return breakdown;
}

void printMonthTimeBreakdown(int year, int month)
{
    MonthTimeBreakdown breakdown = calculateMonthTimeBreakdown(year, month);

    std::cout << std::setw(30) << "Total Days in [" << std::to_string(year) << "-" << std::to_string(month) << "] is: "
        << std::setw(8) << breakdown.totalDays << std::endl;

    std::cout << std::setw(30) << "Total Hours in [" << std::to_string(year) << "-" << std::to_string(month) << "] is: "
        << std::setw(8) << breakdown.totalHours << std::endl;

    std::cout << std::setw(30) << "Total Minutes in [" << std::to_string(year) << "-" << std::to_string(month) << "] is: "
        << std::setw(8) << breakdown.totalMinutes << std::endl;

    std::cout << std::setw(30) << "Total Seconds in [" << std::to_string(year) << "-" << std::to_string(month) << "] is: "
        << std::setw(8) << breakdown.totalSeconds << std::endl;
}

int main()
{
    int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter a month (e.g., 2): ");
    printMonthTimeBreakdown(year, month);
}