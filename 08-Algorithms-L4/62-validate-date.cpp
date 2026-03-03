#include <iostream>

struct Date
{
	int year;
	int month;
	int day;
};

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


bool isValidDate(Date d) {
	if (d.day < 1 || d.day > totalDaysInMonth(d.year, d.month)) return false;
	if (d.year < 1) return false;
	if (d.month < 1 || d.month > 12) return false;
	return true;
}


int main()
{
	Date d{};
	d.day = 1;
	d.month = 1;
	d.year = 2022;
	(isValidDate(d)) ?
		std::cout << "Yes"
		: std::cout << "No";
	
}