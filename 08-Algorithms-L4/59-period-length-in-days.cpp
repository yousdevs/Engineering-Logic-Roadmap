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

short calculateTotalDaysFromBeginningOfYear(Date date) {
	if (date.month < 1 || date.month > 12)
		return 0;

	int maxDays = totalDaysInMonth(date.year, date.month);

	if (date.day < 1 || date.day > maxDays)
		return 0;

	short total = 0;
	for (short i = 1; i < date.month; i++) {
		total += totalDaysInMonth(date.year, i);
	}
	total += date.day;
	return total;
}

short calculateDiffDays(Date date1, Date date2, bool IncludeEndDay = false) {

	short totalDays1 = calculateTotalDaysFromBeginningOfYear(date1);
	short totalDays2 = calculateTotalDaysFromBeginningOfYear(date2);
	short totalDiffDays = 0;

	if (isDate1BeforeDate2(date1, date2))
		std::swap(date1, date2);

	if (date1.year == date2.year)
	{
		short diff = calculateTotalDaysFromBeginningOfYear(date1) -
			calculateTotalDaysFromBeginningOfYear(date2);

		return IncludeEndDay ? diff + 1 : diff;
	}

	totalDays1 = calculateTotalDaysFromBeginningOfYear(date1);
	totalDays2 = calculateTotalDaysFromBeginningOfYear(date2);

	totalDiffDays += totalDaysInYear(date2.year) - totalDays2;
	date2.year++;

	while (date2.year < date1.year) {
		totalDiffDays += totalDaysInYear(date2.year);
		date2.year++;
	}

	totalDiffDays += totalDays1;

	return IncludeEndDay ? ++totalDiffDays: totalDiffDays;
}

int calculatePeriodLength(Period p, bool includeEndDate) {
	return calculateDiffDays(p.startDate, p.endDate, includeEndDate);
}

int main()
{
	Period p = {
		{2022, 2, 1},
		{2022, 2, 10}
	};


	int length = calculatePeriodLength(p, false);
	std::cout << "Period length: " << length;
}