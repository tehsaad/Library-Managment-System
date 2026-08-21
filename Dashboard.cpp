#include "Dashboard.h"
#include "ui_Dashboard.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMessageBox>

Dashboard::Dashboard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dashboard)
{
    ui->setupUi(this);
}

Dashboard::~Dashboard()
{
    delete ui;
}


// =========================================================
// LOAD CSV FILE
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

    QMessageBox::information(
        this,
        "Success",
        "CSV file opened successfully!"
        );

    QTextStream in(&file);

    ui->dataTable->clearContents();
    ui->dataTable->setRowCount(0);

    if (in.atEnd())
    {
        file.close();
        return;
    }

    QString headerLine = in.readLine();

    QStringList headers = headerLine.split(",");

    ui->dataTable->setColumnCount(headers.size());
    ui->dataTable->setHorizontalHeaderLabels(headers);

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.trimmed().isEmpty())
            continue;

        QStringList values = line.split(",");

        int row = ui->dataTable->rowCount();

        ui->dataTable->insertRow(row);

        for (int column = 0;
             column < values.size() &&
             column < ui->dataTable->columnCount();
             column++)
        {
            ui->dataTable->setItem(
                row,
                column,
                new QTableWidgetItem(values[column].trimmed())
                );
        }
    }

    file.close();
}


// =========================================================
// LOGOUT BUTTON
// =========================================================

void Dashboard::on_logoutButton_clicked()
{
    close();
}


// =========================================================
// BOOKS BUTTON
// =========================================================

void Dashboard::on_booksButton_clicked()
{
    loadCSV("Books.csv");
}