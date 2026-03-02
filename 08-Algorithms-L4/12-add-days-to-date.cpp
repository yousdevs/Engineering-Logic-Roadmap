#include <iostream>
#include "my-lib.h"
#include <iomanip>

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


Date getDateFromDayOrderInYear(short dayOrder, short year) {
    Date date{};
    for (short month = 1; month <= 12; month++) {
        short daysInMonth = totalDaysInMonth(year, month);
        if ((dayOrder - daysInMonth) > 0) {
            dayOrder -= daysInMonth;
        }
        else {
            date.day = dayOrder;
            date.month = month;
            date.year = year;
            return date;
        }
    }
    return date;
}

Date calculateDateAfterAddition(Date startDate, short daysToAdd) {

    short dayOfYear = calculateTotalDaysFromBeginningOfYear(startDate);
    short year = startDate.year;

    while (daysToAdd != 0) {
        short daysInYear = totalDaysInYear(year);
        short remainingDaysInYear = daysInYear - dayOfYear;

        if (daysToAdd > remainingDaysInYear) {
            dayOfYear += remainingDaysInYear;
            daysToAdd -= remainingDaysInYear;
            year++;
            dayOfYear = 0;
        }
        else {
            return getDateFromDayOrderInYear(dayOfYear + daysToAdd, year);
        }
    }
}

void printDateAfterAddition(short year, short month, short day, short daysToAdd) {
    Date currentDate = getDate(year, month, day);
    Date dateAfterAddition = calculateDateAfterAddition(currentDate, daysToAdd);
    std::cout << "Date After adding [" << daysToAdd << "] is: "
        << dateAfterAddition.day << "/" << dateAfterAddition.month << "/" << dateAfterAddition.year;
}

int main()
{
    int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter a month (e.g., 2): ");
    int day = mylib::readValidInteger("Please enter a day (e.g., 2): ");
    int daysToAdd = mylib::readValidInteger("Please enter days to add (e.g., 4): ");
    printDateAfterAddition(year, month, day, daysToAdd);
}