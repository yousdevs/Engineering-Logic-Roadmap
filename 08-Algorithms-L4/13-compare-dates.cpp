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



bool isDate1LessThanDate2(Date date1, Date date2) {
    return (date1.year < date2.year) ? true : ((date1.year ==
        date2.year) ? (date1.month < date2.month ? true : (date1.month ==
            date2.month ? date1.day < date2.day : false)) : false);
}

void printComparisionResult(short year1, short year2, short month1, short month2, short day1, short day2) {
    Date date1 = getDate(year1, month1, day1);
    Date date2 = getDate(year2, month2, day2);
    bool isLess = isDate1LessThanDate2(date1, date2);
    (isLess) ? std::cout << "Yes, Date1 Less than Date2"
        : std::cout << "No, Date1 Is Not Less than Date2";
}

int main()
{
    int year = mylib::readValidInteger("Please enter a year For First Date (e.g., 2000): ");
    int month = mylib::readValidInteger("Please enter a month For First Date (e.g., 2): ");
    int day = mylib::readValidInteger("Please enter a day For First Date (e.g., 2): ");

    int year2 = mylib::readValidInteger("Please enter a year For Second Date (e.g., 2000): ");
    int month2 = mylib::readValidInteger("Please enter a month For Second Date (e.g., 2): ");
    int day2 = mylib::readValidInteger("Please enter a day For Second Date (e.g., 2): ");
    printComparisionResult(year, year2, month, month2, day, day2);
}