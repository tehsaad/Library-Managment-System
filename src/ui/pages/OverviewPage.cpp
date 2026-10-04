#include "OverviewPage.h"
#include "core/Library.h"
#include "ui/widgets/StatCard.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QTime>
#include <QVBoxLayout>

#include <algorithm>


OverviewPage::OverviewPage(Library &library, Person &user, QWidget *parent)
    : BasePage(library, user, "", "", parent)
    , m_isStudent(user.getRole() == Role::Student)
{
    const QStringList titles = m_isStudent
        ? QStringList { "Books borrowed", "Warnings", "Library fee", "Next due date" }
        : QStringList { "Books in catalog", "On loan", "Members", "Volunteer applications" };

    auto *cards = new QHBoxLayout;
    cards->setSpacing(14);
    for (int i = 0; i < 4; i++)
    {
        m_cards[i] = new StatCard(titles[i]);
        cards->addWidget(m_cards[i]);
    }
    content()->addLayout(cards);

    m_notice = Theme::label("", "notice");
    m_notice->hide();
    content()->addWidget(m_notice);

    // ---- two tables side by side ----
    m_leftHeading = Theme::label("", "heading");
    m_rightHeading = Theme::label("", "heading");

    if (m_isStudent)
    {
        m_leftTable = createTable({ "Book", "Issued", "Due", "Status" });
        m_rightTable = createTable({ "Book", "Returned" });
    }
    else
    {
        m_leftTable = createTable({ "Student", "Book", "Due", "Late" });
        m_rightTable = createTable({ "Time", "User", "Details" });
    }

    auto *left = new QVBoxLayout;
    left->addWidget(m_leftHeading);
    left->addWidget(m_leftTable);

    auto *right = new QVBoxLayout;
    right->addWidget(m_rightHeading);
    right->addWidget(m_rightTable);

    auto *tables = new QHBoxLayout;
    tables->setSpacing(18);
    tables->addLayout(left, 3);
    tables->addLayout(right, 2);

    content()->addSpacing(8);
    content()->addLayout(tables, 1);
}

QString OverviewPage::greeting()
{
    const int hour = QTime::currentTime().hour();

    if (hour < 12) return "Good morning";
    if (hour < 17) return "Good afternoon";
    return "Good evening";
}

void OverviewPage::refresh()
{
    setTitle(greeting() + ", " + Theme::qs(m_user.getName()));

    if (m_isStudent)
    {
        refreshStudent();
    }
    else
    {
        refreshStaff();
    }
}


// =========================================================
// STUDENT VIEW
// =========================================================

void OverviewPage::refreshStudent()
{
    const Student *student = m_library.findStudent(m_user.getId());
    if (student == nullptr)
    {
        return;
    }

    const Date today = Date::today();
    setSubtitle("Here is where your borrowing stands today, " + Theme::qs(today.toString()) + ".");

    // ---- collect this student's loans ----
    std::vector<const Loan *> active;
    std::vector<const Loan *> returned;
    for (const Loan *loan : m_library.loansForStudent(student->getId()))
    {
        (loan->isActive() ? active : returned).push_back(loan);
    }

    std::sort(active.begin(), active.end(), [](const Loan *a, const Loan *b) {
        return a->getDueDate() < b->getDueDate();
    });
    std::sort(returned.begin(), returned.end(), [](const Loan *a, const Loan *b) {
        return a->getReturnDate() > b->getReturnDate();
    });

    // ---- cards ----
    m_cards[0]->setValue(QString::number(student->getBooksBorrowed()),
                         "of " + QString::number(Student::MAX_BOOKS) + " allowed");
    m_cards[1]->setValue(QString::number(student->getWarnings()),
                         "blocked at " + QString::number(Student::MAX_WARNINGS));
    m_cards[2]->setValue(Theme::qs(EnumText::toString(student->getFeeStatus())),
                         student->getFeeStatus() == FeeStatus::Paid ? "Nothing to pay"
                                                                    : "Please visit the desk");
    if (active.empty())
    {
        m_cards[3]->setValue("—", "No books on loan");
    }
    else
    {
        const int days = today.daysUntil(active.front()->getDueDate());
        m_cards[3]->setValue(Theme::qs(active.front()->getDueDate().toString()),
                             days < 0 ? QString::number(-days) + " days overdue"
                                      : days == 0 ? "Due today"
                                                  : "In " + QString::number(days) + " days");
    }

    // ---- notice when borrowing is blocked ----
    std::string reason;
    const bool canBorrow = student->canBorrow(reason);
    m_notice->setText("You cannot borrow right now. " + Theme::qs(reason));
    m_notice->setVisible(!canBorrow);

    // ---- tables ----
    m_leftHeading->setText("On loan");
    beginFill(m_leftTable, static_cast<int>(active.size()));
    for (int row = 0; row < static_cast<int>(active.size()); row++)
    {
        const Loan *loan = active[row];
        const int days = today.daysUntil(loan->getDueDate());

        m_leftTable->setItem(row, 0, cell(Theme::qs(m_library.bookTitle(loan->getBookId()))));
        m_leftTable->setItem(row, 1, cell(Theme::qs(loan->getIssueDate().toString())));
        m_leftTable->setItem(row, 2, cell(Theme::qs(loan->getDueDate().toString())));
        m_leftTable->setItem(row, 3,
                             days < 0 ? cell("Overdue", Tone::Bad)
                             : days <= 3 ? cell("Due soon", Tone::Warning)
                                         : cell("On time", Tone::Good));
    }
    endFill(m_leftTable);

    m_rightHeading->setText("Recently returned");
    const int shown = std::min<int>(8, static_cast<int>(returned.size()));
    beginFill(m_rightTable, shown);
    for (int row = 0; row < shown; row++)
    {
        m_rightTable->setItem(row, 0, cell(Theme::qs(m_library.bookTitle(returned[row]->getBookId()))));
        m_rightTable->setItem(row, 1, cell(Theme::qs(returned[row]->getReturnDate().toString())));
    }
    endFill(m_rightTable);
}


