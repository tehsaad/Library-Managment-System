#include "Dashboard.h"
#include "ui_Dashboard.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMessageBox>


// =========================================================
// CONSTRUCTOR
// =========================================================

Dashboard::Dashboard(
    const QString &id,
    const QString &username,
    const QString &name,
    const QString &role,
    const QString &books,
    const QString &warnings,
    const QString &feeStatus,
    QWidget *parent
    )
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);

    // ==========================================
    // STORE CURRENT USER
    // ==========================================

    userID = id;
    this->username = username;
    userName = name;
    userRole = role;
    userBooks = books;
    userWarnings = warnings;
    userFeeStatus = feeStatus;
}


// =========================================================
// DESTRUCTOR
// =========================================================

Dashboard::~Dashboard()
{
    delete ui;
}


// =========================================================
// LOAD CSV
// =========================================================

void Dashboard::loadCSV(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(
            this,
            "CSV Error",
            "Could not open:\n" + fileName
            );

        return;
    }

    QTextStream in(&file);

    // Clear previous table
    ui->dataTable->clearContents();
    ui->dataTable->setRowCount(0);


    // ==========================================
    // CHECK EMPTY FILE
    // ==========================================

    if (in.atEnd())
    {
        file.close();
        return;
    }


    // ==========================================
    // READ HEADER
    // ==========================================

    QString headerLine = in.readLine();

    QStringList headers =
        headerLine.split(",");

    ui->dataTable->setColumnCount(headers.size());

    ui->dataTable->setHorizontalHeaderLabels(headers);


    // ==========================================
    // READ DATA
    // ==========================================

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.trimmed().isEmpty())
        {
            continue;
        }


        QStringList values =
            line.split(",");


        int row =
            ui->dataTable->rowCount();

        ui->dataTable->insertRow(row);


        for (int column = 0;
             column < values.size() &&
             column < ui->dataTable->columnCount();
             column++)
        {
            ui->dataTable->setItem(
                row,
                column,
                new QTableWidgetItem(
                    values[column].trimmed()
                    )
                );
        }
    }


    file.close();
}


// =========================================================
// SAVE CSV
// =========================================================

void Dashboard::saveCSV(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(
            QIODevice::WriteOnly |
            QIODevice::Text))
    {
        QMessageBox::warning(
            this,
            "CSV Error",
            "Could not save:\n" + fileName
            );

        return;
    }


    QTextStream out(&file);


    // ==========================================
    // WRITE HEADERS
    // ==========================================

    for (int column = 0;
         column < ui->dataTable->columnCount();
         column++)
    {
        if (column > 0)
        {
            out << ",";
        }


        QTableWidgetItem *header =
            ui->dataTable->horizontalHeaderItem(column);


        if (header)
        {
            out << header->text();
        }
    }

    out << "\n";


    // ==========================================
    // WRITE TABLE DATA
    // ==========================================

    for (int row = 0;
         row < ui->dataTable->rowCount();
         row++)
    {
        for (int column = 0;
             column < ui->dataTable->columnCount();
             column++)
        {
            if (column > 0)
            {
                out << ",";
            }


            QTableWidgetItem *item =
                ui->dataTable->item(row, column);


            if (item)
            {
                out << item->text();
            }
        }

        out << "\n";
    }


    file.close();


    QMessageBox::information(
        this,
        "CSV Saved",
        "Changes saved successfully!"
        );
}


// =========================================================
// LOGOUT
// =========================================================

void Dashboard::on_logoutButton_clicked()
{
    close();
}


// =========================================================
// BOOKS
// =========================================================

void Dashboard::on_booksButton_clicked()
{
    loadCSV("data/Books.csv");
}


// =========================================================
// HISTORY
// =========================================================

void Dashboard::on_historyButton_clicked()
{
    loadCSV("data/History.csv");
}


// =========================================================
// USERS
// =========================================================

void Dashboard::on_userButton_clicked()
{
    loadCSV("data/Users.csv");
}


// =========================================================
// FACULTY / ADMIN
// =========================================================

void Dashboard::on_facultyButton_clicked()
{
    loadCSV("data/Faculty.csv");
}


// =========================================================
// SAVE
// =========================================================

void Dashboard::on_saveButton_clicked()
{
    QMessageBox::information(
        this,
        "Save",
        "The Save functionality will be connected "
        "to the currently selected data in a later step."
        );
}