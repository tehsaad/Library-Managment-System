#ifndef ISSUEBOOKDIALOG_H
#define ISSUEBOOKDIALOG_H

#include "FormDialog.h"

class Library;
class Person;
class QComboBox;
class QLabel;

// =========================================================
// ISSUE BOOK DIALOG - staff lends a book to a student
// =========================================================

class IssueBookDialog : public FormDialog
{
    Q_OBJECT

public:
    // preselectedBookId: the book selected in the catalog (0 = none)
    IssueBookDialog(Library &library, const Person &user, int preselectedBookId, QWidget *parent = nullptr);

    QString resultMessage() const;

protected:
    QString submit() override;

private:
    void updateSummary();
    static int selectedIndex(QComboBox *combo);

    Library &m_library;
    const Person &m_user;

    QComboBox *m_book;
    QComboBox *m_student;
    QLabel *m_summary;
    QString m_resultMessage;
};

#endif // ISSUEBOOKDIALOG_H
