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


WeekDay calculateWeekDay(short year, short month, short day) {
    //Gregorian
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a) - 2;
    short d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12));
    d = d % 7;

    return (WeekDay)d;
}

enum Month {
    January = 0,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

std::string getMonthName(Month month) {
    const std::string monthNames[12] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August", "September",
        "October", "November", "December"
    };
    return monthNames[month];
}

struct CalendarInfo {
    unsigned short year = 0;
    Month month = Month::January;
    WeekDay monthStartWeekDay = WeekDay::Sunday;
    WeekDay monthEndWeekDay = WeekDay::Sunday;
};

Month calculateMonth(short month) {
    if (month < 1 || month > 12) return Month::January;
    return (Month)(month - 1);
}

WeekDay calculateMonthStartWeekDay(short year, short month) {
    return calculateWeekDay(year, month, 1);
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

WeekDay calculateMonthEndWeekDay(short year, short month) {

    return calculateWeekDay(year, month, totalDaysInMonth(year, month));
}

CalendarInfo getCalendarInfo(short year, short month) {
    CalendarInfo info = {};
    info.year = year;
    info.month = calculateMonth(month);
    info.monthStartWeekDay = calculateMonthStartWeekDay(year, month);
    info.monthEndWeekDay = calculateMonthEndWeekDay(year, month);
    return info;
}

void printCalendar(short year, short month) {
    CalendarInfo info = getCalendarInfo(year, month);

    std::cout << std::setw(2) << std::string(12, '_')
        << getMonthName(info.month)
        << " " << year << std::string(12, '_') << std::endl;

    for (short i = 0; i < 7; i++) {
        std::cout << std::setw(5)
            << getWeekDayName((WeekDay)i).substr(0, 3);
    }
    std::cout << std::endl;

    short currentDay = 1;
    short total = totalDaysInMonth(year, month);

    for (short i = 0; i < info.monthStartWeekDay; i++) {
        std::cout << std::setw(5) << "";
    }

    while (currentDay <= total) {
        std::cout << std::setw(5) << currentDay;

        if ((info.monthStartWeekDay + currentDay) % 7 == 0) // break line if we reach 7 columns
            std::cout << std::endl;

        currentDay++;
    }

    std::cout << std::endl;
}

void printYearCalendar(short year) {
    for (short i = 1; i <= 12; i++) {
        printCalendar(year, i);
        std::cout << std::endl;
    }
}

int main()
{
    int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    //int month = mylib::readValidInteger("Please enter a month (e.g., 2): ");
    printYearCalendar(year);
}