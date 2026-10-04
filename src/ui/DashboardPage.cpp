#include "DashboardPage.h"
#include "Theme.h"
#include "core/Library.h"
#include "dialogs/ProfileDialog.h"
#include "pages/BooksPage.h"
#include "pages/HistoryPage.h"
#include "pages/LoansPage.h"
#include "pages/MembersPage.h"
#include "pages/OverviewPage.h"
#include "pages/VolunteersPage.h"

#include <QButtonGroup>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>


DashboardPage::DashboardPage(Library &library, Person &user, QWidget *parent)
    : QWidget(parent)
    , m_library(library)
    , m_user(user)
{
    // ---- sidebar ----
    auto *sidebar = new QFrame;
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(230);

    auto *brand = new QLabel("Library");
    brand->setObjectName("brand");

    m_nav = new QVBoxLayout;
    m_nav->setSpacing(2);

    m_navGroup = new QButtonGroup(this);
    m_navGroup->setExclusive(true);
    connect(m_navGroup, &QButtonGroup::idClicked, this, &DashboardPage::showPage);

    // ---- user chip at the bottom ----
    auto *chip = new QFrame;
    chip->setObjectName("userChip");

    auto *name = Theme::label(Theme::qs(user.getName()), "heading");
    name->setWordWrap(true);
    auto *role = Theme::label(Theme::qs(user.roleName() + "  ·  " + user.getUsername()), "small");

    auto *profile = Theme::button("Profile");
    auto *logout = Theme::button("Sign out");
    connect(profile, &QPushButton::clicked, this, &DashboardPage::openProfile);
    connect(logout, &QPushButton::clicked, this, &DashboardPage::logoutRequested);

    auto *chipButtons = new QHBoxLayout;
    chipButtons->setSpacing(6);
    chipButtons->addWidget(profile);
    chipButtons->addWidget(logout);

    auto *chipLayout = new QVBoxLayout(chip);
    chipLayout->setContentsMargins(14, 12, 14, 12);
    chipLayout->setSpacing(2);
    chipLayout->addWidget(name);
    chipLayout->addWidget(role);
    chipLayout->addSpacing(8);
    chipLayout->addLayout(chipButtons);

    auto *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(16, 24, 16, 16);
    sidebarLayout->setSpacing(4);
    sidebarLayout->addWidget(Theme::label("MANAGEMENT SYSTEM", "eyebrow"));
    sidebarLayout->addWidget(brand);
    sidebarLayout->addSpacing(22);
    sidebarLayout->addLayout(m_nav);
    sidebarLayout->addStretch();
    sidebarLayout->addWidget(chip);

    // ---- pages ----
    m_stack = new QStackedWidget;
    m_stack->setObjectName("contentStack");

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(sidebar);
    layout->addWidget(m_stack, 1);

    // Which pages exist depends on the user's permissions.
    // The questions are virtual functions answered by Student / Faculty / Admin.
    addPage("Overview", new OverviewPage(library, user));
    addPage("Catalog", new BooksPage(library, user));
    addPage(user.canIssueBooks() ? "Loans" : "My books", new LoansPage(library, user));

    if (user.canViewMembers())
    {
        addPage("Members", new MembersPage(library, user));
    }
    if (user.canReviewVolunteers())
    {
        addPage("Volunteers", new VolunteersPage(library, user));
    }
    if (user.canViewHistory())
    {
        addPage("History", new HistoryPage(library, user));
    }

    showPage(0);
}

void DashboardPage::addPage(const QString &name, BasePage *page)
{
    const int index = static_cast<int>(m_pages.size());

    auto *button = new QPushButton(name);
    button->setProperty("nav", true);
    button->setCheckable(true);
    button->setCursor(Qt::PointingHandCursor);

    m_navGroup->addButton(button, index);
    m_nav->addWidget(button);

    m_stack->addWidget(page);
    m_pages.push_back(page);
}

void DashboardPage::showPage(int index)
{
    if (index < 0 || index >= static_cast<int>(m_pages.size()))
    {
        return;
    }

    m_navGroup->button(index)->setChecked(true);

    // refresh() is pure virtual in BasePage: each page reloads its own way
    m_pages[index]->refresh();
    m_stack->setCurrentIndex(index);
}

void DashboardPage::openProfile()
{
    ProfileDialog dialog(m_library, m_user, this);
    dialog.exec();

    // Numbers on the current page may have changed (e.g. after a password change)
    m_pages[m_stack->currentIndex()]->refresh();
}
