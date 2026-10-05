#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include "FormDialog.h"

class Book;
class Library;
class Person;
class QComboBox;
class QLineEdit;
class QSpinBox;

// =========================================================
// BOOK DIALOG - add a new book or edit an existing one
// =========================================================

class BookDialog : public FormDialog
{
    Q_OBJECT

public:
    // existing == nullptr  ->  "Add book" mode
    BookDialog(Library &library, const Person &user, const Book *existing, QWidget *parent = nullptr);

protected:
    QString submit() override;

private:
    Library &m_library;
    const Person &m_user;
    int m_bookId;           // 0 when adding

    QLineEdit *m_title;
    QLineEdit *m_author;
    QComboBox *m_genre;
    QSpinBox *m_year;
    QLineEdit *m_isbn;
};

#endif // BOOKDIALOG_H
