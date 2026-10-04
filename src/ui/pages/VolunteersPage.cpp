#include "VolunteersPage.h"
#include "core/Library.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>


VolunteersPage::VolunteersPage(Library &library, Person &user, QWidget *parent)
    : BasePage(library, user, "Volunteers",
               "People who applied from the welcome screen. Approve or reject each one.",
               parent)
{
    m_pendingOnly = new QCheckBox("Waiting for review only");
    m_pendingOnly->setChecked(true);

    m_reject = Theme::button("Reject", "danger");
    m_approve = Theme::button("Approve", "primary");

    QHBoxLayout *toolbar = addToolbar();
    toolbar->addWidget(m_pendingOnly);
    toolbar->addStretch();
    toolbar->addWidget(m_reject);
    toolbar->addWidget(m_approve);

    m_table = createTable({ "ID", "Name", "Email", "Phone", "Availability", "Applied", "Status" });
    content()->addWidget(m_table, 1);

    // The "why" text is long, so it is shown under the table
    m_reason = Theme::label("", "muted");
    content()->addWidget(m_reason);

    connect(m_pendingOnly, &QCheckBox::toggled, this, &VolunteersPage::refresh);
    connect(m_table, &QTableWidget::itemSelectionChanged, this, &VolunteersPage::updateButtons);
    connect(m_approve, &QPushButton::clicked, this, [this] { review(ApplicationStatus::Approved); });
    connect(m_reject, &QPushButton::clicked, this, [this] { review(ApplicationStatus::Rejected); });
}

void VolunteersPage::refresh()
{
    const QString keep = selectedKey(m_table);

    std::vector<const VolunteerApplication *> shown;
    for (const VolunteerApplication &application : m_library.applications())
    {
        if (!m_pendingOnly->isChecked() || application.getStatus() == ApplicationStatus::Pending)
        {
            shown.push_back(&application);
        }
    }

    beginFill(m_table, static_cast<int>(shown.size()));
    for (int row = 0; row < static_cast<int>(shown.size()); row++)
    {
        const VolunteerApplication *application = shown[row];

        Tone tone = Tone::Warning;
        if (application->getStatus() == ApplicationStatus::Approved) tone = Tone::Good;
        if (application->getStatus() == ApplicationStatus::Rejected) tone = Tone::Bad;

        m_table->setItem(row, 0, numberCell(application->getId()));
        m_table->setItem(row, 1, cell(Theme::qs(application->getName())));
        m_table->setItem(row, 2, cell(Theme::qs(application->getEmail())));
        m_table->setItem(row, 3, cell(Theme::qs(application->getPhone())));
        m_table->setItem(row, 4, cell(Theme::qs(application->getAvailability())));
        m_table->setItem(row, 5, cell(Theme::qs(application->getAppliedOn().toString())));
        m_table->setItem(row, 6, cell(Theme::qs(EnumText::toString(application->getStatus())), tone));
        setRowKey(m_table, row, QString::number(application->getId()));
    }
    endFill(m_table);

    selectKey(m_table, keep);
    updateButtons();
}

void VolunteersPage::updateButtons()
{
    const int id = selectedKey(m_table).toInt();
    const VolunteerApplication *selected = nullptr;

    for (const VolunteerApplication &application : m_library.applications())
    {
        if (application.getId() == id)
        {
            selected = &application;
        }
    }

    const bool pending = selected && selected->getStatus() == ApplicationStatus::Pending;
    m_approve->setEnabled(pending);
    m_reject->setEnabled(pending);

    if (selected == nullptr)
    {
        m_reason->setText(m_table->rowCount() == 0 ? "No applications to show."
                                                   : "Select an application to read it.");
    }
    else
    {
        const QString reason = Theme::qs(selected->getReason());
        m_reason->setText("<b>" + Theme::qs(selected->getName()).toHtmlEscaped() + "</b>: " +
                          (reason.isEmpty() ? "No reason given." : reason.toHtmlEscaped()));
    }
}

void VolunteersPage::review(ApplicationStatus decision)
{
    const int id = selectedKey(m_table).toInt();
    if (id == 0)
    {
        return;
    }

    try
    {
        m_library.reviewApplication(id, decision, m_user);
        refresh();
        flash(decision == ApplicationStatus::Approved ? "Application approved."
                                                      : "Application rejected.");
    }
    catch (const std::exception &e)
    {
        showError(e.what());
    }
}
