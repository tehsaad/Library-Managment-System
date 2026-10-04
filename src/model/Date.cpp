#include "Date.h"

#include <cstdio>
#include <ctime>
#include <stdexcept>


// =========================================================
// CONSTRUCTORS
// =========================================================

Date::Date()
    : m_year(0), m_month(0), m_day(0)
{
}

Date::Date(int year, int month, int day)
    : m_year(year), m_month(month), m_day(day)
{
    if (year < 1 || month < 1 || month > 12 ||
        day < 1 || day > daysInMonth(year, month))
    {
        throw std::invalid_argument("Invalid date");
    }
}


// =========================================================
// FACTORIES
// =========================================================

Date Date::today()
{
    std::time_t now = std::time(nullptr);
    std::tm local = *std::localtime(&now);

    return Date(local.tm_year + 1900, local.tm_mon + 1, local.tm_mday);
}

Date Date::fromString(const std::string &text)
{
    if (text.empty())
    {
        return Date();
    }

    int year = 0, month = 0, day = 0;
    char extra = 0;

    // Expect exactly YYYY-MM-DD and nothing after it
    if (std::sscanf(text.c_str(), "%d-%d-%d%c", &year, &month, &day, &extra) != 3)
    {
        throw std::invalid_argument("Bad date \"" + text + "\" (expected YYYY-MM-DD)");
    }

    return Date(year, month, day);
}

std::string Date::currentTimestamp()
{
    std::time_t now = std::time(nullptr);
    std::tm local = *std::localtime(&now);

    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", &local);
    return buffer;
}


// =========================================================
// GETTERS
// =========================================================

bool Date::isValid() const { return m_year > 0; }
int Date::year() const { return m_year; }
int Date::month() const { return m_month; }
int Date::day() const { return m_day; }

std::string Date::toString() const
{
    if (!isValid())
    {
        return "";
    }

    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", m_year, m_month, m_day);
    return buffer;
}


// =========================================================
// ARITHMETIC
// =========================================================

Date Date::addDays(int days) const
{
    return fromDayNumber(toDayNumber() + days);
}

int Date::daysUntil(const Date &other) const
{
    return static_cast<int>(other.toDayNumber() - toDayNumber());
}


// =========================================================
// OPERATORS
// =========================================================

bool Date::operator==(const Date &other) const
{
    return m_year == other.m_year && m_month == other.m_month && m_day == other.m_day;
}

bool Date::operator!=(const Date &other) const { return !(*this == other); }
bool Date::operator<(const Date &other) const { return toDayNumber() < other.toDayNumber(); }
bool Date::operator<=(const Date &other) const { return !(other < *this); }
bool Date::operator>(const Date &other) const { return other < *this; }
bool Date::operator>=(const Date &other) const { return !(*this < other); }
int Date::operator-(const Date &other) const { return other.daysUntil(*this); }


// =========================================================
// HELPERS
//
// Turning a date into "number of days since 1970-01-01"
// makes adding days and comparing dates simple.
// (Algorithm by Howard Hinnant, years start in March so the
// leap day is the last day of the "year".)
// =========================================================

long Date::toDayNumber() const
{
    long y = m_year;
    const long m = m_month;
    const long d = m_day;

    if (m <= 2)
    {
        y -= 1;
    }

    const long era = y / 400;
    const long yearOfEra = y - era * 400;
    const long monthFromMarch = (m + 9) % 12;
    const long dayOfYear = (153 * monthFromMarch + 2) / 5 + d - 1;
    const long dayOfEra = yearOfEra * 365 + yearOfEra / 4 - yearOfEra / 100 + dayOfYear;

    return era * 146097 + dayOfEra - 719468;
}

Date Date::fromDayNumber(long dayNumber)
{
    dayNumber += 719468;

    const long era = dayNumber / 146097;
    const long dayOfEra = dayNumber - era * 146097;
    const long yearOfEra =
        (dayOfEra - dayOfEra / 1460 + dayOfEra / 36524 - dayOfEra / 146096) / 365;
    const long dayOfYear = dayOfEra - (365 * yearOfEra + yearOfEra / 4 - yearOfEra / 100);
    const long monthFromMarch = (5 * dayOfYear + 2) / 153;

    const int day = static_cast<int>(dayOfYear - (153 * monthFromMarch + 2) / 5 + 1);
    const int month = static_cast<int>(monthFromMarch < 10 ? monthFromMarch + 3 : monthFromMarch - 9);
    const int year = static_cast<int>(yearOfEra + era * 400 + (month <= 2 ? 1 : 0));

    return Date(year, month, day);
}

bool Date::isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int Date::daysInMonth(int year, int month)
{
    static const int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }
    return days[month - 1];
}
