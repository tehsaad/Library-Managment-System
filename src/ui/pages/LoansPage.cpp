#include "LoansPage.h"
#include "core/Library.h"
#include "storage/CsvParser.h"
#include "ui/dialogs/IssueBookDialog.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

#include <algorithm>


LoansPage::LoansPage(Library &library, Person &user, QWidget *parent)
    : BasePage(library, user,
               user.canIssueBooks() ? "Loans" : "My books",
               user.canIssueBooks() ? "Every book that is out, and everything returned."
                                    : "Books you have borrowed. Return on time to avoid warnings.",
               parent)
    , m_ownLoansOnly(!user.canIssueBooks())
{
    m_filter = new QComboBox;
    m_filter->addItem("On loan", static_cast<int>(LoanFilter::Current));
    m_filter->addItem("Overdue", static_cast<int>(LoanFilter::Overdue));
    m_filter->addItem("Returned", static_cast<int>(LoanFilter::Returned));
    m_filter->addItem("All loans", static_cast<int>(LoanFilter::All));

    QHBoxLayout *toolbar = addToolbar();

    if (!m_ownLoansOnly)
    {
        m_search = new QLineEdit;
        m_search->setPlaceholderText("Search student or book");
        m_search->setClearButtonEnabled(true);
        m_search->setMinimumWidth(260);
        toolbar->addWidget(m_search, 1);
        connect(m_search, &QLineEdit::textChanged, this, &LoansPage::refresh);
    }

    toolbar->addWidget(m_filter);
    toolbar->addStretch();

    m_return = Theme::button(m_ownLoansOnly ? "Return book" : "Mark returned");
    toolbar->addWidget(m_return);
    connect(m_return, &QPushButton::clicked, this, &LoansPage::returnSelected);

    if (!m_ownLoansOnly)
    {
        m_issue = Theme::button("Issue book", "primary");
        toolbar->addWidget(m_issue);
        connect(m_issue, &QPushButton::clicked, this, &LoansPage::issueBook);
    }

    QStringList headers = { "Loan", "Book", "Student", "Issued", "Due", "Returned", "Status" };
    if (m_ownLoansOnly)
    {
        headers.removeAt(2);    // a student does not need their own name in every row
    }
    m_table = createTable(headers);
    content()->addWidget(m_table, 1);

    m_count = Theme::label("", "small");
    content()->addWidget(m_count);

    connect(m_filter, &QComboBox::currentIndexChanged, this, &LoansPage::refresh);
    connect(m_table, &QTableWidget::itemSelectionChanged, this, &LoansPage::updateButtons);
}

bool LoansPage::passesFilter(const Loan &loan) const
{
    const auto filter = static_cast<LoanFilter>(m_filter->currentData().toInt());

    switch (filter)
    {
    case LoanFilter::Current:  return loan.isActive();
    case LoanFilter::Overdue:  return loan.isOverdue(Date::today());
    case LoanFilter::Returned: return !loan.isActive();
    case LoanFilter::All:      return true;
    }
    return true;
}

void LoansPage::refresh()
{
    const QString keep = selectedKey(m_table);
    const Date today = Date::today();
    const std::string query = m_search ? Theme::str(m_search->text()) : "";

    // ---- pick the loans to show ----
    std::vector<const Loan *> loans;
    for (const Loan &loan : m_library.loans())
    {
        if (m_ownLoansOnly && loan.getStudentId() != m_user.getId())
        {
            continue;
        }
        if (!passesFilter(loan))
        {
            continue;
        }
        if (!query.empty() &&
            !CsvParser::containsIgnoreCase(m_library.studentName(loan.getStudentId()), query) &&
            !CsvParser::containsIgnoreCase(loan.getStudentId(), query) &&
            !CsvParser::containsIgnoreCase(m_library.bookTitle(loan.getBookId()), query))
        {
            continue;
        }
        loans.push_back(&loan);
    }

    // Newest first
    std::reverse(loans.begin(), loans.end());

    // ---- fill the table ----
    beginFill(m_table, static_cast<int>(loans.size()));
    for (int row = 0; row < static_cast<int>(loans.size()); row++)
    {
        const Loan *loan = loans[row];
        int column = 0;

        m_table->setItem(row, column++, cell(Theme::qs(loan->getId())));
        m_table->setItem(row, column++, cell(Theme::qs(m_library.bookTitle(loan->getBookId()))));
        if (!m_ownLoansOnly)
        {
            m_table->setItem(row, column++, cell(Theme::qs(m_library.studentName(loan->getStudentId()))));
        }
        m_table->setItem(row, column++, cell(Theme::qs(loan->getIssueDate().toString())));
        m_table->setItem(row, column++, cell(Theme::qs(loan->getDueDate().toString())));
        m_table->setItem(row, column++, cell(Theme::qs(loan->getReturnDate().toString())));

        QTableWidgetItem *status;
        if (!loan->isActive())
        {
            status = cell("Returned");
        }
        else if (loan->isOverdue(today))
        {
            status = cell("Overdue " + QString::number(loan->daysOverdue(today)) + " days", Tone::Bad);
        }
        else
        {
            const int daysLeft = today.daysUntil(loan->getDueDate());
            status = daysLeft == 0 ? cell("Due today", Tone::Warning)
                                   : cell(QString::number(daysLeft) + " days left",
                                          daysLeft <= 3 ? Tone::Warning : Tone::Good);
        }
        m_table->setItem(row, column, status);

        setRowKey(m_table, row, Theme::qs(loan->getId()));
    }
    endFill(m_table);

    selectKey(m_table, keep);
    m_count->setText(QString::number(loans.size()) + (loans.size() == 1 ? " loan" : " loans"));
    updateButtons();
}

void LoansPage::updateButtons()
{
    const QString loanId = selectedKey(m_table);
    bool active = false;

    for (const Loan &loan : m_library.loans())
    {
        if (Theme::qs(loan.getId()) == loanId)
        {
            active = loan.isActive();
        }
    }
    m_return->setEnabled(active);
}


// =========================================================
// ACTIONS
// =========================================================

void LoansPage::returnSelected()
{
    const QString loanId = selectedKey(m_table);
    if (loanId.isEmpty())
    {
        return;
    }

    try
    {
        const int daysLate = m_library.returnBook(Theme::str(loanId), m_user);
        refresh();

        if (daysLate > 0)
        {
            flash("Returned " + QString::number(daysLate) +
                      " days late. A warning was added and the library fee is now pending.",
                  true);
        }
        else
        {
            flash("Book returned on time. Thank you!");
        }
    }
    catch (const std::exception &e)
    {
        showError(e.what());
    }
}

void LoansPage::issueBook()
{
    IssueBookDialog dialog(m_library, m_user, 0, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refresh();
        flash(dialog.resultMessage());
    }
}
