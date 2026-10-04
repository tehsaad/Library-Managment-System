#include "BooksPage.h"
#include "core/Library.h"
#include "ui/dialogs/BookDialog.h"
#include "ui/dialogs/IssueBookDialog.h"

#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>


BooksPage::BooksPage(Library &library, Person &user, QWidget *parent)
    : BasePage(library, user, "Catalog",
               user.canManageBooks() ? "Search, add and lend books."
                                     : "Find a book and borrow it for " +
                                           QString::number(Loan::LOAN_PERIOD_DAYS) + " days.",
               parent)
{
    // ---- filters ----
    m_search = new QLineEdit;
    m_search->setPlaceholderText("Search title, author, genre or ISBN");
    m_search->setClearButtonEnabled(true);
    m_search->setMinimumWidth(280);

    m_genre = new QComboBox;
    m_genre->setMinimumWidth(160);

    m_availableOnly = new QCheckBox("Available only");

    QHBoxLayout *toolbar = addToolbar();
    toolbar->addWidget(m_search, 1);
    toolbar->addWidget(m_genre);
    toolbar->addWidget(m_availableOnly);
    toolbar->addStretch();

    // ---- action buttons depend on what this user may do ----
    if (m_user.canManageBooks())
    {
        m_remove = Theme::button("Remove", "danger");
        m_edit = Theme::button("Edit");
        m_add = Theme::button("Add book");
        toolbar->addWidget(m_remove);
        toolbar->addWidget(m_edit);
        toolbar->addWidget(m_add);

        connect(m_add, &QPushButton::clicked, this, &BooksPage::addBook);
        connect(m_edit, &QPushButton::clicked, this, &BooksPage::editBook);
        connect(m_remove, &QPushButton::clicked, this, &BooksPage::removeBook);
    }

    if (m_user.canIssueBooks())
    {
        m_issue = Theme::button("Issue book", "primary");
        toolbar->addWidget(m_issue);
        connect(m_issue, &QPushButton::clicked, this, &BooksPage::issueBook);
    }
    else if (m_user.getRole() == Role::Student)
    {
        m_borrow = Theme::button("Borrow", "primary");
        toolbar->addWidget(m_borrow);
        connect(m_borrow, &QPushButton::clicked, this, &BooksPage::borrowBook);
    }

    // ---- table ----
    m_table = createTable({ "ID", "Title", "Author", "Genre", "Year", "ISBN", "Status" });
    content()->addWidget(m_table, 1);

    m_count = Theme::label("", "small");
    content()->addWidget(m_count);

    connect(m_search, &QLineEdit::textChanged, this, &BooksPage::refresh);
    connect(m_genre, &QComboBox::currentIndexChanged, this, &BooksPage::refresh);
    connect(m_availableOnly, &QCheckBox::toggled, this, &BooksPage::refresh);
    connect(m_table, &QTableWidget::itemSelectionChanged, this, &BooksPage::updateButtons);
    connect(m_table, &QTableWidget::cellDoubleClicked, this, [this] {
        if (m_edit) editBook();
        else if (m_borrow) borrowBook();
    });

    refreshGenres();
}

void BooksPage::refreshGenres()
{
    const QString current = m_genre->currentText();

    m_genre->blockSignals(true);   // do not refresh once per added item
    m_genre->clear();
    m_genre->addItem("All genres", QString());
    for (const std::string &genre : m_library.genres())
    {
        m_genre->addItem(Theme::qs(genre), Theme::qs(genre));
    }
    const int index = m_genre->findText(current);
    m_genre->setCurrentIndex(index >= 0 ? index : 0);
    m_genre->blockSignals(false);
}

void BooksPage::refresh()
{
    const QString keep = selectedKey(m_table);

    const auto books = m_library.searchBooks(Theme::str(m_search->text()),
                                             Theme::str(m_genre->currentData().toString()),
                                             m_availableOnly->isChecked());

    beginFill(m_table, static_cast<int>(books.size()));
    for (int row = 0; row < static_cast<int>(books.size()); row++)
    {
        const Book *book = books[row];

        m_table->setItem(row, 0, numberCell(book->getId()));
        m_table->setItem(row, 1, cell(Theme::qs(book->getTitle())));
        m_table->setItem(row, 2, cell(Theme::qs(book->getAuthor())));
        m_table->setItem(row, 3, cell(Theme::qs(book->getGenre())));
        m_table->setItem(row, 4, numberCell(book->getYear()));
        m_table->setItem(row, 5, cell(Theme::qs(book->getIsbn())));
        m_table->setItem(row, 6, cell(Theme::qs(EnumText::toString(book->getStatus())),
                                      book->isAvailable() ? Tone::Good : Tone::Warning));
        setRowKey(m_table, row, QString::number(book->getId()));
    }
    endFill(m_table);

    selectKey(m_table, keep);
    m_count->setText("Showing " + QString::number(books.size()) + " of " +
                     QString::number(m_library.books().size()) + " books");
    updateButtons();
}

int BooksPage::selectedBookId() const
{
    return selectedKey(m_table).toInt();   // 0 when nothing is selected
}

void BooksPage::updateButtons()
{
    const Book *book = m_library.findBook(selectedBookId());

    if (m_edit) m_edit->setEnabled(book != nullptr);
    if (m_remove) m_remove->setEnabled(book != nullptr && book->isAvailable());
    if (m_borrow) m_borrow->setEnabled(book != nullptr && book->isAvailable());
}


// =========================================================
// ACTIONS
// =========================================================

void BooksPage::addBook()
{
    BookDialog dialog(m_library, m_user, nullptr, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refreshGenres();
        refresh();
        flash("Book added to the catalog.");
    }
}

void BooksPage::editBook()
{
    const Book *book = m_library.findBook(selectedBookId());
    if (book == nullptr)
    {
        return;
    }

    BookDialog dialog(m_library, m_user, book, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refreshGenres();
        refresh();
        flash("Book details saved.");
    }
}

void BooksPage::removeBook()
{
    const Book *book = m_library.findBook(selectedBookId());
    if (book == nullptr)
    {
        return;
    }

    const QString title = Theme::qs(book->getTitle());
    if (!confirm("Remove book", "Remove \"" + title + "\" from the catalog?\nThis cannot be undone."))
    {
        return;
    }

    try
    {
        m_library.removeBook(book->getId(), m_user);
        refreshGenres();
        refresh();
        flash("Removed \"" + title + "\".");
    }
    catch (const std::exception &e)
    {
        showError(e.what());
    }
}

void BooksPage::issueBook()
{
    IssueBookDialog dialog(m_library, m_user, selectedBookId(), this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refresh();
        flash(dialog.resultMessage());
    }
}

void BooksPage::borrowBook()
{
    const Book *book = m_library.findBook(selectedBookId());
    if (book == nullptr)
    {
        return;
    }

    const QString title = Theme::qs(book->getTitle());
    const QString due = Theme::qs(Date::today().addDays(Loan::LOAN_PERIOD_DAYS).toString());

    if (!confirm("Borrow book", "Borrow \"" + title + "\"?\nIt will be due back on " + due + "."))
    {
        return;
    }

    try
    {
        m_library.issueBook(book->getId(), m_user.getId(), m_user);
        refresh();
        flash("You borrowed \"" + title + "\". Please return it by " + due + ".");
    }
    catch (const std::exception &e)
    {
        showError(e.what());
    }
}
