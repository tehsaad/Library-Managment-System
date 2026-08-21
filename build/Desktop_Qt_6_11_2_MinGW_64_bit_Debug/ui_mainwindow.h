/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *contentArea;
    QVBoxLayout *verticalLayout_3;
    QFrame *headerPanel;
    QWidget *titleArea;
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QLabel *subtitleLabel;
    QLabel *logoLabel;
    QSpacerItem *verticalSpacer_3;
    QFrame *menuPanel;
    QGridLayout *gridLayout_4;
    QLabel *statusLabel;
    QLabel *selectLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *adminButton;
    QPushButton *studentButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *facultyButton;
    QPushButton *volunteerButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QLabel *footerLabel;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(1200, 700));
        MainWindow->setMaximumSize(QSize(1280, 720));
        MainWindow->setFocusPolicy(Qt::FocusPolicy::WheelFocus);
        MainWindow->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #000000;\n"
"}\n"
"\n"
"QFrame#headerPanel {\n"
"    background-color: #1E293B;\n"
"    border: none;\n"
"}\n"
"\n"
"QLabel#logoLabel {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 30pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLabel#titleLabel {\n"
"    background-color: transparent;\n"
"    color: white;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 20pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QLabel#subtitleLabel {\n"
"    background-color: transparent;\n"
"    color: #CBD5E1;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"QFrame#menuPanel {\n"
"    background-color: white;\n"
"    border: 1px solid #E2E8F0;\n"
"    border-radius: 14px;\n"
"}\n"
"\n"
"QLabel#selectLabel {\n"
"    background-color: transparent;\n"
"    color: #1E293B;\n"
"    font-size: 20pt;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QPushButton {\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 14pt;\n"
"    font-weight: "
                        "bold;\n"
"}\n"
"\n"
"QPushButton#studentButton {\n"
"    background-color: #2563EB;\n"
"    color: Dark;\n"
"}\n"
"\n"
"QPushButton#studentButton:hover {\n"
"    background-color: #1D4ED8;\n"
"}\n"
"\n"
"QPushButton#studentButton:pressed {\n"
"    background-color: #1E40AF;\n"
"}\n"
"\n"
"QPushButton#facultyButton {\n"
"    background-color: #10B981;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#facultyButton:hover {\n"
"    background-color: #059669;\n"
"}\n"
"\n"
"QPushButton#facultyButton:pressed {\n"
"    background-color: #047857;\n"
"}\n"
"\n"
"QPushButton#adminButton {\n"
"    background-color: #7C3AED;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#adminButton:hover {\n"
"    background-color: #6D28D9;\n"
"}\n"
"\n"
"QPushButton#adminButton:pressed {\n"
"    background-color: #5B21B6;\n"
"}\n"
"\n"
"QPushButton#volunteerButton {\n"
"    background-color: #F59E0B;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#volunteerButton:hover {\n"
"    background-color: #D97706;\n"
"}\n"
"\n"
"QPushButton#v"
                        "olunteerButton:pressed {\n"
