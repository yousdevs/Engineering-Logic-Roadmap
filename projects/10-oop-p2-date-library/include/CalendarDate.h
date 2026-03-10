#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "StringLib.h"


class CalendarDate {
private:
    short _day;
    short _month;
    short _year;

public:
    // Constructors
    CalendarDate();
    CalendarDate(const std::string& stringDate);
    CalendarDate(short day, short month, short year);
    CalendarDate(short dateOrderInYear, short year);

    // Getters & Setters
    void setDay(short day);
    short getDay() const;
    void setMonth(short month);
    short getMonth() const;
    void setYear(short year);
    short getYear() const;

    // System Time & Validation
    static CalendarDate getSystemDate();
    static bool isValidDate(const CalendarDate& date);
    bool isValid() const;

    // Output & Formatting
    static std::string dateToString(const CalendarDate& date);
    std::string dateToString() const;


    static std::string generateMonthCalendar(short month, short year);
    std::string generateMonthCalendar() const;
    static std::string generateYearCalendar(short year);
    std::string generateYearCalendar() const;

    // Calendar Mechanics
    static bool isLeapYear(short year);
    bool isLeapYear() const;

    static short numberOfDaysInYear(short year);
    short numberOfDaysInYear() const;
    static short numberOfHoursInYear(short year);
    short numberOfHoursInYear() const;
    static int numberOfMinutesInYear(short year);
    int numberOfMinutesInYear() const;
    static int numberOfSecondsInYear(short year);
    int numberOfSecondsInYear() const;

    static short numberOfDaysInMonth(short month, short year);
    short numberOfDaysInMonth() const;
    static short numberOfHoursInMonth(short month, short year);
    short numberOfHoursInMonth() const;
    static int numberOfMinutesInMonth(short month, short year);
    int numberOfMinutesInMonth() const;
    static int numberOfSecondsInMonth(short month, short year);
    int numberOfSecondsInMonth() const;

    static short dayOfWeekOrder(short day, short month, short year);
    short dayOfWeekOrder() const;
    static std::string dayShortName(short dayOfWeekOrder);
    static std::string dayShortName(short day, short month, short year);
    std::string dayShortName() const;
    static std::string monthShortName(short monthNumber);
    std::string monthShortName() const;

    // Date Arithmetic Mechanics
    static short daysFromBeginningOfYear(short day, short month, short year);
    short daysFromBeginningOfYear() const;
    static CalendarDate getDateFromDayOrderInYear(short dateOrderInYear, short year);

    // Adding Time
    static CalendarDate addOneDay(const CalendarDate& date);
    void addOneDay();
    static CalendarDate addDays(const CalendarDate& date, short days);
    void addDays(short days);
    static CalendarDate increaseDateByOneWeek(const CalendarDate& date);
    void increaseDateByOneWeek();
    static CalendarDate increaseDateByXWeeks(short weeks, const CalendarDate& date);
    void increaseDateByXWeeks(short weeks);
    static CalendarDate increaseDateByOneMonth(const CalendarDate& date);
    void increaseDateByOneMonth();
    static CalendarDate increaseDateByXMonths(short months, const CalendarDate& date);
    void increaseDateByXMonths(short months);
    static CalendarDate increaseDateByOneYear(const CalendarDate& date);
    void increaseDateByOneYear();
    static CalendarDate increaseDateByXYears(short years, const CalendarDate& date);
    void increaseDateByXYears(short years);
    static CalendarDate increaseDateByOneDecade(const CalendarDate& date);
    void increaseDateByOneDecade();
    static CalendarDate increaseDateByXDecades(short decades, const CalendarDate& date);
    void increaseDateByXDecades(short decades);
    static CalendarDate increaseDateByOneCentury(const CalendarDate& date);
    void increaseDateByOneCentury();
    static CalendarDate increaseDateByOneMillennium(const CalendarDate& date);
    void increaseDateByOneMillennium();

