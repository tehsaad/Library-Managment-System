#ifndef BOOKSPAGE_H
#define BOOKSPAGE_H

#include "BasePage.h"

class QCheckBox;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

// =========================================================
// BOOKS PAGE (the catalog)
//
// Everyone can search. Students can borrow; staff can add,
// edit, remove and issue. Which buttons exist is decided by
// asking the user object (canManageBooks(), canIssueBooks()).
// =========================================================

class BooksPage : public BasePage
{
    Q_OBJECT

public:
    BooksPage(Library &library, Person &user, QWidget *parent = nullptr);

    void refresh() override;

private slots:
    void addBook();
    void editBook();
    void removeBook();
    void issueBook();
    void borrowBook();
    void updateButtons();

private:
    void refreshGenres();
    int selectedBookId() const;

    QLineEdit *m_search;
    QComboBox *m_genre;
    QCheckBox *m_availableOnly;
    QLabel *m_count;
    QTableWidget *m_table;

    QPushButton *m_borrow = nullptr;
    QPushButton *m_issue = nullptr;
    QPushButton *m_add = nullptr;
    QPushButton *m_edit = nullptr;
    QPushButton *m_remove = nullptr;
};

#endif // BOOKSPAGE_H
