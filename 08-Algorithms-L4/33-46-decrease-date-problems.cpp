#include <iostream>
#include <string>
#include "my-lib.h"

struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
};

Date createDate(int day, int month, int year) {
	return { day, month, year };
}

std::string formatDate(Date date) {
	return std::to_string(date.day) + "/" + std::to_string(date.month) + "/" + std::to_string(date.year);
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

Date decreaseDateByOneDay(Date date) {
    // If current day is the first day of the month,
    // roll back to previous month (and possibly previous year)
    if (date.day == 1 && date.month == 1) {
        date.year--;
        date.month = 12;
        date.day = totalDaysInMonth(date.month, date.year);
    }
    else if (date.day == 1) {
        date.month--;
        date.day = totalDaysInMonth(date.month, date.year);
    }
    else {
        date.day--;
    }

    return date;
}

Date decreaseDateByXDays(Date date, int daysToSubtract) {
    for (int i = 0; i < daysToSubtract; i++) {
        date = decreaseDateByOneDay(date);
    }
    return date;
}

Date decreaseDateByOneWeek(Date date) {
    return decreaseDateByXDays(date, 7);
}

Date decreaseDateByXWeeks(Date date, int weeksToSubtract) {
    for (int i = 0; i < weeksToSubtract; i++) {
        date = decreaseDateByOneWeek(date);
    }
    return date;
}

Date decreaseDateByOneMonth(Date date) {
    if (date.month == 1) {
        date.month = 12;
        date.year--;
    }
    else {
        date.month--;
    }

    int daysInNewMonth = totalDaysInMonth(date.month, date.year);

    if (date.day > daysInNewMonth)
        date.day = daysInNewMonth;

    return date;
}

Date decreaseDateByXMonths(Date date, int monthsToSubtract) {
    for (int i = 0; i < monthsToSubtract; i++) {
        date = decreaseDateByOneMonth(date);
    }
    return date;
}

Date decreaseDateByOneYear(Date date) {
    return decreaseDateByXMonths(date, 12);
}

Date decreaseDateByXYears(Date date, int yearsToSubtract) {
    for (int i = 0; i < yearsToSubtract; i++) {
        date = decreaseDateByOneYear(date);
    }
    return date;
}

Date decreaseDateByXYearsFaster(Date date, int yearsToSubtract) {
    date.year -= yearsToSubtract;

    int daysInMonth = totalDaysInMonth(date.month, date.year);

    if (date.day > daysInMonth)
        date.day = daysInMonth;

    return date;
}

Date decreaseDateByOneDecade(Date date) {
    return decreaseDateByXYearsFaster(date, 10);
}

Date decreaseDateByXDecades(Date date, int decadesToSubtract) {
    while (decadesToSubtract-- != 0) {
        date = decreaseDateByOneDecade(date);
    }
    return date;
}

Date decreaseDateByXDecadesFaster(Date date, int decadesToSubtract) {
    date.year -= decadesToSubtract * 10;

    int daysInMonth = totalDaysInMonth(date.month, date.year);

    if (date.day > daysInMonth)
        date.day = daysInMonth;

    return date;
}

Date decreaseDateByOneCentury(Date date) {
    return decreaseDateByXDecadesFaster(date, 10);
}

Date decreaseDateByOneMillennium(Date date) {
    for (int i = 0; i < 10; i++) {
        date = decreaseDateByOneCentury(date);
    }
    return date;
}


void printDateAfterDecrease(int day, int month, int year) {
	Date date = createDate(day, month, year);

	date = decreaseDateByOneDay(date);
	std::cout << "01-Subtracting one day: " << formatDate(date) << std::endl;

	date = decreaseDateByXDays(date, 10);
	std::cout << "02-Subtracting 10 days: " << formatDate(date) << std::endl;

	date = decreaseDateByOneWeek(date);
	std::cout << "03-Subtracting one Week: " << formatDate(date) << std::endl;

	date = decreaseDateByXWeeks(date, 10);
	std::cout << "04-Subtracting 10 weeks: " << formatDate(date) << std::endl;

	date = decreaseDateByOneMonth(date);
	std::cout << "05-Subtracting one Month: " << formatDate(date) << std::endl;

	date = decreaseDateByXMonths(date, 5);
	std::cout << "06-Subtracting 5 Months: " << formatDate(date) << std::endl;

	date = decreaseDateByOneYear(date);
	std::cout << "07-Subtracting one Year: " << formatDate(date) << std::endl;

	date = decreaseDateByXYears(date, 10);
	std::cout << "08-Subtracting 10 Years: " << formatDate(date) << std::endl;

	date = decreaseDateByXYearsFaster(date, 10);
	std::cout << "09-Subtracting 10 Years (Faster): " << formatDate(date) << std::endl;

	date = decreaseDateByOneDecade(date);
	std::cout << "10-Subtracting one Decade: " << formatDate(date) << std::endl;

	date = decreaseDateByXDecades(date, 10);
	std::cout << "11-Subtracting 10 Decades: " << formatDate(date) << std::endl;

	date = decreaseDateByXDecadesFaster(date, 10);
	std::cout << "12-Subtracting 10 Decades (Faster): " << formatDate(date) << std::endl;

	date = decreaseDateByOneCentury(date);
	std::cout << "13-Subtracting one Century: " << formatDate(date) << std::endl;

	date = decreaseDateByOneMillennium(date);
	std::cout << "14-Subtracting one Millennium: " << formatDate(date) << std::endl;
}

int main() {

	//int day = mylib::readValidInteger("Enter a day: ");
	//int month = mylib::readValidInteger("Enter a month: ");
	//int year = mylib::readValidInteger("Enter a year: ");

	//printDateAfterIncrease(day, month, year);

	printDateAfterDecrease(31, 12, 2022);

	return 0;
}