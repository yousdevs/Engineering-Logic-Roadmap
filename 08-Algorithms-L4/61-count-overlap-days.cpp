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

bool isOverlap(Period p1, Period p2) {
	//inclusive
	return !(
		isDate1BeforeDate2(p1.endDate, p2.startDate) ||
		isDate1AfterDate2(p1.startDate, p2.endDate)
		);
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
	Date d{};
	if (date.day == totalDaysInMonth(date.month, date.year) && isLastMonthInYear(date.month)) {
		d.day = 1;
		d.month = 1;
		d.year = ++date.year;
		return d;
	}
	else if (date.day == totalDaysInMonth(date.month, date.year)) {
		d.day = 1;
		d.month = ++date.month;
		d.year = date.year;
		return d;
	}
	d.day = ++date.day;
	d.month = date.month;
	d.year = date.year;
	return d;
}

int calculateOverlapDaysCount(Period p1, Period p2) {
	if (!isOverlap(p1, p2)) return 0;

	Date overlapStartDate =
		isDate1AfterDate2(p1.startDate, p2.startDate)
		? p1.startDate
		: p2.startDate;

	Date overlapEndDate = overlapStartDate;
	Date minEndDate = (isDate1AfterDate2(p1.endDate, p2.endDate)) ? p2.endDate : p1.endDate;
	
	int total = 0;
	while (!isDate1EqualDate2(overlapEndDate, minEndDate)) {
		total++;
		overlapEndDate = increaseDateByOneDay(overlapEndDate);
	}
	return total;
}

int main()
{
	Period p1 = {
		{2022, 1, 1},
		{2022, 1, 10}
	};

	Period p2 = {
		{2022, 1, 5},
		{2050, 12, 30}
	};

	std::cout << "Overlap Days Count is " << calculateOverlapDaysCount(p1, p2);


	return 0;
}