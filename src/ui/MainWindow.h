#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "model/Enums.h"

#include <QMainWindow>

class DashboardPage;
class Library;
class LoginPage;
class Person;
class QStackedWidget;
class WelcomePage;

// =========================================================
// MAIN WINDOW
//
// One window for the whole app. A QStackedWidget swaps
// between three screens:
//
//   Welcome  --role-->  Login  --success-->  Dashboard
//      ^                  |                      |
//      +------ back ------+------ sign out ------+
// =========================================================

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Library &library, QWidget *parent = nullptr);

private slots:
    void showWelcome();
    void showLogin(Role role);
    void showVolunteerForm();
    void openDashboard(Person *user);
    void signOut();

private:
    Library &m_library;
    Person *m_currentUser = nullptr;

    QStackedWidget *m_stack;
    WelcomePage *m_welcome;
    LoginPage *m_login;
    DashboardPage *m_dashboard = nullptr;
};

#endif // MAINWINDOW_H
