#include "MembersPage.h"
#include "core/Library.h"
#include "ui/dialogs/StudentDialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>


MembersPage::MembersPage(Library &library, Person &user, QWidget *parent)
    : BasePage(library, user, "Members",
               user.canManageMembers() ? "Add students, update fees and clear warnings."
                                       : "Student accounts. Only an administrator can change them.",
               parent)
{
    m_search = new QLineEdit;
    m_search->setPlaceholderText("Search by name, username or ID");
    m_search->setClearButtonEnabled(true);
    m_search->setMinimumWidth(280);

    QHBoxLayout *toolbar = addToolbar();
    toolbar->addWidget(m_search, 1);
    toolbar->addStretch();

    if (m_user.canManageMembers())
    {
        m_remove = Theme::button("Remove", "danger");
        m_edit = Theme::button("Edit");
        m_add = Theme::button("Add member", "primary");
        toolbar->addWidget(m_remove);
        toolbar->addWidget(m_edit);
        toolbar->addWidget(m_add);

        connect(m_add, &QPushButton::clicked, this, &MembersPage::addMember);
        connect(m_edit, &QPushButton::clicked, this, &MembersPage::editMember);
        connect(m_remove, &QPushButton::clicked, this, &MembersPage::removeMember);
    }

    m_table = createTable({ "ID", "Username", "Name", "Books", "Warnings", "Fee" });
    content()->addWidget(m_table, 1);

    m_count = Theme::label("", "small");
    content()->addWidget(m_count);

    connect(m_search, &QLineEdit::textChanged, this, &MembersPage::refresh);
    connect(m_table, &QTableWidget::itemSelectionChanged, this, &MembersPage::updateButtons);
    connect(m_table, &QTableWidget::cellDoubleClicked, this, [this] {
        if (m_edit) editMember();
    });
}

void MembersPage::refresh()
{
    const QString keep = selectedKey(m_table);
    const auto students = m_library.searchStudents(Theme::str(m_search->text()));

    beginFill(m_table, static_cast<int>(students.size()));
    for (int row = 0; row < static_cast<int>(students.size()); row++)
    {
        const Student *student = students[row];
        const bool blocked = student->getWarnings() >= Student::MAX_WARNINGS;
        const bool paid = student->getFeeStatus() == FeeStatus::Paid;

        m_table->setItem(row, 0, cell(Theme::qs(student->getId())));
        m_table->setItem(row, 1, cell(Theme::qs(student->getUsername())));
        m_table->setItem(row, 2, cell(Theme::qs(student->getName())));
        m_table->setItem(row, 3, numberCell(student->getBooksBorrowed()));

        QTableWidgetItem *warnings = numberCell(student->getWarnings());
        if (blocked)
        {
            warnings->setForeground(Theme::color(Tone::Bad));
        }
        m_table->setItem(row, 4, warnings);

        m_table->setItem(row, 5, cell(Theme::qs(EnumText::toString(student->getFeeStatus())),
                                      paid ? Tone::Good : Tone::Warning));
        setRowKey(m_table, row, Theme::qs(student->getId()));
    }
    endFill(m_table);

    selectKey(m_table, keep);
    m_count->setText(QString::number(students.size()) + " members");
    updateButtons();
}

void MembersPage::updateButtons()
{
    const bool selected = !selectedKey(m_table).isEmpty();

    if (m_edit) m_edit->setEnabled(selected);
    if (m_remove) m_remove->setEnabled(selected);
}


// =========================================================
// ACTIONS
// =========================================================

void MembersPage::addMember()
{
    StudentDialog dialog(m_library, m_user, nullptr, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refresh();
        flash("Member added.");
    }
}

void MembersPage::editMember()
{
    const Student *student = m_library.findStudent(Theme::str(selectedKey(m_table)));
    if (student == nullptr)
    {
        return;
    }

    StudentDialog dialog(m_library, m_user, student, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        refresh();
        flash("Member updated.");
    }
}

void MembersPage::removeMember()
{
    const Student *student = m_library.findStudent(Theme::str(selectedKey(m_table)));
    if (student == nullptr)
    {
        return;
    }

    const QString name = Theme::qs(student->getName());
    if (!confirm("Remove member", "Remove " + name + "'s account?\nThis cannot be undone."))
    {
        return;
    }

    try
    {
        m_library.removeStudent(student->getId(), m_user);
        refresh();
        flash("Removed " + name + ".");
    }
    catch (const std::exception &e)
    {
        showError(e.what());
    }
}
