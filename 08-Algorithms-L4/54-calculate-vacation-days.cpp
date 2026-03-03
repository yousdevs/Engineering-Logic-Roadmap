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

WeekDay calculateWeekDay(DateInfo date) {
    return calculateWeekDay(date.year, date.month, date.day);
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

int daysUntilEndOfMonth(DateInfo info) {
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

DateInfo increaseDateByOneDay(DateInfo date) {
    // If current day is the last day of the month,
    // roll over to next month (and possibly next year)
    if (date.day == totalDaysInMonth(date.month, date.year) && isLastMonthInYear(date.month)) {
        return { 1, 1, (++date.year) };
    }
    else if (date.day == totalDaysInMonth(date.month, date.year)) {
        return { 1, (++date.month), date.year };
    }
    return { (++date.day), date.month, date.year };
}

bool areDatesEqual(DateInfo date1, DateInfo date2) {
    return (date1.day == date2.day) && (date1.month == date2.month) && (date1.year == date2.year);
}

int calcVacationDays(DateInfo startDate, DateInfo endDate){
    int totalDays = 0;
    while (!areDatesEqual(startDate, endDate)) {
        if (isBusinessDay(startDate.weekDay)) {
            totalDays += 1;
            startDate = increaseDateByOneDay(startDate);
            startDate.weekDay = calculateWeekDay(startDate);
        }
        else {
            startDate = increaseDateByOneDay(startDate);
            startDate.weekDay = calculateWeekDay(startDate);
        }
    }
    return totalDays;
}

void printActualVacationDays(int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear)
{
    DateInfo startDate = getDateInfo(startYear, startMonth, startDay);
    DateInfo endDate = getDateInfo(endYear, endMonth, endDay);

    std::cout << "Vacation starts " << formatDateInfo(startDate) << std::endl;
    std::cout << "Vacation ends " << formatDateInfo(endDate) << std::endl;

    std::cout << "Actual Vacation days count is " << std::to_string(calcVacationDays(startDate, endDate)) << " days" << std::endl;
}

int main()
{
    
    //int startDay = mylib::readValidInteger("Please enter start day (e.g., 3): ");
    //int startMonth = mylib::readValidInteger("Please enter start month (e.g., 2): ");
    //int startYear = mylib::readValidInteger("Please enter start year (e.g., 2000): ");

    //int endDay = mylib::readValidInteger("Please enter end day (e.g., 3): ");
    //int endMonth = mylib::readValidInteger("Please enter end month (e.g., 2): ");
    //int endYear = mylib::readValidInteger("Please enter end year (e.g., 2000): ");

    printActualVacationDays(1, 9, 2022, 5, 9, 2022);

}