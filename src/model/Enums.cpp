#include "Enums.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace
{
// Lower-case copy so "admin", "Admin" and "ADMIN" all match
std::string lower(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

[[noreturn]] void unknown(const std::string &what, const std::string &text)
{
    throw std::invalid_argument("Unknown " + what + ": \"" + text + "\"");
}
}

namespace EnumText
{

// =========================================================
// TO STRING
// =========================================================

std::string toString(Role role)
{
    switch (role)
    {
    case Role::Student: return "Student";
    case Role::Faculty: return "Faculty";
    case Role::Admin:   return "Admin";
    }
    return "";
}

std::string toString(FeeStatus status)
{
    switch (status)
    {
    case FeeStatus::Paid:    return "Paid";
    case FeeStatus::Pending: return "Pending";
    }
    return "";
}

std::string toString(BookStatus status)
{
    switch (status)
    {
    case BookStatus::Available: return "Available";
    case BookStatus::Issued:    return "Issued";
    }
    return "";
}

std::string toString(LoanStatus status)
{
    switch (status)
    {
    case LoanStatus::Active:   return "Active";
    case LoanStatus::Returned: return "Returned";
    }
    return "";
}

std::string toString(ApplicationStatus status)
{
    switch (status)
    {
    case ApplicationStatus::Pending:  return "Pending";
    case ApplicationStatus::Approved: return "Approved";
    case ApplicationStatus::Rejected: return "Rejected";
    }
    return "";
}

std::string toString(ActionType action)
{
    switch (action)
    {
    case ActionType::Login:             return "Login";
    case ActionType::Logout:            return "Logout";
    case ActionType::AddBook:           return "AddBook";
    case ActionType::EditBook:          return "EditBook";
    case ActionType::RemoveBook:        return "RemoveBook";
    case ActionType::IssueBook:         return "IssueBook";
    case ActionType::ReturnBook:        return "ReturnBook";
    case ActionType::AddMember:         return "AddMember";
    case ActionType::EditMember:        return "EditMember";
    case ActionType::RemoveMember:      return "RemoveMember";
    case ActionType::ChangePassword:    return "ChangePassword";
    case ActionType::VolunteerApplied:  return "VolunteerApplied";
    case ActionType::VolunteerReviewed: return "VolunteerReviewed";
    }
    return "";
}


// =========================================================
// FROM STRING
// =========================================================

Role roleFromString(const std::string &text)
{
    const std::string t = lower(text);
    if (t == "student") return Role::Student;
    if (t == "faculty") return Role::Faculty;
    if (t == "admin")   return Role::Admin;
    unknown("role", text);
}

FeeStatus feeStatusFromString(const std::string &text)
{
    const std::string t = lower(text);
    if (t == "paid")    return FeeStatus::Paid;
    if (t == "pending") return FeeStatus::Pending;
    unknown("fee status", text);
}

BookStatus bookStatusFromString(const std::string &text)
{
    const std::string t = lower(text);
    if (t == "available") return BookStatus::Available;
    if (t == "issued")    return BookStatus::Issued;
    unknown("book status", text);
}

LoanStatus loanStatusFromString(const std::string &text)
{
    const std::string t = lower(text);
    if (t == "active")   return LoanStatus::Active;
    if (t == "returned") return LoanStatus::Returned;
    unknown("loan status", text);
}

ApplicationStatus applicationStatusFromString(const std::string &text)
{
    const std::string t = lower(text);
    if (t == "pending")  return ApplicationStatus::Pending;
    if (t == "approved") return ApplicationStatus::Approved;
    if (t == "rejected") return ApplicationStatus::Rejected;
    unknown("application status", text);
}

ActionType actionFromString(const std::string &text)
{
    // Loop over every value instead of writing 13 if-statements
    const ActionType all[] = {
        ActionType::Login, ActionType::Logout, ActionType::AddBook,
        ActionType::EditBook, ActionType::RemoveBook, ActionType::IssueBook,
        ActionType::ReturnBook, ActionType::AddMember, ActionType::EditMember,
        ActionType::RemoveMember, ActionType::ChangePassword,
        ActionType::VolunteerApplied, ActionType::VolunteerReviewed
    };

    for (ActionType action : all)
    {
        if (lower(toString(action)) == lower(text))
        {
            return action;
        }
    }
    unknown("action", text);
}

}
