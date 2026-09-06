#include "loginui.h"
#include "ui_loginui.h"
#include "mainwindow.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>


LoginUI::LoginUI(const QString &type, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginUI)
    , Display(nullptr)
    , mainWindow(qobject_cast<MainWindow*>(parent))
{
    ui->setupUi(this);

    loginType = type;

    ui->passwordTextBox->setEchoMode(QLineEdit::Password);
}


LoginUI::~LoginUI()
{
    delete ui;
}


// =========================================================
// LOGIN
// =========================================================

void LoginUI::on_loginButton_clicked()
{
    QString username =
        ui->usernameTextBox->text().trimmed();

    QString password =
        ui->passwordTextBox->text().trimmed();


    // -----------------------------------------------------
    // Empty fields
    // -----------------------------------------------------

    if (username.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Login",
            "Please enter username and password."
            );

        return;
    }


    // -----------------------------------------------------
    // Select CSV
    // -----------------------------------------------------

    QString fileName;

    if (loginType == "Student")
    {
        fileName = "data/Users.csv";
    }
    else if (loginType == "Faculty" ||
             loginType == "Admin")
    {
        fileName = "data/Faculty.csv";
    }
    else
    {
        QMessageBox::critical(
            this,
            "Error",
            "Unknown login type."
            );

        return;
    }


    // -----------------------------------------------------
    // Open CSV
    // -----------------------------------------------------

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(
            this,
            "File Error",
            "Could not open:\n" + fileName
            );

        return;
    }


    QTextStream in(&file);


    bool firstLine = true;
    bool loginSuccessful = false;

    QString userID;
    QString userName;
    QString userRole;

    QString books;
    QString warnings;
    QString feeStatus;


    // =====================================================
    // READ CSV
    // =====================================================

    while (!in.atEnd())
    {
        QString qLine = in.readLine();


        // -------------------------------------------------
        // Skip header
        // -------------------------------------------------

        if (firstLine)
        {
            firstLine = false;
            continue;
        }


        if (qLine.trimmed().isEmpty())
        {
            continue;
        }


        // -------------------------------------------------
        // Convert to raw char*
        // -------------------------------------------------

        QByteArray byteLine = qLine.toUtf8();

        const char *line = byteLine.constData();


        // -------------------------------------------------
        // RAW PARSER
        // -------------------------------------------------

        char fields[7][600];

        int fieldIdx = 0;
        int charIdx = 0;
        int i = 0;


        while (line[i] != '\0' &&
               line[i] != '\n' &&
               line[i] != '\r')
        {
            if (line[i] == ',')
            {
                if (fieldIdx < 7)
                {
                    fields[fieldIdx][charIdx] = '\0';
                }

                fieldIdx++;
                charIdx = 0;

                if (fieldIdx >= 7)
                {
                    break;
                }
            }
            else
            {
                if (fieldIdx < 7 &&
                    charIdx < 599)
                {
                    fields[fieldIdx][charIdx] =
                        line[i];

                    charIdx++;
                }
            }

            i++;
        }


        // Finish last field

        if (fieldIdx < 7)
        {
            fields[fieldIdx][charIdx] = '\0';
            fieldIdx++;
        }


        // -------------------------------------------------
        // Need at least 4 fields
        // -------------------------------------------------

        if (fieldIdx < 4)
        {
            continue;
        }


        // -------------------------------------------------
        // Common fields
        //
        // 0 = ID
        // 1 = Username
        // 2 = Name
        // 3 = Pass
        // -------------------------------------------------

        QString csvID =
            QString::fromUtf8(fields[0]).trimmed();

        QString csvUsername =
            QString::fromUtf8(fields[1]).trimmed();

        QString csvName =
            QString::fromUtf8(fields[2]).trimmed();

        QString csvPassword =
            QString::fromUtf8(fields[3]).trimmed();


        // -------------------------------------------------
        // Student-specific information
        // -------------------------------------------------

        if (loginType == "Student" &&
            fieldIdx >= 7)
        {
            books =
                QString::fromUtf8(fields[4]).trimmed();

            warnings =
                QString::fromUtf8(fields[5]).trimmed();

            feeStatus =
                QString::fromUtf8(fields[6]).trimmed();
        }


        // -------------------------------------------------
        // Faculty/Admin role
        // -------------------------------------------------

        if (loginType == "Faculty" ||
            loginType == "Admin")
        {
            if (fieldIdx >= 5)
            {
                userRole =
                    QString::fromUtf8(fields[4]).trimmed();
            }
        }

        if (username == csvUsername &&
            password == csvPassword)
        {
            if (loginType == "Faculty" &&
                userRole != "Faculty")
            {
                continue;
            }

            if (loginType == "Admin" &&
                userRole != "Admin")
            {
                continue;
            }

            loginSuccessful = true;

            userID = csvID;
            userName = csvName;

            break;
        }
    }


    file.close();


    if (loginSuccessful)
    {
        QMessageBox::information(
            this,
            "Login Successful",
            "Welcome, " + userName + "!"
            );

        Display = new Dashboard(
            userID,
            username,
            userName,
            loginType,
            books,
            warnings,
            feeStatus
            );

        Display->show();

        this->hide();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Login Failed",
            "Invalid username or password."
            );
    }
}

void LoginUI::on_backButton_clicked()
{
    this->hide();

    if (mainWindow != nullptr)
    {
        mainWindow->show();
    }
}

void LoginUI::on_showPasswordCheckBox_toggled(bool checked)
{
    if (checked)
    {
        ui->passwordTextBox->setEchoMode(
            QLineEdit::Normal
            );
    }
    else
    {
        ui->passwordTextBox->setEchoMode(
            QLineEdit::Password
            );
    }
}