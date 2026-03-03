#include <iostream>

struct Date
{
	int year;
	int month;
	int day;
};
bool isDate1BeforeDate2(Date date1, Date date2)
{
	return (date1.year < date2.year) ? true : ((date1.year ==
		date2.year) ? (date1.month < date2.month ? true : (date1.month ==
			date2.month ? date1.day < date2.day : false)) : false);
}
bool isDate1EqualDate2(Date date1, Date date2)
{
	return (date1.day == date2.day) && (date2.month == date2.month) && (date1.year == date2.year);
}
bool isDate1AfterDate2(Date date1, Date date2)
{
	return (!isDate1BeforeDate2(date1, date2) &&
		!isDate1EqualDate2(date1, date2));
}


int main()
{
	Date date1 = {1, 1, 2000};
	Date date2 = { 1, 1, 2022 };
	if (isDate1AfterDate2(date1, date2))
		std::cout << "\nYes, Date1 is After Date2.";
	else
		std::cout << "\nNo, Date1 is NOT After Date2.";

	return 0;
}