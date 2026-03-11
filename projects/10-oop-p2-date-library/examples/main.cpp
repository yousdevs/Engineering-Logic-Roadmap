#include "CalendarDate.h"
#include <iostream>

int main() {
	using std::cout;
	using std::endl;

	cout << "===== Constructors =====\n";

	CalendarDate d1;                         // system date
	CalendarDate d2("10/3/2024");            // string constructor
	CalendarDate d3(15, 5, 2022);            // day month year
	//CalendarDate d4(120, 2023);              // day order in year

	cout << d1 << endl;
	cout << d2 << endl;
	cout << d3 << endl;
	//cout << d4 << endl;

	cout << "\n===== Getters / Setters =====\n";

	d3.setDay(20);
	d3.setMonth(6);
	d3.setYear(2025);

	cout << "Day: " << d3.getDay() << endl;
	cout << "Month: " << d3.getMonth() << endl;
	cout << "Year: " << d3.getYear() << endl;

	cout << "Updated date: " << d3 << endl;

	cout << "\n===== Validation =====\n";

	//CalendarDate invalidDate(31, 2, 2024);

	//cout << "Is d2 valid? " << d2.isValid() << endl;
	//cout << "Is invalidDate valid? " << invalidDate.isValid() << endl;

	//cout << "\n===== Calendar Generation =====\n";

	//cout << CalendarDate::generateMonthCalendar(3, 2024);

	//cout << CalendarDate::generateYearCalendar(2024);

	cout << "\n===== Leap Year =====\n";

	cout << "2024 leap year? "
		<< CalendarDate::isLeapYear(2024) << endl;

	cout << "d2 leap year? "
		<< d2.isLeapYear() << endl;


	cout << "\n===== Days / Time Calculations =====\n";

	cout << "Days in year: "
		<< CalendarDate::numberOfDaysInYear(2024) << endl;

	cout << "Days in month: "
		<< CalendarDate::numberOfDaysInMonth(2, 2024) << endl;

	cout << "Hours in month: "
		<< CalendarDate::numberOfHoursInMonth(2, 2024) << endl;

	cout << "Minutes in year: "
		<< CalendarDate::numberOfMinutesInYear(2024) << endl;


	cout << "\n===== Day / Month Names =====\n";

	cout << "Day order: "
		<< CalendarDate::dayOfWeekOrder(10, 3, 2024) << endl;

	cout << "Day short name: "
		<< CalendarDate::dayShortName(10, 3, 2024) << endl;

	cout << "Month short name: "
		<< CalendarDate::monthShortName(3) << endl;


	cout << "\n===== Days From Beginning Of Year =====\n";

	cout << CalendarDate::daysFromBeginningOfYear(10, 3, 2024) << endl;

	cout << "Date from order 200 in 2023: "
		<< CalendarDate::getDateFromDayOrderInYear(200, 2023) << endl;
	/*
	cout << "\n===== Add Date Operations =====\n";

	CalendarDate addTest(28, 2, 2024);

	cout << "Original: " << addTest << endl;

	addTest.addOneDay();
	cout << "Add one day: " << addTest << endl;

	addTest.addDays(10);
	cout << "Add 10 days: " << addTest << endl;

	addTest.increaseDateByOneWeek();
	cout << "Add week: " << addTest << endl;

	addTest.increaseDateByOneMonth();
	cout << "Add month: " << addTest << endl;

	addTest.increaseDateByOneYear();
	cout << "Add year: " << addTest << endl;
	*/

	
	cout << "\n===== Decrease Date Operations =====\n";

	CalendarDate subTest(10, 3, 2024);

	cout << "Original: " << subTest << endl;

	subTest.decreaseDateByOneDay();
	cout << "Minus one day: " << subTest << endl;

	subTest.decreaseDateByOneWeek();
	cout << "Minus week: " << subTest << endl;

	subTest.decreaseDateByOneMonth();
	cout << "Minus month: " << subTest << endl;

	subTest.decreaseDateByOneYear();
	cout << "Minus year: " << subTest << endl;
	
	cout << "\n===== Date Comparison =====\n";

	CalendarDate c1(10, 3, 2024);
	CalendarDate c2(15, 3, 2024);

	cout << "c1 before c2: "
		<< CalendarDate::isBefore(c1, c2) << endl;

	cout << "c1 equal c2: "
		<< CalendarDate::isEqual(c1, c2) << endl;

	cout << "c1 after c2: "
		<< CalendarDate::isAfter(c1, c2) << endl;


	cout << "\n===== Compare Enum =====\n";

	CalendarDate::CompareResult result = CalendarDate::compare(c1, c2);

	if (result == CalendarDate::CompareResult::Before)
		cout << "c1 before c2\n";


	return 0;
}