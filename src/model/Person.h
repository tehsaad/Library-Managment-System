#ifndef PERSON_H
#define PERSON_H

#include "CsvSerializable.h"
#include "Enums.h"

#include <string>
#include <utility>
#include <vector>

// =========================================================
// PERSON (abstract base class)
//
//            Person            <- abstract, cannot be created
//           |       |
//      Student    Faculty
//                    |
//                  Admin       <- Admin "is a" Faculty with more rights
//
// The rest of the program only holds Person pointers and asks
// questions like user->canManageBooks(). Each subclass answers
// differently (polymorphism), so there are no if (role == ...)
// checks scattered around the GUI.
// =========================================================

// A list of "label: value" pairs for showing on the profile screen
using DetailList = std::vector<std::pair<std::string, std::string>>;

class Person : public CsvSerializable
{
public:
    Person(const std::string &id,
           const std::string &username,
           const std::string &name,
           const std::string &password);

    ~Person() override = default;

    // ---- getters / setters (encapsulation) ----
    const std::string &getId() const;
    const std::string &getUsername() const;
    const std::string &getName() const;

    void setName(const std::string &name);
    void setUsername(const std::string &username);

    bool checkPassword(const std::string &attempt) const;
    void setPassword(const std::string &newPassword);   // throws if too short

    // ---- pure virtual: every subclass MUST say what it is ----
    virtual Role getRole() const = 0;

    // ---- permissions: default is "no", subclasses override ----
    virtual bool canManageBooks() const;        // add / edit / delete books
    virtual bool canIssueBooks() const;         // issue & return for anyone
    virtual bool canViewMembers() const;
    virtual bool canManageMembers() const;      // add / edit / delete students
    virtual bool canReviewVolunteers() const;
    virtual bool canViewHistory() const;

    // Information shown on the profile screen
    virtual DetailList profileDetails() const;

    std::string roleName() const;

    static const std::size_t MIN_PASSWORD_LENGTH = 3;

protected:
    // protected: subclasses need it when writing their CSV row,
    // but outside code must use checkPassword()/setPassword()
    std::string m_password;

private:
    std::string m_id;
    std::string m_username;
    std::string m_name;
};

#endif // PERSON_H
