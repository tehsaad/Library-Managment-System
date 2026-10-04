#include "Loan.h"
#include "storage/CsvParser.h"


Loan::Loan()
    : m_bookId(0), m_status(LoanStatus::Active)
{
}

Loan::Loan(const std::string &id,
           int bookId,
           const std::string &studentId,
           const Date &issueDate,
           const Date &dueDate,
           const Date &returnDate,
           LoanStatus status)
    : m_id(id)
    , m_bookId(bookId)
    , m_studentId(studentId)
    , m_issueDate(issueDate)
    , m_dueDate(dueDate)
    , m_returnDate(returnDate)
    , m_status(status)
{
}


// =========================================================
// CSV
// =========================================================

std::vector<std::string> Loan::csvHeader()
{
    return { "LoanID", "BookID", "StudentID", "IssueDate", "DueDate", "ReturnDate", "Status" };
}

Loan Loan::fromCsvRow(const std::vector<std::string> &row)
{
    CsvParser::requireColumns(row, 7, "loan");

    return Loan(row[0],
                CsvParser::toInt(row[1], "BookID"),
                row[2],
                Date::fromString(row[3]),
                Date::fromString(row[4]),
                Date::fromString(row[5]),
                EnumText::loanStatusFromString(row[6]));
}

std::vector<std::string> Loan::toCsvRow() const
{
    return { m_id,
             std::to_string(m_bookId),
             m_studentId,
             m_issueDate.toString(),
             m_dueDate.toString(),
             m_returnDate.toString(),
             EnumText::toString(m_status) };
}


// =========================================================
// GETTERS
// =========================================================

const std::string &Loan::getId() const { return m_id; }
int Loan::getBookId() const { return m_bookId; }
const std::string &Loan::getStudentId() const { return m_studentId; }
const Date &Loan::getIssueDate() const { return m_issueDate; }
const Date &Loan::getDueDate() const { return m_dueDate; }
const Date &Loan::getReturnDate() const { return m_returnDate; }
LoanStatus Loan::getStatus() const { return m_status; }

bool Loan::isActive() const
{
    return m_status == LoanStatus::Active;
}

bool Loan::isOverdue(const Date &today) const
{
    return isActive() && today > m_dueDate;
}

int Loan::daysOverdue(const Date &today) const
{
    return isOverdue(today) ? today - m_dueDate : 0;
}

void Loan::markReturned(const Date &returnDate)
{
    m_returnDate = returnDate;
    m_status = LoanStatus::Returned;
}
