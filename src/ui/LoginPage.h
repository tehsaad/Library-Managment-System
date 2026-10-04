#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include "model/Enums.h"

#include <QWidget>

class Library;
class Person;
class QCheckBox;
class QLabel;
class QLineEdit;

// =========================================================
// LOGIN PAGE
//
// One page for all three roles; setRole() changes the text.
// On success it emits loggedIn(user) with the Person object
// the Library found (a Student, Faculty or Admin).
// =========================================================

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(Library &library, QWidget *parent = nullptr);

    void setRole(Role role);

signals:
    void loggedIn(Person *user);
    void backRequested();

private slots:
    void attemptLogin();

private:
    Library &m_library;
    Role m_role;

    QLabel *m_eyebrow;
    QLabel *m_hint;
    QLineEdit *m_username;
    QLineEdit *m_password;
    QCheckBox *m_showPassword;
    QLabel *m_error;
};

#endif // LOGINPAGE_H