"    background-color: #B45309;\n"
"}\n"
"\n"
"QPushButton#settingsButton {\n"
"    background-color: #475569;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#settingsButton:hover {\n"
"    background-color: #334155;\n"
"}\n"
"\n"
"QPushButton#settingsButton:pressed {\n"
"    background-color: #1E293B;\n"
"}\n"
"\n"
"QPushButton#exitButton {\n"
"    background-color: #DC2626;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton#exitButton:hover {\n"
"    background-color: #B91C1C;\n"
"}\n"
"\n"
"QPushButton#exitButton:pressed {\n"
"    background-color: #991B1B;\n"
"}\n"
"\n"
"QLabel#statusLabel {\n"
"    background-color: transparent;\n"
"    color: #64748B;\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"QLabel#footerLabel {\n"
"    background-color: transparent;\n"
"    color: #64748B;\n"
"    font-size: 9pt;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("QWidget#centralWidget {\n"
"    background-color: #000000;\n"
"}"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        contentArea = new QWidget(centralwidget);
        contentArea->setObjectName("contentArea");
        verticalLayout_3 = new QVBoxLayout(contentArea);
        verticalLayout_3->setObjectName("verticalLayout_3");
        headerPanel = new QFrame(contentArea);
        headerPanel->setObjectName("headerPanel");
        headerPanel->setMinimumSize(QSize(0, 120));
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

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        menuPanel = new QFrame(contentArea);
        menuPanel->setObjectName("menuPanel");
        menuPanel->setFrameShape(QFrame::Shape::StyledPanel);
        menuPanel->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_4 = new QGridLayout(menuPanel);
        gridLayout_4->setObjectName("gridLayout_4");
        statusLabel = new QLabel(menuPanel);
        statusLabel->setObjectName("statusLabel");
        QFont font;
        font.setPointSize(10);
        statusLabel->setFont(font);

        gridLayout_4->addWidget(statusLabel, 2, 0, 1, 1);

        selectLabel = new QLabel(menuPanel);
        selectLabel->setObjectName("selectLabel");
        selectLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(selectLabel, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(25);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        adminButton = new QPushButton(menuPanel);
        adminButton->setObjectName("adminButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(adminButton->sizePolicy().hasHeightForWidth());
        adminButton->setSizePolicy(sizePolicy);
        adminButton->setMinimumSize(QSize(250, 70));

        horizontalLayout->addWidget(adminButton);

        studentButton = new QPushButton(menuPanel);
        studentButton->setObjectName("studentButton");
        sizePolicy.setHeightForWidth(studentButton->sizePolicy().hasHeightForWidth());
        studentButton->setSizePolicy(sizePolicy);
        studentButton->setMinimumSize(QSize(250, 70));

        horizontalLayout->addWidget(studentButton);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        facultyButton = new QPushButton(menuPanel);
        facultyButton->setObjectName("facultyButton");
        sizePolicy.setHeightForWidth(facultyButton->sizePolicy().hasHeightForWidth());
        facultyButton->setSizePolicy(sizePolicy);
        facultyButton->setMinimumSize(QSize(250, 70));

        horizontalLayout->addWidget(facultyButton);

        volunteerButton = new QPushButton(menuPanel);
        volunteerButton->setObjectName("volunteerButton");
        sizePolicy.setHeightForWidth(volunteerButton->sizePolicy().hasHeightForWidth());
        volunteerButton->setSizePolicy(sizePolicy);
        volunteerButton->setMinimumSize(QSize(250, 70));

        horizontalLayout->addWidget(volunteerButton);


        gridLayout_4->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, -1, -1);
        settingsButton = new QPushButton(menuPanel);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setMinimumSize(QSize(200, 55));

        horizontalLayout_4->addWidget(settingsButton);

        exitButton = new QPushButton(menuPanel);
        exitButton->setObjectName("exitButton");
        exitButton->setMinimumSize(QSize(200, 55));

        horizontalLayout_4->addWidget(exitButton);


        gridLayout_4->addLayout(horizontalLayout_4, 10, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 4, 0, 1, 1);


        verticalLayout_3->addWidget(menuPanel);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        footerLabel = new QLabel(contentArea);
        footerLabel->setObjectName("footerLabel");
        footerLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(footerLabel);


        verticalLayout->addWidget(contentArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 25));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Library Managment System", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Library Management System", nullptr));
        subtitleLabel->setText(QCoreApplication::translate("MainWindow", "Welcome to your digital library", nullptr));
        logoLabel->setText(QCoreApplication::translate("MainWindow", "LMS", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", " LMS", nullptr));
        selectLabel->setText(QCoreApplication::translate("MainWindow", "Welcome to LMS", nullptr));
        adminButton->setText(QCoreApplication::translate("MainWindow", "Admin Login", nullptr));
        studentButton->setText(QCoreApplication::translate("MainWindow", "STUDENT LOGIN", nullptr));
        facultyButton->setText(QCoreApplication::translate("MainWindow", "Faculty Login", nullptr));
        volunteerButton->setText(QCoreApplication::translate("MainWindow", "New Login", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "Setings", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        footerLabel->setText(QCoreApplication::translate("MainWindow", "Library Management System", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
