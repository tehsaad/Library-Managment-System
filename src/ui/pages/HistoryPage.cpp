#include "HistoryPage.h"
#include "core/Library.h"
#include "storage/CsvParser.h"

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>


HistoryPage::HistoryPage(Library &library, Person &user, QWidget *parent)
    : BasePage(library, user, "History",
               "Every sign-in, loan and change, newest first. Saved in History.csv.",
               parent)
{
    m_search = new QLineEdit;
    m_search->setPlaceholderText("Search user or details");
    m_search->setClearButtonEnabled(true);
    m_search->setMinimumWidth(280);

    // Fill the filter straight from the ActionType enum
    m_action = new QComboBox;
    m_action->addItem("All actions", -1);
    const ActionType actions[] = {
        ActionType::Login, ActionType::Logout, ActionType::AddBook, ActionType::EditBook,
        ActionType::RemoveBook, ActionType::IssueBook, ActionType::ReturnBook,
        ActionType::AddMember, ActionType::EditMember, ActionType::RemoveMember,
        ActionType::ChangePassword, ActionType::VolunteerApplied, ActionType::VolunteerReviewed
    };
    for (ActionType action : actions)
    {
        m_action->addItem(readable(Theme::qs(EnumText::toString(action))), static_cast<int>(action));
    }

    QHBoxLayout *toolbar = addToolbar();
    toolbar->addWidget(m_search, 1);
    toolbar->addWidget(m_action);
    toolbar->addStretch();

    m_table = createTable({ "Time", "User", "Action", "Details" });
    content()->addWidget(m_table, 1);

    m_count = Theme::label("", "small");
    content()->addWidget(m_count);

    connect(m_search, &QLineEdit::textChanged, this, &HistoryPage::refresh);
    connect(m_action, &QComboBox::currentIndexChanged, this, &HistoryPage::refresh);
}

// "VolunteerReviewed" -> "Volunteer reviewed"
QString HistoryPage::readable(const QString &actionName)
{
    QString text;
    for (int i = 0; i < actionName.size(); i++)
    {
        const QChar c = actionName[i];
        if (i > 0 && c.isUpper())
        {
            text += ' ';
            text += c.toLower();
        }
        else
        {
            text += c;
        }
    }
    return text;
}

void HistoryPage::refresh()
{
    const std::string query = Theme::str(m_search->text());
    const int actionFilter = m_action->currentData().toInt();
    const auto &history = m_library.history();

    // Walk backwards so the newest entry is on top
    std::vector<const HistoryEntry *> shown;
    for (auto it = history.rbegin(); it != history.rend(); ++it)
    {
        if (actionFilter >= 0 && static_cast<int>(it->getAction()) != actionFilter)
        {
            continue;
        }
        if (!query.empty() &&
            !CsvParser::containsIgnoreCase(it->getUsername(), query) &&
            !CsvParser::containsIgnoreCase(it->getDetails(), query))
        {
            continue;
        }
        shown.push_back(&*it);
    }

    beginFill(m_table, static_cast<int>(shown.size()));
    for (int row = 0; row < static_cast<int>(shown.size()); row++)
    {
        const HistoryEntry *entry = shown[row];
        m_table->setItem(row, 0, cell(Theme::qs(entry->getTimestamp())));
        m_table->setItem(row, 1, cell(Theme::qs(entry->getUsername())));
        m_table->setItem(row, 2, cell(readable(Theme::qs(EnumText::toString(entry->getAction())))));
        m_table->setItem(row, 3, cell(Theme::qs(entry->getDetails())));
    }
    endFill(m_table);
    m_table->setSortingEnabled(false);   // keep newest first

    m_count->setText(QString::number(shown.size()) + " of " +
                     QString::number(history.size()) + " entries");
}