    // Subtracting Time
    static CalendarDate decreaseDateByOneDay(const CalendarDate& date);
    void decreaseDateByOneDay();
    static CalendarDate decreaseDateByOneWeek(const CalendarDate& date);
    void decreaseDateByOneWeek();
    static CalendarDate decreaseDateByXWeeks(short weeks, const CalendarDate& date);
    void decreaseDateByXWeeks(short weeks);
    static CalendarDate decreaseDateByOneMonth(const CalendarDate& date);
    void decreaseDateByOneMonth();
    static CalendarDate decreaseDateByXMonths(short months, const CalendarDate& date);
    void decreaseDateByXMonths(short months);
    static CalendarDate decreaseDateByOneYear(const CalendarDate& date);
    void decreaseDateByOneYear();
    static CalendarDate decreaseDateByXYears(short years, const CalendarDate& date);
    void decreaseDateByXYears(short years);
    static CalendarDate decreaseDateByOneDecade(const CalendarDate& date);
    void decreaseDateByOneDecade();
    static CalendarDate decreaseDateByXDecades(short decades, const CalendarDate& date);
    void decreaseDateByXDecades(short decades);
    static CalendarDate decreaseDateByOneCentury(const CalendarDate& date);
    void decreaseDateByOneCentury();
    static CalendarDate decreaseDateByOneMillennium(const CalendarDate& date);
    void decreaseDateByOneMillennium();

    // Comparisons
    static bool isBefore(const CalendarDate& date1, const CalendarDate& date2);
    bool isBefore(const CalendarDate& date2) const;
    static bool isEqual(const CalendarDate& date1, const CalendarDate& date2);
    bool isEqual(const CalendarDate& date2) const;
    static bool isAfter(const CalendarDate& date1, const CalendarDate& date2);
    bool isAfter(const CalendarDate& date2) const;

    enum class CompareResult { Before = -1, Equal = 0, After = 1 };
    static CompareResult compare(const CalendarDate& date1, const CalendarDate& date2);
    CompareResult compare(const CalendarDate& date2) const;

    // Utility & Difference
    static void swapDates(CalendarDate& date1, CalendarDate& date2);
    static int getDifferenceInDays(const CalendarDate& date1, const CalendarDate& date2, bool includeEndDay = false);
    int getDifferenceInDays(const CalendarDate& date2, bool includeEndDay = false) const;
    static short calculateAgeInDays(const CalendarDate& dateOfBirth);

    // Business & Vacations
    static bool isLastDayInMonth(const CalendarDate& date);
    bool isLastDayInMonth() const;
    static bool isLastMonthInYear(short month);

    static bool isEndOfWeek(const CalendarDate& date);
    bool isEndOfWeek() const;
    static bool isWeekend(const CalendarDate& date);
    bool isWeekend() const;
    static bool isBusinessDay(const CalendarDate& date);
    bool isBusinessDay() const;

    static short daysUntilEndOfWeek(const CalendarDate& date);
    short daysUntilEndOfWeek() const;
    static short daysUntilEndOfMonth(const CalendarDate& date);
    short daysUntilEndOfMonth() const;
    static short daysUntilEndOfYear(const CalendarDate& date);
    short daysUntilEndOfYear() const;

    static short calculateBusinessDays(const CalendarDate& dateFrom, const CalendarDate& dateTo);
    static short calculateVacationDays(const CalendarDate& dateFrom, const CalendarDate& dateTo);
    static CalendarDate calculateVacationReturnDate(const CalendarDate& dateFrom, short vacationDays);

    // Decoupled I/O Friend Function
    friend std::ostream& operator<<(std::ostream& os, const CalendarDate& date);
};

// =================================================================
// IMPLEMENTATION SECTION
// =================================================================

inline CalendarDate::CalendarDate() {
    std::time_t t = std::time(nullptr);
    struct tm now;

#if defined(_WIN32)
    // The :: ensures we use the global C-runtime function
    (void)::localtime_s(&now, &t);
#else
    localtime_r(&t, &now);
#endif

    _day = static_cast<short>(now.tm_mday);
    _month = static_cast<short>(now.tm_mon + 1);
    _year = static_cast<short>(now.tm_year + 1900);
}

inline CalendarDate::CalendarDate(const std::string& stringDate) {
    std::vector<std::string> tokens = StringLib::split(stringDate, "/");
    if (tokens.size() == 3) {
        _day = static_cast<short>(std::stoi(tokens.at(0)));
        _month = static_cast<short>(std::stoi(tokens.at(1)));
        _year = static_cast<short>(std::stoi(tokens.at(2)));
    }
    else {
        throw std::invalid_argument("Date must be in dd/mm/yyyy format");
    }
}

inline CalendarDate::CalendarDate(short day, short month, short year){
    _day = day;
    _month = month;
    _year = year;
}

