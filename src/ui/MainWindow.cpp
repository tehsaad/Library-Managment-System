#include "MainWindow.h"
#include "DashboardPage.h"
#include "LoginPage.h"
#include "Theme.h"
#include "WelcomePage.h"
#include "core/Library.h"
#include "dialogs/VolunteerDialog.h"

#include <QMessageBox>
#include <QStackedWidget>


MainWindow::MainWindow(Library &library, QWidget *parent)
    : QMainWindow(parent)
    , m_library(library)
{
    setWindowTitle("Library Management System");
    setMinimumSize(1060, 700);
    resize(1240, 780);

    m_welcome = new WelcomePage;
    m_login = new LoginPage(library);

    m_stack = new QStackedWidget;
    m_stack->addWidget(m_welcome);
    m_stack->addWidget(m_login);
    setCentralWidget(m_stack);

    connect(m_welcome, &WelcomePage::roleChosen, this, &MainWindow::showLogin);
    connect(m_welcome, &WelcomePage::volunteerChosen, this, &MainWindow::showVolunteerForm);
    connect(m_login, &LoginPage::backRequested, this, &MainWindow::showWelcome);
    connect(m_login, &LoginPage::loggedIn, this, &MainWindow::openDashboard);

    showWelcome();
}

void MainWindow::showWelcome()
{
    m_stack->setCurrentWidget(m_welcome);
}

void MainWindow::showLogin(Role role)
{
    m_login->setRole(role);
    m_stack->setCurrentWidget(m_login);
}

void MainWindow::showVolunteerForm()
{
    VolunteerDialog dialog(m_library, this);

    if (dialog.exec() == QDialog::Accepted)
    {
        QMessageBox::information(this, "Application sent",
                                 "Thank you, " + dialog.applicantName() +
                                     "!\n\nAn administrator will review your application.");
    }
}

void MainWindow::openDashboard(Person *user)
{
    m_currentUser = user;

    // A fresh dashboard for every sign-in, built for this user's role
    m_dashboard = new DashboardPage(m_library, *user);
    connect(m_dashboard, &DashboardPage::logoutRequested, this, &MainWindow::signOut);

    m_stack->addWidget(m_dashboard);
    m_stack->setCurrentWidget(m_dashboard);
}

void MainWindow::signOut()
{
    if (m_currentUser != nullptr)
    {
        try
        {
            m_library.logout(*m_currentUser);
        }
        catch (const std::exception &e)
        {
            QMessageBox::warning(this, "Could not save", e.what());
        }
    }

    m_currentUser = nullptr;
    showWelcome();

    // Remove the old dashboard (deleteLater: we are inside one of its signals)
    m_stack->removeWidget(m_dashboard);
    m_dashboard->deleteLater();
    m_dashboard = nullptr;
}
