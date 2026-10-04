#ifndef DATE_H
#define DATE_H

#include <string>

// =========================================================
// DATE
//
// A small value class for calendar dates (no time of day).
// Shows encapsulation (year/month/day are private and always
// valid) and operator overloading (==, <, - ...).
//
// Text format in the CSV files: YYYY-MM-DD
// A default-constructed Date is "empty" (e.g. a loan that
// has not been returned yet).
// =========================================================

class Date
{
public:
    Date();                                 // empty date
    Date(int year, int month, int day);     // throws if invalid

    static Date today();
    static Date fromString(const std::string &text);   // "" -> empty date
    static std::string currentTimestamp();             // "YYYY-MM-DD HH:MM"

    bool isValid() const;

    int year() const;
    int month() const;
    int day() const;

    std::string toString() const;           // "" for an empty date

    Date addDays(int days) const;
    int daysUntil(const Date &other) const; // other - this, in days

    // ---- operator overloading ----
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    bool operator<(const Date &other) const;
    bool operator<=(const Date &other) const;
    bool operator>(const Date &other) const;
    bool operator>=(const Date &other) const;
    int operator-(const Date &other) const; // difference in days

private:
    long toDayNumber() const;
    static Date fromDayNumber(long dayNumber);

    static bool isLeapYear(int year);
    static int daysInMonth(int year, int month);

    int m_year;
    int m_month;
    int m_day;
};

#endif // DATE_H