inline CalendarDate::CalendarDate(short dateOrderInYear, short year) {
    CalendarDate c = CalendarDate::getDateFromDayOrderInYear(dateOrderInYear, year);
    _day = c.getDay();
    _month = c.getMonth();
    _year = c.getYear();
}

inline std::ostream& operator<<(std::ostream& os, const CalendarDate& date) {

    os << (date._day < 10 ? "0" : "") << date._day << "/"
        << (date._month < 10 ? "0" : "") << date._month << "/"
        << date._year;
    return os;
}

// Getters & Setters
inline void CalendarDate::setDay(short day) {
    _day = day;
}

inline short CalendarDate::getDay() const {
    return _day;
}

inline void CalendarDate::setMonth(short month) {
    _month = month;
}

inline short CalendarDate::getMonth() const {
    return _month;
}

inline void CalendarDate::setYear(short year) {
    _year = year;
}

inline short CalendarDate::getYear() const {
    return _year;
}

// System Time & Validation
inline CalendarDate CalendarDate::getSystemDate() {
    return CalendarDate();
}

inline bool CalendarDate::isValidDate(const CalendarDate& date) {
    
    short month = date.getMonth();
    short year = date.getYear();
    short day = date.getDay();

    if (CalendarDate::isLastMonthInYear(month) || year < 1) return false;
    
    if (day > CalendarDate::numberOfDaysInMonth(month, year) || day < 1) return false;

    return true;
}

inline bool CalendarDate::isValid() const {
    return CalendarDate::isValidDate(CalendarDate(getDay(), getMonth(), getYear()));
}

// Output & Formatting
inline std::string CalendarDate::dateToString(const CalendarDate& date) {
    return (date.getDay() < 10 ? "0" : "") + std::to_string(date.getDay()) + "/" 
        + (date.getMonth() < 10 ? "0" : "") + std::to_string(date.getMonth()) + "/"
        + std::to_string(date.getYear());
}

inline std::string CalendarDate::dateToString() const {
    return CalendarDate::dateToString(CalendarDate(getDay(), getMonth(), getYear()));
}

inline std::string CalendarDate::generateMonthCalendar(short month, short year){
    std::ostringstream c;

    c << std::setw(20)
        << CalendarDate::monthShortName(month) << " "
        << year << "\n";

    for (short i = 0; i < 7; i++)
        c << std::setw(5) << CalendarDate::dayShortName(i);

    c << "\n";

    short totalDays = CalendarDate::numberOfDaysInMonth(month, year);
    short monthStartWeekday = CalendarDate::dayOfWeekOrder(1, month, year);

    for (short i = 0; i < monthStartWeekday; i++)
        c << std::setw(5) << "";

    for (short day = 1; day <= totalDays; day++)
    {
        c << std::setw(5) << day;

        if ((monthStartWeekday + day) % 7 == 0)
            c << "\n";
    }

    c << "\n";

    return c.str();
}

inline std::string CalendarDate::generateMonthCalendar() const {
    return CalendarDate::generateMonthCalendar(getMonth(), getYear());
}

inline std::string CalendarDate::generateYearCalendar(short year) {
    std::string c;
    for (short i = 1; i <= 12; i++) {
        c += CalendarDate::generateMonthCalendar(i, year);
    }
    return c;
}

inline std::string CalendarDate::generateYearCalendar() const {
    return CalendarDate::generateYearCalendar(getYear());
}

// Calendar Mechanics
inline bool CalendarDate::isLeapYear(short year) {
    return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

inline bool CalendarDate::isLeapYear() const {
    return CalendarDate::isLeapYear(getYear());
}

inline short CalendarDate::numberOfDaysInYear(short year) {
    return (CalendarDate::isLeapYear(year)) ? 366 : 365;
}

inline short CalendarDate::numberOfDaysInYear() const {
    return CalendarDate::numberOfDaysInYear(getYear());
}

inline short CalendarDate::numberOfHoursInYear(short year) {
    return CalendarDate::numberOfDaysInYear(year) * 24;
}

inline short CalendarDate::numberOfHoursInYear() const {
    return CalendarDate::numberOfHoursInYear(getYear());
}

inline int CalendarDate::numberOfMinutesInYear(short year) {
    return CalendarDate::numberOfHoursInYear(year) * 60;
}

inline int CalendarDate::numberOfMinutesInYear() const {
    return CalendarDate::numberOfMinutesInYear(getYear());
}

inline int CalendarDate::numberOfSecondsInYear(short year) {
    return CalendarDate::numberOfMinutesInYear(year) * 60;
}

inline int CalendarDate::numberOfSecondsInYear() const {
    return CalendarDate::numberOfSecondsInYear(getYear());
}

inline short CalendarDate::numberOfDaysInMonth(short month, short year) {
    if (month < 1 || month > 12) return 0;
    const short daysInMonthes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2 && CalendarDate::isLeapYear(year))? 29 : daysInMonthes[month - 1];
}

