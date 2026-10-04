#include "WelcomePage.h"
#include "Theme.h"
#include "widgets/RoleCard.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>


WelcomePage::WelcomePage(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("welcomePage");

    auto *student = new RoleCard("S", "Student",
                                 "Search the catalog, borrow books and see your due dates.");
    auto *faculty = new RoleCard("F", "Faculty",
                                 "Manage the catalog, issue and return books for students.");
    auto *admin = new RoleCard("A", "Administrator",
                               "Everything faculty can do, plus members and volunteers.");
    auto *volunteer = new RoleCard("V", "Volunteer",
                                   "No account needed. Apply to help out at the library.");

    connect(student, &RoleCard::clicked, this, [this] { emit roleChosen(Role::Student); });
    connect(faculty, &RoleCard::clicked, this, [this] { emit roleChosen(Role::Faculty); });
    connect(admin, &RoleCard::clicked, this, [this] { emit roleChosen(Role::Admin); });
    connect(volunteer, &RoleCard::clicked, this, &WelcomePage::volunteerChosen);

    auto *grid = new QGridLayout;
    grid->setSpacing(16);
    grid->addWidget(student, 0, 0);
    grid->addWidget(faculty, 0, 1);
    grid->addWidget(admin, 1, 0);
    grid->addWidget(volunteer, 1, 1);

    auto *headline = Theme::label("Welcome to the library.", "display");
    auto *subtitle = Theme::label("Choose how you would like to sign in.", "muted");
    auto *footer = Theme::label("Data is stored as CSV files in the \"data\" folder next to the program.",
                                "small");

    // A fixed-width column in the middle of the window
    auto *column = new QWidget;
    column->setMaximumWidth(760);

    auto *columnLayout = new QVBoxLayout(column);
    columnLayout->setContentsMargins(0, 0, 0, 0);
    columnLayout->setSpacing(6);
    columnLayout->addWidget(Theme::label("LIBRARY MANAGEMENT SYSTEM", "eyebrow"));
    columnLayout->addWidget(headline);
    columnLayout->addWidget(subtitle);
    columnLayout->addSpacing(28);
    columnLayout->addLayout(grid);
    columnLayout->addSpacing(28);
    columnLayout->addWidget(footer);

    // Centre the column with stretches on every side
    auto *row = new QHBoxLayout;
    row->addStretch();
    row->addWidget(column, 1);
    row->addStretch();

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 40, 40, 40);
    layout->addStretch(2);
    layout->addLayout(row);
    layout->addStretch(3);
}
