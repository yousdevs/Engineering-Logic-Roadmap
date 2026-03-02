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

WeekDay calculateWeekDay(short year, short month, short day) {
    //Gregorian
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a) - 2;
    short d = ( day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12) ) ;
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

void printDateInfo(int year, int month, int day)
{
    DateInfo info = getDateInfo(year, month, day);

    std::cout << std::setw(30) << "Date: " << std::setw(8) << std::to_string(info.year) << "-" << std::to_string(info.month) << "-" << std::to_string(info.day) << std::endl;

    std::cout << std::setw(30) << "WeekDay Order: " << std::setw(8) << std::to_string(info.weekDay) << std::endl;


    std::cout << std::setw(30) << "WeekDay Name: " << std::setw(8) << getWeekDayName(info.weekDay) << std::endl;

}

int main()
{
    int year = mylib::readValidInteger("Please enter a year (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter a month (e.g., 2): ");
    int day = mylib::readValidInteger("Please enter a day (e.g., 3): ");
    printDateInfo(year, month, day);
}