inline short CalendarDate::numberOfDaysInMonth() const {
    return CalendarDate::numberOfDaysInMonth(getMonth(), getYear());
}

inline short CalendarDate::numberOfHoursInMonth(short month, short year) {
    return CalendarDate::numberOfDaysInMonth(month, year) * 24;
}

inline short CalendarDate::numberOfHoursInMonth() const {
    return CalendarDate::numberOfHoursInMonth(getMonth(), getYear());
}

inline int numberOfMinutesInMonth(short month, short year) {
    return CalendarDate::numberOfHoursInMonth(month, year) * 60;
}

inline int CalendarDate::numberOfMinutesInMonth() const {
    return CalendarDate::numberOfMinutesInMonth(getMonth(), getYear());
}

inline int CalendarDate::numberOfSecondsInMonth(short month, short year) {
    return CalendarDate::numberOfMinutesInMonth(month, year) * 60;
}

inline int CalendarDate::numberOfSecondsInMonth() const {
    return CalendarDate::numberOfSecondsInMonth(getMonth(), getYear());
}

inline short CalendarDate::dayOfWeekOrder(short day, short month, short year) {
    /*
    * Gregorian
    * returns day of week order between 0 (Sunday) and 6 (Satarday)
    */
    short a = (14 - month) / 12;
    short y = year - a;
    short m = month + (12 * a) - 2;
    short d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12));
    d = d % 7;

    return d;
}

inline short CalendarDate::dayOfWeekOrder() const {
    return CalendarDate::dayOfWeekOrder(getDay(), getMonth(), getYear());
}

inline std::string CalendarDate::dayShortName(short dayOfWeekOrder) {
    if (dayOfWeekOrder < 0 || dayOfWeekOrder > 6) return "Invalid day order.";
    const std::string dayNames[7] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    return dayNames[dayOfWeekOrder].substr(0, 3);
}

inline std::string CalendarDate::dayShortName(short day, short month, short year) {
    return CalendarDate::dayShortName(CalendarDate::dayOfWeekOrder(day, month, year));
}

inline std::string CalendarDate::dayShortName() const {
    return CalendarDate::dayShortName(getDay(), getMonth(), getYear());
}

inline std::string CalendarDate::monthShortName(short monthNumber) {
    if (monthNumber < 1 || monthNumber > 12) return "Invalid month number";

    const std::string monthNames[12] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August", "September",
        "October", "November", "December"
    };
    return monthNames[monthNumber - 1].substr(0, 3);
}

inline std::string CalendarDate::monthShortName() const {
    return CalendarDate::monthShortName(getMonth());
}

// Date Arithmetic Mechanics
inline short CalendarDate::daysFromBeginningOfYear(short day, short month, short year) {
    short total = 0;
    for (short i = 1; i < month; i++) {
        total += CalendarDate::numberOfDaysInMonth(i, year);
    }
    total += day;
    return total;
}

inline short CalendarDate::daysFromBeginningOfYear() const {
    return CalendarDate::daysFromBeginningOfYear(getDay(), getMonth(), getYear());
}

inline CalendarDate CalendarDate::getDateFromDayOrderInYear(short dateOrderInYear, short year) {
    
    short month = 1;

    while (dateOrderInYear > CalendarDate::numberOfDaysInMonth(month, year))
    {
        dateOrderInYear -= CalendarDate::numberOfDaysInMonth(month, year);
        month++;
    }

    return CalendarDate(dateOrderInYear, month, year);
}

// Adding Time
inline CalendarDate CalendarDate::addOneDay(const CalendarDate& date) {

    if (CalendarDate::isLastDayInMonth(date)) {
        if (CalendarDate::isLastMonthInYear(date.getYear())) {
            return CalendarDate(1, 1, date.getYear() + 1);
        }
        else {
            return CalendarDate(1, date.getMonth() + 1, date.getYear());
        }
    }
    return CalendarDate(date.getDay() + 1, date.getMonth(), date.getYear());
}

