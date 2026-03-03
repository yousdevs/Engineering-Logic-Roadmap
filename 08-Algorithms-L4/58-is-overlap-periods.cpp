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

struct Period {
	Date startDate{};
	Date endDate{};
};

bool isOverlap(Period p1, Period p2) {
	//inclusive
	return !(
		isDate1BeforeDate2(p1.endDate, p2.startDate) ||
		isDate1AfterDate2(p1.startDate, p2.endDate)
		);
}

int main()
{
	Period p1 = {
		{1, 2, 2022},
		{10, 2, 2022}
	};

	Period p2 = {
		{5, 2, 2022},
		{15, 2, 2022}
	};


	(isOverlap(p1, p2)) ?
		std::cout << "Periods overlap"
		: std::cout << "Periods are not overlap";
}