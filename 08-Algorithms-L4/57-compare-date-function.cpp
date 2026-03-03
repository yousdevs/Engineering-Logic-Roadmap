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

enum DateComparisionResult {
	Date1BeforeDate2 = -1,
	Date1EqualsDate2 = 0,
	Date1AfterDate2 = 1,
};

DateComparisionResult compareDates(Date d1, Date d2) {
	if (isDate1AfterDate2(d1, d2))
		return DateComparisionResult::Date1AfterDate2;
	else if (isDate1BeforeDate2(d1, d2))
		return DateComparisionResult::Date1BeforeDate2;

	return DateComparisionResult::Date1EqualsDate2;
}


int main()
{
	Date date1 = { 1, 1, 2000 };
	Date date2 = { 1, 1, 2005 };
	if (compareDates(date1, date2) == DateComparisionResult::Date1AfterDate2)
		std::cout << "\nDate1 is After Date2.";
	else if (compareDates(date1, date2) == DateComparisionResult::Date1BeforeDate2)
		std::cout << "\nDate1 Before Date2.";
	else
		std::cout << "\nBoth Dates Are same";
	return 0;
}