inline void CalendarDate::addOneDay() {
    CalendarDate temp = CalendarDate::addOneDay(CalendarDate(getDay(), getMonth(), getYear()));
    setDay(temp.getDay());
    setMonth(temp.getMonth());
    setYear(temp.getYear());
}

inline CalendarDate addDays(const CalendarDate& date, short days) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    for (short i = 0; i < days; i++) {
        newDate.addOneDay();
    }
    return newDate;
}

inline void CalendarDate::addDays(short days) {
    CalendarDate newDate = CalendarDate::addDays(CalendarDate(getDay(), getMonth(), getYear()), days);
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByOneWeek(const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    return CalendarDate::addDays(newDate, 7);
}

inline void CalendarDate::increaseDateByOneWeek() {
    CalendarDate newDate = CalendarDate::increaseDateByOneWeek(CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByXWeeks(short weeks, const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    for (short i = 0; i < weeks; i++) {
        newDate.increaseDateByOneWeek();
    }
    return newDate;
}

inline void CalendarDate::increaseDateByXWeeks(short weeks) {
    CalendarDate newDate = CalendarDate::increaseDateByXWeeks(weeks, CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByOneMonth(const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());

    if (CalendarDate::isLastMonthInYear(newDate.getMonth())){
        newDate.setMonth(1);
        newDate.setYear(newDate.getYear() + 1);
    }
    else{
        newDate.setMonth(newDate.getMonth() + 1);
    }

    short daysInNewMonth = CalendarDate::numberOfDaysInMonth(newDate.getMonth(), newDate.getYear());

    if (newDate.getDay() > daysInNewMonth)
        newDate.setDay(daysInNewMonth);

    return newDate;
}

inline void CalendarDate::increaseDateByOneMonth() {
    CalendarDate newDate = CalendarDate::increaseDateByOneMonth(CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByXMonths(short months, const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    for (short i = 0; i < months; i++) {
        newDate.increaseDateByOneMonth();
    }
    return newDate;
}

inline void CalendarDate::increaseDateByXMonths(short months) {
    CalendarDate newDate = CalendarDate::increaseDateByXMonths(months, CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByOneYear(const CalendarDate& date) {
    
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    newDate.setYear(newDate.getYear() + 1);
    return newDate;
}

inline void CalendarDate::increaseDateByOneYear() {
    CalendarDate newDate = CalendarDate::increaseDateByOneYear(CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByXYears(short years, const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    for (short i = 0; i < years; i++) {
        newDate.increaseDateByOneYear();
    }
    return newDate;
}

inline void CalendarDate::increaseDateByXYears(short years) {
    CalendarDate newDate = CalendarDate::increaseDateByXYears(years, CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByOneDecade(const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    newDate.increaseDateByXYears(10);
    return newDate;
}

inline void CalendarDate::increaseDateByOneDecade() {
    CalendarDate newDate = CalendarDate::increaseDateByOneDecade(CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByXDecades(short decades, const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    for (short i = 0; i < decades; i++) {
        newDate.increaseDateByOneDecade();
    }
    return newDate;
}

inline void CalendarDate::increaseDateByXDecades(short decades) {
    CalendarDate newDate = CalendarDate::increaseDateByXDecades(decades, CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByOneCentury(const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    newDate.increaseDateByXDecades(10);
    return newDate;
}

inline void CalendarDate::increaseDateByOneCentury() {
    CalendarDate newDate = CalendarDate::increaseDateByOneCentury(CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}

inline CalendarDate CalendarDate::increaseDateByOneMillennium(const CalendarDate& date) {
    CalendarDate newDate(date.getDay(), date.getMonth(), date.getYear());
    for (short i = 0; i < 10; i++) {
        newDate.increaseDateByOneCentury();
    }
    return newDate;
}

inline void CalendarDate::increaseDateByOneMillennium() {
    CalendarDate newDate = CalendarDate::increaseDateByOneMillennium(CalendarDate(getDay(), getMonth(), getYear()));
    setDay(newDate.getDay());
    setMonth(newDate.getMonth());
    setYear(newDate.getYear());
}
