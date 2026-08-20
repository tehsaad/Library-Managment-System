/********************************************************************************
** Form generated from reading UI file 'Dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dashboard
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *headerPanel;
    QWidget *titleArea;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QLabel *label;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLabel *authority;
    QLabel *authorityLabel;
    QLabel *username;
    QWidget *contentLayout;
    QFrame *sidePanel;
    QVBoxLayout *verticalLayout_2;
    QPushButton *dashboardButton;
    QPushButton *booksButton;
    QPushButton *memberButton;
    QPushButton *borrowedButton;
    QPushButton *issueBookButton;
    QPushButton *userButton;
    QPushButton *historyButton;
    QPushButton *volunteersButton;
    QPushButton *myBooksButton;
    QPushButton *returnBookButton;
    QPushButton *manageBooksButton;
    QPushButton *facultyButton;
    QPushButton *profileButton;
    QPushButton *settingsButton;
    QPushButton *reportstButton;
    QPushButton *logoutButton;
    QFrame *tablePanel;
    QTableWidget *tableWidget;
    QLabel *footerLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Dashboard)
    {
        if (Dashboard->objectName().isEmpty())
            Dashboard->setObjectName("Dashboard");
        Dashboard->resize(1920, 1080);
        Dashboard->setMaximumSize(QSize(1920, 1080));
        Dashboard->setStyleSheet(QString::fromUtf8("/* =========================================================\n"
"   LMS DASHBOARD\n"
"   ========================================================= */\n"
"\n"
"\n"
"/* =========================================================\n"
"   MAIN WINDOW\n"
"   ========================================================= */\n"
"\n"
"QMainWindow {\n"
"    background-color: #F5F7FA;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   CENTRAL WIDGET\n"
"   ========================================================= */\n"
"\n"
"#centralWidget {\n"
"    background-color: #F5F7FA;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   HEADER\n"
"   ========================================================= */\n"
"\n"
"#headerPanel {\n"
"    background-color: #1E293B;\n"
"    border: none;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   LMS LOGO\n"
"   ========================================================= */\n"
"\n"
"#logo"
                        "Label {\n"
"    color: #FFFFFF;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 28pt;\n"
"    font-weight: bold;\n"
"\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   HEADER TITLE\n"
"   ========================================================= */\n"
"\n"
"#titleLabel {\n"
"    color: #FFFFFF;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 18pt;\n"
"    font-weight: bold;\n"
"\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   HEADER SUBTITLE\n"
"   ========================================================= */\n"
"\n"
"#subtitleLabel {\n"
"    color: #CBD5E1;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 9.5pt;\n"
"\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   USER INFORMATION PANEL\n"
"   ======================================================="
                        "== */\n"
"\n"
"#userInfoPanel {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   USERNAME\n"
"   ========================================================= */\n"
"\n"
"#usernameLabel {\n"
"    color: #FFFFFF;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   AUTHORITY\n"
"   ========================================================= */\n"
"\n"
"#authorityLabel {\n"
"    color: #60A5FA;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 9pt;\n"
"    font-weight: bold;\n"
"\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   CONTENT AREA\n"
"   ========================================================= */\n"
"\n"
"#contentPanel {\n"
"    background-color: #F5F7FA;\n"
""
                        "    border: none;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   LEFT SIDEBAR\n"
"   ========================================================= */\n"
"\n"
"#sidePanel {\n"
"    background-color: #0F172A;\n"
"\n"
"    border: none;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   ALL SIDEBAR BUTTONS - BASE\n"
"   ========================================================= */\n"
"\n"
"#sidePanel QPushButton {\n"
"    background-color: transparent;\n"
"\n"
"    color: #CBD5E1;\n"
"\n"
"    border: none;\n"
"    border-radius: 7px;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"    font-weight: bold;\n"
"\n"
"    text-align: left;\n"
"\n"
"    padding-left: 20px;\n"
"    padding-right: 10px;\n"
"\n"
"    min-height: 42px;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   SIDEBAR BUTTON - HOVER\n"
"   ========================================================= */\n"
"\n"
"#sidePanel"
                        " QPushButton:hover {\n"
