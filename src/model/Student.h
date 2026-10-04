#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

// =========================================================
// STUDENT
//
// Users.csv:
// ID,Username,Name,Password,Books_Borrowed,Warnings,Fee_Status
// =========================================================

class Student : public Person
{
public:
    static const int MAX_BOOKS = 5;
    static const int MAX_WARNINGS = 3;

    Student(const std::string &id,
            const std::string &username,
            const std::string &name,
            const std::string &password,
            int booksBorrowed = 0,
            int warnings = 0,
            FeeStatus feeStatus = FeeStatus::Paid);

    // ---- CSV ----
    static std::vector<std::string> csvHeader();
    static Student fromCsvRow(const std::vector<std::string> &row);
    std::vector<std::string> toCsvRow() const override;

    // ---- overrides ----
    Role getRole() const override;
    DetailList profileDetails() const override;

    // ---- student-only data ----
    int getBooksBorrowed() const;
    int getWarnings() const;
    FeeStatus getFeeStatus() const;

    void setBooksBorrowed(int count);
    void setWarnings(int warnings);
    void setFeeStatus(FeeStatus status);

    void borrowOne();
    void returnOne();
    void addWarning();

    // Can this student take another book? If not, "reason" says why.
    bool canBorrow(std::string &reason) const;

private:
    int m_booksBorrowed;
    int m_warnings;
    FeeStatus m_feeStatus;
};

#endif // STUDENT_H
