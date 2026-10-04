#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QWidget>

#include <vector>

class BasePage;
class Library;
class Person;
class QButtonGroup;
class QStackedWidget;
class QVBoxLayout;

// =========================================================
// DASHBOARD PAGE
//
// Sidebar on the left, the selected page on the right.
// Pages are only added when the user is allowed to use them,
// e.g. "Volunteers" appears only if user.canReviewVolunteers().
// All pages are stored as BasePage pointers.
// =========================================================

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    DashboardPage(Library &library, Person &user, QWidget *parent = nullptr);

signals:
    void logoutRequested();

private slots:
    void showPage(int index);
    void openProfile();

private:
    void addPage(const QString &name, BasePage *page);

    Library &m_library;
    Person &m_user;

    QVBoxLayout *m_nav;
    QButtonGroup *m_navGroup;
    QStackedWidget *m_stack;
    std::vector<BasePage *> m_pages;
};

#endif // DASHBOARDPAGE_H
