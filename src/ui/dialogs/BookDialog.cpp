#include "BookDialog.h"
#include "core/Library.h"
#include "ui/Theme.h"

#include <QComboBox>
#include <QDate>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>


BookDialog::BookDialog(Library &library, const Person &user, const Book *existing, QWidget *parent)
    : FormDialog(existing ? "Edit book" : "Add a book",
                 existing ? "Update the catalog details. The loan status is not changed here."
                          : "The new book is added to the catalog as available.",
                 existing ? "Save changes" : "Add book",
                 parent)
    , m_library(library)
    , m_user(user)
    , m_bookId(existing ? existing->getId() : 0)
{
    m_title = new QLineEdit;
    m_title->setPlaceholderText("e.g. The Silent Forest");

    m_author = new QLineEdit;
    m_author->setPlaceholderText("e.g. John Smith");

    m_genre = new QComboBox;
    m_genre->setEditable(true);     // pick an existing genre or type a new one
    for (const std::string &genre : library.genres())
    {
        m_genre->addItem(Theme::qs(genre));
    }

    m_year = new QSpinBox;
    m_year->setRange(1000, 2100);
    m_year->setValue(QDate::currentDate().year());

    m_isbn = new QLineEdit;
    m_isbn->setPlaceholderText("13 digits (optional)");

    if (existing != nullptr)
    {
        m_title->setText(Theme::qs(existing->getTitle()));
        m_author->setText(Theme::qs(existing->getAuthor()));
        m_genre->setCurrentText(Theme::qs(existing->getGenre()));
        m_year->setValue(existing->getYear());
        m_isbn->setText(Theme::qs(existing->getIsbn()));
    }
    else
    {
        m_genre->setCurrentIndex(-1);
    }

    form()->addRow("Title", m_title);
    form()->addRow("Author", m_author);
    form()->addRow("Genre", m_genre);
    form()->addRow("Year", m_year);
    form()->addRow("ISBN", m_isbn);
}

QString BookDialog::submit()
{
    Book book(m_bookId,
              Theme::str(m_title->text()),
              Theme::str(m_author->text()),
              Theme::str(m_genre->currentText()),
              m_year->value(),
              Theme::str(m_isbn->text()));

    try
    {
        if (m_bookId == 0)
        {
            m_library.addBook(book, m_user);
        }
        else
        {
            m_library.updateBook(book, m_user);
        }
    }
    catch (const std::exception &e)
    {
        return e.what();
    }

    return QString();
}
