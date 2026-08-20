/********************************************************************************
** Form generated from reading UI file 'loginui.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINUI_H
#define UI_LOGINUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginUI
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QFrame *headerPanel;
    QWidget *titleArea;
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QLabel *logoLabel;
    QSpacerItem *verticalSpacer;
    QFrame *loginPanel;
    QVBoxLayout *verticalLayout;
    QPushButton *backButton;
    QLabel *welcomeLabbel;
    QLabel *welcomeSubtitleLabel;
    QLabel *usernameLabel;
    QLineEdit *usernameTextBox;
    QLabel *passwordLabel;
    QLineEdit *passwordTextBox;
    QCheckBox *showPasswordCheckBox;
    QLabel *statusLabel;
    QPushButton *loginButton;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginUI)
    {
        if (LoginUI->objectName().isEmpty())
            LoginUI->setObjectName("LoginUI");
        LoginUI->resize(1894, 1027);
        LoginUI->setStyleSheet(QString::fromUtf8("/* =========================================================\n"
"   MAIN LOGIN WINDOW\n"
"   ========================================================= */\n"
"\n"
"QMainWindow {\n"
"    background-color: #000000;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   HEADER\n"
"   ========================================================= */\n"
"\n"
"#headerPanel {\n"
"    background-color: #1E293B;\n"
"}\n"
"\n"
"#logoLabel {\n"
"    color: white;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 32pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"#titleLabel {\n"
"    color: white;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 20pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"#subtitleLabel {\n"
"    color: #CBD5E1;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   LOGIN CARD\n"
"   ========================================================= */\n"
"\n"
"#loginPanel {\n"
"    ba"
                        "ckground-color: white;\n"
"    border: 1px solid #E2E8F0;\n"
"    border-radius: 18px;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   WELCOME\n"
"   ========================================================= */\n"
"\n"
"#welcomeLabel {\n"
"    color: #1E293B;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 24pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"#welcomeSubtitleLabel {\n"
"    color: #64748B;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   LABELS\n"
"   ========================================================= */\n"
"\n"
"#usernameLabel,\n"
"#passwordLabel {\n"
"    color: #334155;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   TEXT BOXES\n"
"   ========================================================= */\n"
"\n"
"#usernameTextBox,\n"
""
                        "#passwordTextBox {\n"
"    background-color: #F8FAFC;\n"
"    color: #1E293B;\n"
"\n"
"    border: 2px solid #CBD5E1;\n"
"    border-radius: 8px;\n"
"\n"
"    padding: 8px;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 11pt;\n"
"}\n"
"\n"
"#usernameTextBox:focus,\n"
"#passwordTextBox:focus {\n"
"    border: 2px solid #2563EB;\n"
"    background-color: white;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   SHOW PASSWORD\n"
"   ========================================================= */\n"
"\n"
"#showPasswordCheckBox {\n"
"    color: #475569;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   LOGIN BUTTON\n"
"   ========================================================= */\n"
"\n"
"#loginButton {\n"
"    background-color: #2563EB;\n"
"    color: white;\n"
"\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: "
                        "11pt;\n"
"    font-weight: bold;\n"
"\n"
"    padding: 10px;\n"
"}\n"
"\n"
"#loginButton:hover {\n"
"    background-color: #1D4ED8;\n"
"}\n"
"\n"
"#loginButton:pressed {\n"
"    background-color: #1E40AF;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   CLEAR BUTTON\n"
"   ========================================================= */\n"
"\n"
"#clearButton {\n"
"    background-color: #E2E8F0;\n"
"    color: #334155;\n"
"\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 11pt;\n"
"    font-weight: bold;\n"
"\n"
"    padding: 10px;\n"
"}\n"
"\n"
"#clearButton:hover {\n"
"    background-color: #CBD5E1;\n"
"}\n"
"\n"
"#clearButton:pressed {\n"
"    background-color: #94A3B8;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   BACK BUTTON\n"
"   ========================================================= */\n"
"\n"
"#backButton {\n"
"    background-color: transparent;\n"
"    color: #256"
                        "3EB;\n"
