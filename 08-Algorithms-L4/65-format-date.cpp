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

std::string replaceWordInString(std::string str, std::string stringToReplace, std::string sRepalceTo){
	short pos = str.find(stringToReplace);
	while (pos != std::string::npos)
	{
		str = str.replace(pos, stringToReplace.length(),
			sRepalceTo);
		pos = str.find(stringToReplace);//find next
	}
	return str;
}

std::string formateDate(Date date, std::string dateFormat = "dd/mm/yyyy")
{
	std::string formattedDate = "";
	formattedDate = replaceWordInString(dateFormat, "dd", std::to_string(date.day));
	formattedDate = replaceWordInString(formattedDate,"mm", std::to_string(date.month));
	formattedDate = replaceWordInString(formattedDate,"yyyy", std::to_string(date.year));
	return formattedDate;
}

int main()
{
	std::string dateString = "1/1/2001";
	Date date = stringToDate(dateString);
	std::cout << "\n" << formateDate(date) << "\n";
	std::cout << "\n" << formateDate(date, "yyyy/dd/mm") << "\n";
	std::cout << "\n" << formateDate(date, "mm/dd/yyyy") << "\n";
	std::cout << "\n" << formateDate(date, "mm-dd-yyyy") << "\n";
	std::cout << "\n" << formateDate(date, "dd-mm-yyyy") << "\n";
	std::cout << "\n" << formateDate(date, "Day:dd, Month:mm,Year:yyyy") << "\n";

}