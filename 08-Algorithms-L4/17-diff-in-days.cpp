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

bool isDate1LessThanDate2(Date date1, Date date2) {
    return (date1.year < date2.year) ? true : ((date1.year ==
        date2.year) ? (date1.month < date2.month ? true : (date1.month ==
            date2.month ? date1.day < date2.day : false)) : false);
}


short calculateDiffDays(Date date1, Date date2, bool IncludeEndDay = false) {

    short totalDays1 = calculateTotalDaysFromBeginningOfYear(date1);
    short totalDays2 = calculateTotalDaysFromBeginningOfYear(date2);
    short totalDiffDays = 0;

    if (isDate1LessThanDate2(date1, date2))
        std::swap(date1, date2);

    totalDays1 = calculateTotalDaysFromBeginningOfYear(date1);
    totalDays2 = calculateTotalDaysFromBeginningOfYear(date2);

    totalDiffDays += totalDaysInYear(date2.year) - totalDays2;
    date2.year++;

    while (date2.year < date1.year) {
        totalDiffDays += totalDaysInYear(date2.year);
        date2.year++;
    }

    totalDiffDays += totalDays1;

    return IncludeEndDay ? totalDiffDays + 1 : totalDiffDays;
}

void printDiffResult(short year1, short year2, short month1, short month2, short day1, short day2) {
    Date date1 = getDate(year1, month1, day1);
    Date date2 = getDate(year2, month2, day2);
    bool isLess = isDate1LessThanDate2(date1, date2);
    short diff = calculateDiffDays(date1, date2, true);
    std::cout << "Diff is (" << diff << ") day(s).";
}

int main()
{
    int year = mylib::readValidInteger("Please enter a year For First Date (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter a month For First Date (e.g., 2): ");
    int day = mylib::readValidInteger("Please enter a day For First Date (e.g., 2): ");

    int year2 = mylib::readValidInteger("Please enter a year For Second Date (e.g., 2000): ");
    int month2 = mylib::readValidInteger("Please enter a month For Second Date (e.g., 2): ");
    int day2 = mylib::readValidInteger("Please enter a day For Second Date (e.g., 2): ");
    printDiffResult(year, year2, month, month2, day, day2);
}