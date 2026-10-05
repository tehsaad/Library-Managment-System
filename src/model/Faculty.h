#ifndef FACULTY_H
#define FACULTY_H

#include "Person.h"

#include <memory>

// =========================================================
// FACULTY
//
// Faculty.csv:  ID,Username,Name,Password,Role
// (Admins live in the same file with Role = Admin)
//
// Faculty can manage the book catalog, issue/return books,
// see members and read the history log.
// =========================================================

class Faculty : public Person
{
public:
    Faculty(const std::string &id,
            const std::string &username,
            const std::string &name,
            const std::string &password);

    // ---- CSV ----
    static std::vector<std::string> csvHeader();

    // Factory: reads the Role column and creates a Faculty OR an Admin
    static std::unique_ptr<Faculty> fromCsvRow(const std::vector<std::string> &row);

    std::vector<std::string> toCsvRow() const override;

    // ---- overrides ----
    Role getRole() const override;

    bool canManageBooks() const override;
    bool canIssueBooks() const override;
    bool canViewMembers() const override;
    bool canViewHistory() const override;
};

#endif // FACULTY_H