// =========================================================
// STAFF VIEW
// =========================================================

void OverviewPage::refreshStaff()
{
    const LibraryStatistics stats = m_library.statistics();
    const Date today = Date::today();

    setSubtitle("Signed in as " + Theme::qs(m_user.roleName()) + ". Library summary for " +
                Theme::qs(today.toString()) + ".");

    m_cards[0]->setValue(QString::number(stats.totalBooks),
                         QString::number(stats.availableBooks) + " available");
    m_cards[1]->setValue(QString::number(stats.activeLoans),
                         stats.overdueLoans == 0 ? "None overdue"
                                                 : QString::number(stats.overdueLoans) + " overdue");
    m_cards[2]->setValue(QString::number(stats.totalStudents),
                         QString::number(stats.pendingFees) + " with pending fees");
    m_cards[3]->setValue(QString::number(stats.pendingApplications), "waiting for review");

    m_notice->setVisible(stats.overdueLoans > 0);
    m_notice->setText(QString::number(stats.overdueLoans) +
                      " book(s) are overdue. Returning them late adds a warning and a fee.");

    // ---- overdue loans, most overdue first ----
    std::vector<const Loan *> overdue;
    for (const Loan &loan : m_library.loans())
    {
        if (loan.isOverdue(today))
        {
            overdue.push_back(&loan);
        }
    }
    std::sort(overdue.begin(), overdue.end(), [](const Loan *a, const Loan *b) {
        return a->getDueDate() < b->getDueDate();
    });

    m_leftHeading->setText("Overdue");
    beginFill(m_leftTable, static_cast<int>(overdue.size()));
    for (int row = 0; row < static_cast<int>(overdue.size()); row++)
    {
        const Loan *loan = overdue[row];
        m_leftTable->setItem(row, 0, cell(Theme::qs(m_library.studentName(loan->getStudentId()))));
        m_leftTable->setItem(row, 1, cell(Theme::qs(m_library.bookTitle(loan->getBookId()))));
        m_leftTable->setItem(row, 2, cell(Theme::qs(loan->getDueDate().toString())));
        m_leftTable->setItem(row, 3, cell(QString::number(loan->daysOverdue(today)) + " days", Tone::Bad));
    }
    endFill(m_leftTable);

    // ---- latest history entries ----
    const auto &history = m_library.history();
    const int shown = std::min<int>(10, static_cast<int>(history.size()));

    m_rightHeading->setText("Recent activity");
    beginFill(m_rightTable, shown);
    for (int row = 0; row < shown; row++)
    {
        const HistoryEntry &entry = history[history.size() - 1 - row];
        m_rightTable->setItem(row, 0, cell(Theme::qs(entry.getTimestamp())));
        m_rightTable->setItem(row, 1, cell(Theme::qs(entry.getUsername())));
        m_rightTable->setItem(row, 2, cell(Theme::qs(entry.getDetails())));
    }
    endFill(m_rightTable);
    m_rightTable->setSortingEnabled(false);   // keep newest first
}
