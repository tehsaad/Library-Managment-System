#ifndef PROFILEDIALOG_H
#define PROFILEDIALOG_H

#include "FormDialog.h"

class Library;
class Person;
class QLineEdit;

// =========================================================
// PROFILE DIALOG
//
// Shows person.profileDetails() - a virtual function, so a
// Student sees their borrowing info and staff do not, without
// this dialog checking the role. Also lets the user change
// their password.
// =========================================================

class ProfileDialog : public FormDialog
{
    Q_OBJECT

public:
    ProfileDialog(Library &library, Person &user, QWidget *parent = nullptr);

    bool passwordChanged() const;

protected:
    QString submit() override;

private:
    Library &m_library;
    Person &m_user;
    bool m_passwordChanged;

    QLineEdit *m_current;
    QLineEdit *m_new;
    QLineEdit *m_confirm;
};

#endif // PROFILEDIALOG_H
