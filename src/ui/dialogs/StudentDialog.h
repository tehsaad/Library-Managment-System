#ifndef STUDENTDIALOG_H
#define STUDENTDIALOG_H

#include "FormDialog.h"

#include <string>

class Library;
class Person;
class Student;
class QComboBox;
class QLineEdit;
class QSpinBox;

// =========================================================
// STUDENT DIALOG - admin adds or edits a member
// =========================================================

class StudentDialog : public FormDialog
{
    Q_OBJECT

public:
    StudentDialog(Library &library, const Person &user, const Student *existing, QWidget *parent = nullptr);

protected:
    QString submit() override;

private:
    Library &m_library;
    const Person &m_user;
    std::string m_studentId;    // empty when adding

    QLineEdit *m_name;
    QLineEdit *m_username;
    QLineEdit *m_password;
    QComboBox *m_fee;
    QSpinBox *m_warnings;
};

#endif // STUDENTDIALOG_H
