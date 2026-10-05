#ifndef ADMIN_H
#define ADMIN_H

#include "Faculty.h"

// =========================================================
// ADMIN
//
// Multilevel inheritance: Admin -> Faculty -> Person.
// An Admin can do everything Faculty can (inherited), and
// additionally manages members and volunteer applications.
// =========================================================

class Admin : public Faculty
{
public:
    Admin(const std::string &id,
          const std::string &username,
          const std::string &name,
          const std::string &password);

    Role getRole() const override;

    bool canManageMembers() const override;
    bool canReviewVolunteers() const override;
};

#endif // ADMIN_H
