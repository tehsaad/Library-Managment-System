#include "Faculty.h"
#include "Admin.h"
#include "storage/CsvParser.h"

#include <stdexcept>


Faculty::Faculty(const std::string &id,
                 const std::string &username,
                 const std::string &name,
                 const std::string &password)
    : Person(id, username, name, password)
{
}


// =========================================================
// CSV
// =========================================================

std::vector<std::string> Faculty::csvHeader()
{
    return { "ID", "Username", "Name", "Password", "Role" };
}

std::unique_ptr<Faculty> Faculty::fromCsvRow(const std::vector<std::string> &row)
{
    CsvParser::requireColumns(row, 5, "faculty");

    const Role role = EnumText::roleFromString(row[4]);

    if (role == Role::Admin)
    {
        return std::make_unique<Admin>(row[0], row[1], row[2], row[3]);
    }
    if (role == Role::Faculty)
    {
        return std::make_unique<Faculty>(row[0], row[1], row[2], row[3]);
    }

    throw std::invalid_argument("Students belong in Users.csv, not Faculty.csv");
}

std::vector<std::string> Faculty::toCsvRow() const
{
    // getRole() is virtual: an Admin object writes "Admin" here
    return { getId(), getUsername(), getName(), m_password, roleName() };
}


// =========================================================
// OVERRIDES
// =========================================================

Role Faculty::getRole() const { return Role::Faculty; }

bool Faculty::canManageBooks() const { return true; }
bool Faculty::canIssueBooks() const { return true; }
bool Faculty::canViewMembers() const { return true; }
bool Faculty::canViewHistory() const { return true; }
