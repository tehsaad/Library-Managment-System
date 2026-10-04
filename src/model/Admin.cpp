#include "Admin.h"


Admin::Admin(const std::string &id,
             const std::string &username,
             const std::string &name,
             const std::string &password)
    : Faculty(id, username, name, password)
{
}

Role Admin::getRole() const { return Role::Admin; }

bool Admin::canManageMembers() const { return true; }
bool Admin::canReviewVolunteers() const { return true; }
