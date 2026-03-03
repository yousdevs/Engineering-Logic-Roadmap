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
	return (date1.day == date2.day) && (date1.month == date2.month) && (date1.year == date2.year);
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

struct Period {
	Date startDate{};
	Date endDate{};
};


bool isDateWithinPeriod(Period p, Date d) {
	return !(compareDates(d, p.startDate) ==
		DateComparisionResult::Date1BeforeDate2
		||
		compareDates(d, p.endDate) ==
		DateComparisionResult::Date1AfterDate2);
}

int main()
{
	Period p = {
		{2022, 2, 1},
		{2022, 2, 10}
	};
	Date d = {2022, 2, 5};

	(isDateWithinPeriod(p, d)) ?
		std::cout << "Yes"
		: std::cout << "No";

	return 0;
}