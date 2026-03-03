#include <iostream>
#include "my-lib.h"
#include <iomanip>

enum WeekDay {
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

std::string getWeekDayName(WeekDay weekDay) {
    const std::string dayNames[7] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    return dayNames[weekDay];
}

struct DateInfo
{
    unsigned short day = 0;
    unsigned short month = 0;
    unsigned short year = 0;
    WeekDay weekDay = WeekDay::Sunday;
};

std::string formatDateInfo(DateInfo info) {
    return getWeekDayName(info.weekDay).substr(0, 3) +
        ", " + std::to_string(info.day) +
        "/" + std::to_string(info.month) +
        "/" + std::to_string(info.year);
}

WeekDay calculateWeekDay(short year, short month, short day) {
    //Gregorian
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a) - 2;
    short d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12));
    d = d % 7;

    return (WeekDay)d;
}

DateInfo getDateInfo(int year, int month, int day)
{
    DateInfo info{};

    info.day = day;
    info.month = month;
    info.year = year;
    info.weekDay = calculateWeekDay(year, month, day);

    return info;
}

bool isEndOfWeek(WeekDay weekday) {
    return weekday == WeekDay::Saturday;
}

bool isWeekEnd(WeekDay weekday) {
    return weekday == WeekDay::Saturday || weekday == WeekDay::Sunday;
}

bool isBusinessDay(WeekDay weekday) {
    return  !isWeekEnd(weekday);
}

int daysUntilEndOfWeek(WeekDay weekday) {
    if (weekday == isEndOfWeek(weekday)) return 0;
    return WeekDay::Saturday - weekday;
}

bool isLeapYear(int year) {
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

bool isLastMonthInYear(int month) {
    return (month == 12);
}

int totalDaysInMonth(int month, int year) {
    if (month < 1 || month > 12) return -1;
    const int daysPerMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return (month == 2 && isLeapYear(year)) ? 29 : daysPerMonth[month - 1];
}

int daysUntilEndOfMonth(DateInfo info){
    return totalDaysInMonth(info.month, info.year) - info.day + 1;
}

int monthsUntilEndOfYear(DateInfo info) {
    return 12 - info.month;
}

int daysUntilEndOfYear(DateInfo info) {
    int totalDays = 0;
    int monthsUntilYearEnd = monthsUntilEndOfYear(info); 

    totalDays += daysUntilEndOfMonth(info);
    info.month++;
    while (monthsUntilYearEnd-- != 0) {
        totalDays += totalDaysInMonth(info.month, info.year);
        info.month++;
    }
    
    return totalDays;
}

void printDateInfo(int year, int month, int day)
{
    DateInfo info = getDateInfo(year, month, day);

    std::cout << std::setw(30) << "Today is: " << std::setw(8) << formatDateInfo(info) << std::endl;
    std::cout << std::setw(30) << "Is it End Of Week? " << std::setw(8);
    isEndOfWeek(info.weekDay) ? std::cout << "Yes, it is" : std::cout << "No, it is Not";
    std::cout << std::endl;
    
    std::cout << std::setw(30) << "Is It WeekEnd? ";
    std::cout << std::setw(8);
    isWeekEnd(info.weekDay) ? std::cout << "Yes, it is" : std::cout << "No, it is Not";
    std::cout << std::endl;

    std::cout << std::setw(30) << "Is It Business Day? ";
    std::cout << std::setw(8);
    isBusinessDay(info.weekDay) ? std::cout << "Yes, it is" : std::cout << "No, it is Not";
    std::cout << std::endl;

    std::cout << std::setw(30) << "Days until end of week: ";
    std::cout << std::setw(8);
    std::cout << daysUntilEndOfWeek(info.weekDay);
    std::cout << std::endl;

    std::cout << std::setw(30) << "Days until end of Month: ";
    std::cout << std::setw(8);
    std::cout << daysUntilEndOfMonth(info);
    std::cout << std::endl;

    std::cout << std::setw(30) << "Days until end of Year: ";
    std::cout << std::setw(8);
    std::cout << daysUntilEndOfYear(info);
    std::cout << std::endl;
}

int main()
{
    //int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    //int month = mylib::readValidInteger("Please enter a month (e.g., 2): ");
    //int day = mylib::readValidInteger("Please enter a day (e.g., 3): ");
    //printDateInfo(year, month, day);
    printDateInfo(2022, 9, 23);
}