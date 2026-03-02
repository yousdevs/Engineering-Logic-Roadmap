#include <iostream>
#include "my-lib.h"
#include <ctime>

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

bool isLastDayOfMonth(Date date) {
    return (date.day == totalDaysInMonth(date.year, date.month));
}

bool isLastMonthOfYear(Date date) {
    return (date.month == 12);
}

Date increaseDateByOneDay(Date date) {
    if (isLastMonthOfYear(date) && isLastDayOfMonth(date)) {
        date.year += 1;
        date.day = 1;
        date.month = 1;
        return date;
    }
    else if (isLastDayOfMonth(date)) {
        date.day = 1;
        date.month += 1;
        return date;
    }
    date.day += 1;
    return date;
}

int calculateDiffDays(Date date1, Date date2, bool IncludeEndDay = false){
    int days = 0;
    while (isDate1LessThanDate2(date1, date2))
    {
        days++;
        date1 = increaseDateByOneDay(date1);
    }
    return IncludeEndDay ? ++days : days;
}

Date getSystemDate()
{
    Date result;

    time_t t = time(0);

    tm now;
    localtime_s(&now, &t);

    result.year = now.tm_year + 1900;
    result.month = now.tm_mon + 1;
    result.day = now.tm_mday;

    return result;
}

short calculateAgeInDays(Date birthday) {
    Date currentDate = getSystemDate();
    return calculateDiffDays( birthday, currentDate);
}

void printAgeInDays(short year, short month, short day) {
    Date birthday = getDate(year, month, day);
    short ageInDays = calculateAgeInDays(birthday);
    std::cout << "Your Age Is (" << ageInDays << ") in Days";
}

int main()
{
    std::cout << "Enter Your Birthday: " << std::endl;
    int year = mylib::readValidInteger("Please enter year (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter month (e.g., 2): ");
    int day = mylib::readValidInteger("Please enter day (e.g., 2): ");
    printAgeInDays(year, month, day);
    
    return 0;
}