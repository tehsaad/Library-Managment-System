#include "IssueBookDialog.h"
#include "core/Library.h"
#include "ui/Theme.h"

#include <QComboBox>
#include <QCompleter>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

namespace
{
// A combo box you can type into to filter a long list
QComboBox *searchableCombo(const QString &placeholder)
{
    auto *combo = new QComboBox;
    combo->setEditable(true);
    combo->setInsertPolicy(QComboBox::NoInsert);
    combo->completer()->setFilterMode(Qt::MatchContains);
    combo->completer()->setCompletionMode(QCompleter::PopupCompletion);
    combo->lineEdit()->setPlaceholderText(placeholder);
    combo->setMinimumWidth(320);
    return combo;
}
}


IssueBookDialog::IssueBookDialog(Library &library, const Person &user, int preselectedBookId, QWidget *parent)
    : FormDialog("Issue a book",
                 "Lend an available book to a student for " +
                     QString::number(Loan::LOAN_PERIOD_DAYS) + " days.",
                 "Issue book",
                 parent)
    , m_library(library)
    , m_user(user)
{
    m_book = searchableCombo("Type a title...");
    for (const Book *book : library.searchBooks("", "", true))
    {
        m_book->addItem(Theme::qs(book->getTitle() + "  -  " + book->getAuthor()), book->getId());
    }

    m_student = searchableCombo("Type a name or ID...");
    for (const Student *student : library.students())
    {
        m_student->addItem(Theme::qs(student->getName() + "  (" + student->getId() + ")"),
                           Theme::qs(student->getId()));
    }

    m_book->setCurrentIndex(preselectedBookId > 0 ? m_book->findData(preselectedBookId) : -1);
    m_student->setCurrentIndex(-1);

    m_summary = Theme::label("", "muted");

    form()->addRow("Book", m_book);
    form()->addRow("Student", m_student);
    body()->addWidget(m_summary);

    connect(m_book, &QComboBox::currentIndexChanged, this, &IssueBookDialog::updateSummary);
    connect(m_student, &QComboBox::currentIndexChanged, this, &IssueBookDialog::updateSummary);
    updateSummary();
}

int IssueBookDialog::selectedIndex(QComboBox *combo)
{
    // With an editable combo, trust the typed text over the old index
    return combo->findText(combo->currentText());
}

void IssueBookDialog::updateSummary()
{
    const int studentIndex = selectedIndex(m_student);
    const Date due = Date::today().addDays(Loan::LOAN_PERIOD_DAYS);

    if (studentIndex < 0)
    {
        m_summary->setText("Due back on " + Theme::qs(due.toString()) + ".");
        return;
    }

    const Student *student =
        m_library.findStudent(Theme::str(m_student->itemData(studentIndex).toString()));
    if (student == nullptr)
    {
        return;
    }

    std::string reason;
    QString text = Theme::qs(student->getName()) + " has " +
                   QString::number(student->getBooksBorrowed()) + " of " +
                   QString::number(Student::MAX_BOOKS) + " books. ";

    text += student->canBorrow(reason)
                ? "Due back on " + Theme::qs(due.toString()) + "."
                : Theme::qs(reason);

    m_summary->setText(text);
}

QString IssueBookDialog::submit()
{
    const int bookIndex = selectedIndex(m_book);
    const int studentIndex = selectedIndex(m_student);

    if (bookIndex < 0)
    {
        return "Choose a book from the list.";
    }
    if (studentIndex < 0)
    {
        return "Choose a student from the list.";
    }

    try
    {
        const Loan &loan = m_library.issueBook(m_book->itemData(bookIndex).toInt(),
                                               Theme::str(m_student->itemData(studentIndex).toString()),
                                               m_user);

        m_resultMessage = "Issued \"" + Theme::qs(m_library.bookTitle(loan.getBookId())) +
                          "\" to " + Theme::qs(m_library.studentName(loan.getStudentId())) +
                          ". Due " + Theme::qs(loan.getDueDate().toString()) + ".";
    }
    catch (const std::exception &e)
    {
        return e.what();
    }

    return QString();
}

QString IssueBookDialog::resultMessage() const
{
    return m_resultMessage;
}
