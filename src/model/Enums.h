#ifndef ENUMS_H
#define ENUMS_H

#include <string>

// =========================================================
// ENUMS
//
// Every "fixed list of choices" in the library is an
// enum class instead of a plain string. The compiler then
// catches typos like "Admn" for us.
// =========================================================

// Who is logged in
enum class Role
{
    Student,
    Faculty,
    Admin
};

// Has the student paid their library fee?
enum class FeeStatus
{
    Paid,
    Pending
};

// Is the book on the shelf or with someone?
enum class BookStatus
{
    Available,
    Issued
};

// Is the loan still open?
enum class LoanStatus
{
    Active,
    Returned
};

// Volunteer applications go through a review
enum class ApplicationStatus
{
    Pending,
    Approved,
    Rejected
};

// Everything that can appear in the history log
enum class ActionType
{
    Login,
    Logout,
    AddBook,
    EditBook,
    RemoveBook,
    IssueBook,
    ReturnBook,
    AddMember,
    EditMember,
    RemoveMember,
    ChangePassword,
    VolunteerApplied,
    VolunteerReviewed
};


// =========================================================
// ENUM <-> TEXT
//
// CSV files and the GUI need text, so each enum has a
// toString() (function overloading: same name, different
// parameter type) and a fromString() that throws
// std::invalid_argument for unknown text.
// =========================================================

namespace EnumText
{
std::string toString(Role role);
std::string toString(FeeStatus status);
std::string toString(BookStatus status);
std::string toString(LoanStatus status);
std::string toString(ApplicationStatus status);
std::string toString(ActionType action);

Role roleFromString(const std::string &text);
FeeStatus feeStatusFromString(const std::string &text);
BookStatus bookStatusFromString(const std::string &text);
LoanStatus loanStatusFromString(const std::string &text);
ApplicationStatus applicationStatusFromString(const std::string &text);
ActionType actionFromString(const std::string &text);
}

#endif // ENUMS_H
