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




	return 0;
}