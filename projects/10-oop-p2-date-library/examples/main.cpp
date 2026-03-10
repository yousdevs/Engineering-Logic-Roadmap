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

	return 0;
}