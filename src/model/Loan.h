#ifndef LOAN_H
#define LOAN_H

#include "CsvSerializable.h"
#include "Date.h"
#include "Enums.h"

#include <string>

// =========================================================
// LOAN
//
// One book given to one student.
// Loans.csv:  LoanID,BookID,StudentID,IssueDate,DueDate,ReturnDate,Status
// =========================================================

class Loan : public CsvSerializable
{
public:
    static const int LOAN_PERIOD_DAYS = 14;

    Loan();
    Loan(const std::string &id,
         int bookId,
         const std::string &studentId,
         const Date &issueDate,
         const Date &dueDate,
         const Date &returnDate = Date(),
         LoanStatus status = LoanStatus::Active);

    // ---- CSV ----
    static std::vector<std::string> csvHeader();
    static Loan fromCsvRow(const std::vector<std::string> &row);
    std::vector<std::string> toCsvRow() const override;

    // ---- getters ----
    const std::string &getId() const;
    int getBookId() const;
    const std::string &getStudentId() const;
    const Date &getIssueDate() const;
    const Date &getDueDate() const;
    const Date &getReturnDate() const;
    LoanStatus getStatus() const;

    bool isActive() const;
    bool isOverdue(const Date &today) const;
    int daysOverdue(const Date &today) const;   // 0 when not overdue

    void markReturned(const Date &returnDate);

private:
    std::string m_id;
    int m_bookId;
    std::string m_studentId;
    Date m_issueDate;
    Date m_dueDate;
    Date m_returnDate;
    LoanStatus m_status;
};

#endif // LOAN_H