"    background-color: #1E293B;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   SIDEBAR BUTTON - PRESSED\n"
"   ========================================================= */\n"
"\n"
"#sidePanel QPushButton:pressed {\n"
"    background-color: #334155;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   DASHBOARD BUTTON\n"
"   ========================================================= */\n"
"\n"
"#dashboardButton {\n"
"    background-color: #2563EB !important;\n"
"    color: #FFFFFF !important;\n"
"\n"
"    border-radius: 7px;\n"
"\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
"#dashboardButton:hover {\n"
"    background-color: #1D4ED8 !important;\n"
"}\n"
"\n"
"\n"
"#dashboardButton:pressed {\n"
"    background-color: #1E40AF !important;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   STUDENT BUTTONS\n"
"   ====================="
                        "==================================== */\n"
"\n"
"#myBooksButton:hover,\n"
"#borrowedBooksButton:hover,\n"
"#historyButton:hover {\n"
"    background-color: #1E3A8A;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   FACULTY BUTTONS\n"
"   ========================================================= */\n"
"\n"
"#manageBooksButton:hover,\n"
"#issueBookButton:hover,\n"
"#returnBookButton:hover,\n"
"#membersButton:hover {\n"
"    background-color: #065F46;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   ADMIN BUTTONS\n"
"   ========================================================= */\n"
"\n"
"#usersButton:hover,\n"
"#booksButton:hover,\n"
"#facultyButton:hover,\n"
"#volunteersButton:hover,\n"
"#reportsButton:hover,\n"
"#settingsButton:hover {\n"
"    background-color: #5B21B6;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   PROFILE"
                        " BUTTON\n"
"   ========================================================= */\n"
"\n"
"#profileButton {\n"
"    color: #CBD5E1;\n"
"}\n"
"\n"
"\n"
"#profileButton:hover {\n"
"    background-color: #475569;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   LOGOUT BUTTON\n"
"   ========================================================= */\n"
"\n"
"#logoutButton {\n"
"    color: #FCA5A5;\n"
"}\n"
"\n"
"\n"
"#logoutButton:hover {\n"
"    background-color: #7F1D1D;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"#logoutButton:pressed {\n"
"    background-color: #991B1B;\n"
"    color: #FFFFFF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   TABLE PANEL\n"
"   ========================================================= */\n"
"\n"
"#tablePanel {\n"
"    background-color: #F5F7FA;\n"
"\n"
"    border: none;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   TABLE TITLE\n"
"   =============="
                        "=========================================== */\n"
"\n"
"#tableTitleLabel {\n"
"    color: #1E293B;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 17pt;\n"
"    font-weight: bold;\n"
"\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   DATA TABLE\n"
"   ========================================================= */\n"
"\n"
"#dataTable {\n"
"    background-color: #FFFFFF;\n"
"\n"
"    color: #1E293B;\n"
"\n"
"    border: 1px solid #E2E8F0;\n"
"\n"
"    border-radius: 8px;\n"
"\n"
"    gridline-color: #E2E8F0;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"\n"
"    selection-background-color: #DBEAFE;\n"
"    selection-color: #1E3A8A;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   TABLE HEADER\n"
"   ========================================================= */\n"
"\n"
"#dataTable QHeaderView::section {\n"
"    background-color: #1E293B;\n"
"\n"
"    color: #FFFFFF;\n"
""
                        "\n"
"    border: none;\n"
"\n"
"    padding: 10px;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   TABLE HEADER - HOVER\n"
"   ========================================================= */\n"
"\n"
"#dataTable QHeaderView::section:hover {\n"
"    background-color: #334155;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   TABLE CORNER\n"
"   ========================================================= */\n"
"\n"
"#dataTable QTableCornerButton::section {\n"
"    background-color: #1E293B;\n"
"    border: none;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   TABLE SCROLLBAR\n"
"   ========================================================= */\n"
"\n"
"#dataTable QScrollBar:vertical {\n"
"    background-color: #F1F5F9;\n"
"\n"
"    width: 10px;\n"
"\n"
"    margin: 0px;\n"
"}\n"
"\n"
"\n"
"#dataTable QScrollBar::h"
                        "andle:vertical {\n"
"    background-color: #CBD5E1;\n"
"\n"
"    border-radius: 5px;\n"
"\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"\n"
"#dataTable QScrollBar::handle:vertical:hover {\n"
"    background-color: #94A3B8;\n"
"}\n"
"\n"
"\n"
"#dataTable QScrollBar::add-line:vertical,\n"
"#dataTable QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"\n"
"#dataTable QScrollBar:horizontal {\n"
"    background-color: #F1F5F9;\n"
"\n"
"    height: 10px;\n"
"}\n"
"\n"
"\n"
"#dataTable QScrollBar::handle:horizontal {\n"
"    background-color: #CBD5E1;\n"
"\n"
"    border-radius: 5px;\n"
"\n"
"    min-width: 30px;\n"
"}\n"
"\n"
"\n"
"#dataTable QScrollBar::handle:horizontal:hover {\n"
"    background-color: #94A3B8;\n"
"}\n"
"\n"
"\n"
"#dataTable QScrollBar::add-line:horizontal,\n"
"#dataTable QScrollBar::sub-line:horizontal {\n"
"    width: 0px;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   FOOTER\n"
"   ========================================================= */"
                        "\n"
