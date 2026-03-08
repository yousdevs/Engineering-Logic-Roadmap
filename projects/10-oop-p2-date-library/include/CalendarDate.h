#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>


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