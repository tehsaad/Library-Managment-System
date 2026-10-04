#include "Person.h"

#include <stdexcept>


Person::Person(const std::string &id,
               const std::string &username,
               const std::string &name,
               const std::string &password)
    : m_password(password)
    , m_id(id)
    , m_username(username)
    , m_name(name)
{
}


// =========================================================
// GETTERS / SETTERS
// =========================================================

const std::string &Person::getId() const { return m_id; }
const std::string &Person::getUsername() const { return m_username; }
const std::string &Person::getName() const { return m_name; }

void Person::setName(const std::string &name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Name cannot be empty.");
    }
    m_name = name;
}

void Person::setUsername(const std::string &username)
{
    if (username.empty())
    {
        throw std::invalid_argument("Username cannot be empty.");
    }
    m_username = username;
}

bool Person::checkPassword(const std::string &attempt) const
{
    return attempt == m_password;
}

void Person::setPassword(const std::string &newPassword)
{
    if (newPassword.size() < MIN_PASSWORD_LENGTH)
    {
        throw std::invalid_argument("Password must be at least " +
                                    std::to_string(MIN_PASSWORD_LENGTH) +
                                    " characters.");
    }
    m_password = newPassword;
}


// =========================================================
// PERMISSIONS (default: not allowed)
// =========================================================

bool Person::canManageBooks() const { return false; }
bool Person::canIssueBooks() const { return false; }
bool Person::canViewMembers() const { return false; }
bool Person::canManageMembers() const { return false; }
bool Person::canReviewVolunteers() const { return false; }
bool Person::canViewHistory() const { return false; }


// =========================================================
// PROFILE
// =========================================================

DetailList Person::profileDetails() const
{
    return {
        { "ID", m_id },
        { "Username", m_username },
        { "Name", m_name },
        { "Role", roleName() }
    };
}

std::string Person::roleName() const
{
    // getRole() is virtual, so this works for every subclass
    return EnumText::toString(getRole());
}
