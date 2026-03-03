#include <iostream>
#include "my-lib.h"
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


Date stringToDate(std::string str) {
	std::vector<std::string> splitted = mylib::split(str, "/");
	Date d{};
	d.day = std::stoi(splitted[0]); //TODO handle out of bound
	d.month = std::stoi(splitted[1]);
	d.year = std::stoi(splitted[2]);
	return d; // TODO validate
}

std::string  dateToStr(Date converted) {
	return std::to_string(converted.day)
		+ "/" + std::to_string(converted.month)
		+ "/" + std::to_string(converted.year);

}
int main()
{
	std::string dateStr = "21/2/2001";
	Date converted = stringToDate(dateStr);
	std::cout << "Day: " << converted.day << std::endl;
	std::cout << "Month: " << converted.month << std::endl;
	std::cout << "Year: " << converted.year << std::endl;

	std::string dToStr = dateToStr(converted);
	std::cout << dToStr;
}