"\n"
"#footerLabel {\n"
"    color: #64748B;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 9pt;\n"
"\n"
"    background-color: transparent;\n"
"}"));
        centralwidget = new QWidget(Dashboard);
        centralwidget->setObjectName("centralwidget");
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 1921, 101));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        headerPanel = new QWidget(horizontalLayoutWidget);
        headerPanel->setObjectName("headerPanel");
        titleArea = new QWidget(headerPanel);
        titleArea->setObjectName("titleArea");
        titleArea->setGeometry(QRect(120, 0, 411, 101));
        verticalLayout = new QVBoxLayout(titleArea);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(titleArea);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        subtitleLabel = new QLabel(titleArea);
        subtitleLabel->setObjectName("subtitleLabel");

        verticalLayout->addWidget(subtitleLabel);

        label = new QLabel(headerPanel);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 40, 63, 20));
        widget = new QWidget(headerPanel);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(1430, 0, 481, 101));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName("formLayout");
        usernameLabel = new QLabel(widget);
        usernameLabel->setObjectName("usernameLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, usernameLabel);

        authority = new QLabel(widget);
        authority->setObjectName("authority");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, authority);

        authorityLabel = new QLabel(widget);
        authorityLabel->setObjectName("authorityLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, authorityLabel);

        username = new QLabel(widget);
        username->setObjectName("username");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, username);


        horizontalLayout->addWidget(headerPanel);

        contentLayout = new QWidget(centralwidget);
        contentLayout->setObjectName("contentLayout");
        contentLayout->setGeometry(QRect(0, 100, 1931, 971));
        sidePanel = new QFrame(contentLayout);
        sidePanel->setObjectName("sidePanel");
        sidePanel->setGeometry(QRect(-10, -2, 381, 931));
        sidePanel->setFrameShape(QFrame::Shape::StyledPanel);
        sidePanel->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(sidePanel);
        verticalLayout_2->setObjectName("verticalLayout_2");
        dashboardButton = new QPushButton(sidePanel);
        dashboardButton->setObjectName("dashboardButton");
        dashboardButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(dashboardButton, 0, Qt::AlignmentFlag::AlignHCenter);

        booksButton = new QPushButton(sidePanel);
        booksButton->setObjectName("booksButton");
        booksButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(booksButton, 0, Qt::AlignmentFlag::AlignHCenter);

        memberButton = new QPushButton(sidePanel);
        memberButton->setObjectName("memberButton");
        memberButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(memberButton, 0, Qt::AlignmentFlag::AlignHCenter);

        borrowedButton = new QPushButton(sidePanel);
        borrowedButton->setObjectName("borrowedButton");
        borrowedButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(borrowedButton, 0, Qt::AlignmentFlag::AlignHCenter);

        issueBookButton = new QPushButton(sidePanel);
        issueBookButton->setObjectName("issueBookButton");
        issueBookButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(issueBookButton, 0, Qt::AlignmentFlag::AlignHCenter);

        userButton = new QPushButton(sidePanel);
        userButton->setObjectName("userButton");
        userButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(userButton, 0, Qt::AlignmentFlag::AlignHCenter);

        historyButton = new QPushButton(sidePanel);
        historyButton->setObjectName("historyButton");
        historyButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(historyButton, 0, Qt::AlignmentFlag::AlignHCenter);

        volunteersButton = new QPushButton(sidePanel);
        volunteersButton->setObjectName("volunteersButton");
        volunteersButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(volunteersButton, 0, Qt::AlignmentFlag::AlignHCenter);

        myBooksButton = new QPushButton(sidePanel);
        myBooksButton->setObjectName("myBooksButton");
        myBooksButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(myBooksButton, 0, Qt::AlignmentFlag::AlignHCenter);

        returnBookButton = new QPushButton(sidePanel);
        returnBookButton->setObjectName("returnBookButton");
        returnBookButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(returnBookButton, 0, Qt::AlignmentFlag::AlignHCenter);

        manageBooksButton = new QPushButton(sidePanel);
        manageBooksButton->setObjectName("manageBooksButton");
        manageBooksButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(manageBooksButton, 0, Qt::AlignmentFlag::AlignHCenter);

        facultyButton = new QPushButton(sidePanel);
        facultyButton->setObjectName("facultyButton");
        facultyButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(facultyButton, 0, Qt::AlignmentFlag::AlignHCenter);

        profileButton = new QPushButton(sidePanel);
        profileButton->setObjectName("profileButton");
        profileButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(profileButton, 0, Qt::AlignmentFlag::AlignHCenter);

        settingsButton = new QPushButton(sidePanel);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(settingsButton, 0, Qt::AlignmentFlag::AlignHCenter);

        reportstButton = new QPushButton(sidePanel);
        reportstButton->setObjectName("reportstButton");
        reportstButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(reportstButton, 0, Qt::AlignmentFlag::AlignHCenter);

        logoutButton = new QPushButton(sidePanel);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);

        verticalLayout_2->addWidget(logoutButton, 0, Qt::AlignmentFlag::AlignHCenter);

        tablePanel = new QFrame(contentLayout);
        tablePanel->setObjectName("tablePanel");
        tablePanel->setGeometry(QRect(380, 0, 1541, 951));
        tablePanel->setFrameShape(QFrame::Shape::StyledPanel);
        tablePanel->setFrameShadow(QFrame::Shadow::Raised);
        tableWidget = new QTableWidget(tablePanel);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(50, 100, 1401, 641));
        footerLabel = new QLabel(centralwidget);
        footerLabel->setObjectName("footerLabel");
        footerLabel->setGeometry(QRect(720, 1030, 621, 20));
        Dashboard->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Dashboard);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 25));
        Dashboard->setMenuBar(menubar);
        statusbar = new QStatusBar(Dashboard);
        statusbar->setObjectName("statusbar");
        Dashboard->setStatusBar(statusbar);

        retranslateUi(Dashboard);

        QMetaObject::connectSlotsByName(Dashboard);
    } // setupUi

    void retranslateUi(QMainWindow *Dashboard)
    {
        Dashboard->setWindowTitle(QCoreApplication::translate("Dashboard", "LMS Dashboard", nullptr));
        titleLabel->setText(QCoreApplication::translate("Dashboard", "Library Managment System", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("Dashboard", "Welcome to LMS Dashboard!", nullptr));
        label->setText(QCoreApplication::translate("Dashboard", "LMS", nullptr));
        usernameLabel->setText(QCoreApplication::translate("Dashboard", "TextLabel", nullptr));
        authority->setText(QCoreApplication::translate("Dashboard", "Authority:", nullptr));
        authorityLabel->setText(QCoreApplication::translate("Dashboard", "TextLabel", nullptr));
        username->setText(QCoreApplication::translate("Dashboard", "Username:", nullptr));
        dashboardButton->setText(QCoreApplication::translate("Dashboard", "Dashboard", nullptr));
        booksButton->setText(QCoreApplication::translate("Dashboard", "Books", nullptr));
        memberButton->setText(QCoreApplication::translate("Dashboard", "Members", nullptr));
        borrowedButton->setText(QCoreApplication::translate("Dashboard", "Borrowed", nullptr));
        issueBookButton->setText(QCoreApplication::translate("Dashboard", "Issue Book", nullptr));
        userButton->setText(QCoreApplication::translate("Dashboard", "User", nullptr));
        historyButton->setText(QCoreApplication::translate("Dashboard", "History", nullptr));
        volunteersButton->setText(QCoreApplication::translate("Dashboard", "Volunteers", nullptr));
        myBooksButton->setText(QCoreApplication::translate("Dashboard", "My Books", nullptr));
        returnBookButton->setText(QCoreApplication::translate("Dashboard", "Return Book", nullptr));
        manageBooksButton->setText(QCoreApplication::translate("Dashboard", "Manage Books", nullptr));
        facultyButton->setText(QCoreApplication::translate("Dashboard", "Faculty", nullptr));
        profileButton->setText(QCoreApplication::translate("Dashboard", "Profile", nullptr));
        settingsButton->setText(QCoreApplication::translate("Dashboard", "Settings", nullptr));
        reportstButton->setText(QCoreApplication::translate("Dashboard", "Reports", nullptr));
        logoutButton->setText(QCoreApplication::translate("Dashboard", "Exit", nullptr));
        footerLabel->setText(QCoreApplication::translate("Dashboard", "Library Managment System- Dashboard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dashboard: public Ui_Dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