"\n"
"    border: none;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"#backButton:hover {\n"
"    color: #1D4ED8;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   STATUS\n"
"   ========================================================= */\n"
"\n"
"#statusLabel {\n"
"    color: #DC2626;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 9.5pt;\n"
"\n"
"    padding: 5px;\n"
"}\n"
"\n"
"\n"
"/* =========================================================\n"
"   FOOTER\n"
"   ========================================================= */\n"
"\n"
"#footerLabel {\n"
"    color: #94A3B8;\n"
"\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 9pt;\n"
"}"));
        centralwidget = new QWidget(LoginUI);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        headerPanel = new QFrame(centralwidget);
        headerPanel->setObjectName("headerPanel");
        headerPanel->setMinimumSize(QSize(0, 60));
        headerPanel->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        headerPanel->setFrameShape(QFrame::Shape::StyledPanel);
        headerPanel->setFrameShadow(QFrame::Shadow::Raised);
        titleArea = new QWidget(headerPanel);
        titleArea->setObjectName("titleArea");
        titleArea->setGeometry(QRect(123, 12, 469, 95));
        verticalLayout_2 = new QVBoxLayout(titleArea);
        verticalLayout_2->setObjectName("verticalLayout_2");
        titleLabel = new QLabel(titleArea);
        titleLabel->setObjectName("titleLabel");

        verticalLayout_2->addWidget(titleLabel);

        subtitleLabel = new QLabel(titleArea);
        subtitleLabel->setObjectName("subtitleLabel");

        verticalLayout_2->addWidget(subtitleLabel);

        logoLabel = new QLabel(headerPanel);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(10, 20, 111, 81));
        logoLabel->setFrameShape(QFrame::Shape::StyledPanel);
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(headerPanel);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        loginPanel = new QFrame(centralwidget);
        loginPanel->setObjectName("loginPanel");
        loginPanel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        loginPanel->setFrameShape(QFrame::Shape::StyledPanel);
        loginPanel->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(loginPanel);
        verticalLayout->setObjectName("verticalLayout");
        backButton = new QPushButton(loginPanel);
        backButton->setObjectName("backButton");

        verticalLayout->addWidget(backButton, 0, Qt::AlignmentFlag::AlignLeft);

        welcomeLabbel = new QLabel(loginPanel);
        welcomeLabbel->setObjectName("welcomeLabbel");
        QFont font;
        font.setPointSize(36);
        font.setUnderline(true);
        welcomeLabbel->setFont(font);
        welcomeLabbel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(welcomeLabbel);

        welcomeSubtitleLabel = new QLabel(loginPanel);
        welcomeSubtitleLabel->setObjectName("welcomeSubtitleLabel");
        welcomeSubtitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(welcomeSubtitleLabel);

        usernameLabel = new QLabel(loginPanel);
        usernameLabel->setObjectName("usernameLabel");

        verticalLayout->addWidget(usernameLabel);

        usernameTextBox = new QLineEdit(loginPanel);
        usernameTextBox->setObjectName("usernameTextBox");

        verticalLayout->addWidget(usernameTextBox);

        passwordLabel = new QLabel(loginPanel);
        passwordLabel->setObjectName("passwordLabel");

        verticalLayout->addWidget(passwordLabel);

        passwordTextBox = new QLineEdit(loginPanel);
        passwordTextBox->setObjectName("passwordTextBox");
        passwordTextBox->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(passwordTextBox);

        showPasswordCheckBox = new QCheckBox(loginPanel);
        showPasswordCheckBox->setObjectName("showPasswordCheckBox");

        verticalLayout->addWidget(showPasswordCheckBox);

        statusLabel = new QLabel(loginPanel);
        statusLabel->setObjectName("statusLabel");

        verticalLayout->addWidget(statusLabel);

        loginButton = new QPushButton(loginPanel);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton, 0, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);


        verticalLayout_3->addWidget(loginPanel);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        LoginUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginUI);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1894, 25));
        LoginUI->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginUI);
        statusbar->setObjectName("statusbar");
        LoginUI->setStatusBar(statusbar);

        retranslateUi(LoginUI);

        QMetaObject::connectSlotsByName(LoginUI);
    } // setupUi

    void retranslateUi(QMainWindow *LoginUI)
    {
        LoginUI->setWindowTitle(QCoreApplication::translate("LoginUI", "MainWindow", nullptr));
        titleLabel->setText(QCoreApplication::translate("LoginUI", "Library Management System", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("LoginUI", "Welcome to your digital library", nullptr));
        logoLabel->setText(QCoreApplication::translate("LoginUI", "LMS", nullptr));
        backButton->setText(QCoreApplication::translate("LoginUI", "<--", nullptr));
        welcomeLabbel->setText(QCoreApplication::translate("LoginUI", "Welcome Back!", nullptr));
        welcomeSubtitleLabel->setText(QCoreApplication::translate("LoginUI", "Sign in to continue to your LMS account.", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginUI", "Username:", nullptr));
        usernameTextBox->setPlaceholderText(QCoreApplication::translate("LoginUI", "Enter your username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginUI", "Password", nullptr));
        passwordTextBox->setPlaceholderText(QCoreApplication::translate("LoginUI", "Enter your password", nullptr));
        showPasswordCheckBox->setText(QCoreApplication::translate("LoginUI", "Show Password", nullptr));
        statusLabel->setText(QString());
        loginButton->setText(QCoreApplication::translate("LoginUI", "Login", nullptr));
        label->setText(QCoreApplication::translate("LoginUI", "Library Management System  |  Secure Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginUI: public Ui_LoginUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINUI_H
