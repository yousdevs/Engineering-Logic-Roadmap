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

Date increaseDateByOneDay(Date date) {
	// If current day is the last day of the month,
	// roll over to next month (and possibly next year)
	if (date.day == totalDaysInMonth(date.month, date.year) && isLastMonthInYear(date.month)) {
		return { 1, 1, (++date.year) }; 
	}
	else if (date.day == totalDaysInMonth(date.month, date.year)) {
		return { 1, (++date.month), date.year };
	}
	return {(++date.day), date.month, date.year};
}

Date increaseDateByXDays(Date date, int daysToAdd) {
	for (int i = 0; i < daysToAdd; i++) {
		date = increaseDateByOneDay(date);
	}
	return date;
}

Date increaseDateByOneWeek(Date date) {
	
	return increaseDateByXDays(date, 7);
}

Date increaseDateByXWeeks(Date date, int weeksToAdd) {
	for (int i = 0; i < weeksToAdd; i++) {
		date = increaseDateByOneWeek(date);
	}
	return date;
}

Date increaseDateByOneMonth(Date date) {
	if (isLastMonthInYear(date.month))
	{
		date.month = 1;
		date.year++;
	}
	else
	{
		date.month++;
	}

	int daysInNewMonth = totalDaysInMonth(date.month, date.year);

	if (date.day > daysInNewMonth)
		date.day = daysInNewMonth;

	return date;
}

Date increaseDateByXMonths(Date date, int monthsToAdd) {

	for (int i = 0; i < monthsToAdd; i++) {
		date = increaseDateByOneMonth(date);
	}
	return date;
}

Date increaseDateByOneYear(Date date) {

	return increaseDateByXMonths(date, 12);
}

Date increaseDateByXYears(Date date, int yearsToAdd){

	for (int i = 0; i < yearsToAdd; i++) {
		date = increaseDateByOneYear(date);
	}
	return date;
}

Date increaseDateByXYearsFaster(Date date, int yearsToAdd) {
	date.year += yearsToAdd;
	int daysInMonth = totalDaysInMonth(date.month, date.year);

	if (date.day > daysInMonth)
		date.day = daysInMonth;
	return date;
}

Date increaseDateByOneDecade(Date date) {
	return increaseDateByXYearsFaster(date, 10);
}

Date increaseDateByXDecades(Date date, int decadesToAdd) {
	while (decadesToAdd-- != 0) {
		date = increaseDateByOneDecade(date);
	}
	return date;
}
 
Date increaseDateByXDecadesFaster(Date date, int decadesToAdd) {
	date.year += decadesToAdd * 10; 
	int daysInMonth = totalDaysInMonth(date.month, date.year);

	if (date.day > daysInMonth)
		date.day = daysInMonth;
	return date;
}

Date increaseDateByOneCentury(Date date) {

	return increaseDateByXDecadesFaster(date, 10);
}

Date increaseDateByOneMillennium(Date date) {
	for (int i = 0; i < 10; i++) {
		date = increaseDateByOneCentury(date);
	}
	return date;
}


void printDateAfterIncrease(int day, int month, int year) {
	Date date = createDate(day, month, year);

	date = increaseDateByOneDay(date);
	std::cout << "01-Adding one day: " << formatDate(date) << std::endl;

	date = increaseDateByXDays(date, 10);
	std::cout << "02-Adding 10 days: " << formatDate(date) << std::endl;

	date = increaseDateByOneWeek(date);
	std::cout << "03-Adding one Week: " << formatDate(date) << std::endl;

	date = increaseDateByXWeeks(date, 10);
	std::cout << "04-Adding 10 weeks: " << formatDate(date) << std::endl;

	date = increaseDateByOneMonth(date);
	std::cout << "05-Adding one Month: " << formatDate(date) << std::endl;

	date = increaseDateByXMonths(date, 5);
	std::cout << "06-Adding 5 Months: " << formatDate(date) << std::endl;

	date = increaseDateByOneYear(date);
	std::cout << "07-Adding one Year: " << formatDate(date) << std::endl;

	date = increaseDateByXYears(date, 10);
	std::cout << "08-Adding 10 Years: " << formatDate(date) << std::endl;

	date = increaseDateByXYearsFaster(date, 10);
	std::cout << "09-Adding 10 Years (Faster): " << formatDate(date) << std::endl;

	date = increaseDateByOneDecade(date);
	std::cout << "10-Adding one Decade: " << formatDate(date) << std::endl;

	date = increaseDateByXDecades(date, 10);
	std::cout << "11-Adding 10 Decades: " << formatDate(date) << std::endl;

	date = increaseDateByXDecadesFaster(date, 10);
	std::cout << "12-Adding 10 Decades (Faster): " << formatDate(date) << std::endl;

	date = increaseDateByOneCentury(date);
	std::cout << "13-Adding one Century: " << formatDate(date) << std::endl;

	date = increaseDateByOneMillennium(date);
	std::cout << "14-Adding one Millennium: " << formatDate(date) << std::endl;
}

int main() {

	//int day = mylib::readValidInteger("Enter a day: ");
	//int month = mylib::readValidInteger("Enter a month: ");
	//int year = mylib::readValidInteger("Enter a year: ");

	//printDateAfterIncrease(day, month, year);

	printDateAfterIncrease(31, 12, 2022);

	return 0;
}