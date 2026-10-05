#include "Student.h"
#include "storage/CsvParser.h"

#include <stdexcept>


Student::Student(const std::string &id,
                 const std::string &username,
                 const std::string &name,
                 const std::string &password,
                 int booksBorrowed,
                 int warnings,
                 FeeStatus feeStatus)
    : Person(id, username, name, password)      // call the base constructor
    , m_booksBorrowed(booksBorrowed)
    , m_warnings(warnings)
    , m_feeStatus(feeStatus)
{
}


// =========================================================
// CSV
// =========================================================

std::vector<std::string> Student::csvHeader()
{
    return { "ID", "Username", "Name", "Password", "Books_Borrowed", "Warnings", "Fee_Status" };
}

Student Student::fromCsvRow(const std::vector<std::string> &row)
{
    CsvParser::requireColumns(row, 7, "student");

    return Student(row[0],
                   row[1],
                   row[2],
                   row[3],
                   CsvParser::toInt(row[4], "Books_Borrowed"),
                   CsvParser::toInt(row[5], "Warnings"),
                   EnumText::feeStatusFromString(row[6]));
}

std::vector<std::string> Student::toCsvRow() const
{
    return { getId(),
             getUsername(),
             getName(),
             m_password,
             std::to_string(m_booksBorrowed),
             std::to_string(m_warnings),
             EnumText::toString(m_feeStatus) };
}


// =========================================================
// OVERRIDES
// =========================================================

Role Student::getRole() const
{
    return Role::Student;
}

DetailList Student::profileDetails() const
{
    // Start with what every Person has, then add student info
    DetailList details = Person::profileDetails();

    details.push_back({ "Books borrowed",
                        std::to_string(m_booksBorrowed) + " of " + std::to_string(MAX_BOOKS) });
    details.push_back({ "Warnings",
                        std::to_string(m_warnings) + " of " + std::to_string(MAX_WARNINGS) });
    details.push_back({ "Fee status", EnumText::toString(m_feeStatus) });

    return details;
}


// =========================================================
// STUDENT DATA
// =========================================================

int Student::getBooksBorrowed() const { return m_booksBorrowed; }
int Student::getWarnings() const { return m_warnings; }
FeeStatus Student::getFeeStatus() const { return m_feeStatus; }

void Student::setBooksBorrowed(int count)
{
    m_booksBorrowed = count < 0 ? 0 : count;
}

void Student::setWarnings(int warnings)
{
    if (warnings < 0)
    {
        throw std::invalid_argument("Warnings cannot be negative.");
    }
    m_warnings = warnings;
}

void Student::setFeeStatus(FeeStatus status)
{
    m_feeStatus = status;
}

void Student::borrowOne()
{
    m_booksBorrowed++;
}

void Student::returnOne()
{
    if (m_booksBorrowed > 0)
    {
        m_booksBorrowed--;
    }
}

void Student::addWarning()
{
    m_warnings++;
}

bool Student::canBorrow(std::string &reason) const
{
    if (m_feeStatus == FeeStatus::Pending)
    {
        reason = getName() + " has a pending library fee.";
        return false;
    }

    if (m_warnings >= MAX_WARNINGS)
    {
        reason = getName() + " has " + std::to_string(m_warnings) +
                 " warnings and is blocked from borrowing.";
        return false;
    }

    if (m_booksBorrowed >= MAX_BOOKS)
    {
        reason = getName() + " already has the maximum of " +
                 std::to_string(MAX_BOOKS) + " books.";
        return false;
    }

    reason.clear();
    return true;
}
