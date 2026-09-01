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


void Dashboard::saveCSV(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(
            this,
            "CSV Error",
            "Could not save:\n" + fileName
            );

        return;
    }

    QTextStream out(&file);

    // Write headers
    for (int column = 0;
         column < ui->dataTable->columnCount();
         column++)
    {
        if (column > 0)
            out << ",";

        QTableWidgetItem *header =
            ui->dataTable->horizontalHeaderItem(column);

        if (header)
            out << header->text();
    }

    out << "\n";


    // Write table data
    for (int row = 0;
         row < ui->dataTable->rowCount();
         row++)
    {
        for (int column = 0;
             column < ui->dataTable->columnCount();
             column++)
        {
            if (column > 0)
                out << ",";

            QTableWidgetItem *item =
                ui->dataTable->item(row, column);

            if (item)
                out << item->text();
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

void Dashboard::on_logoutButton_clicked()
{
    close();
}

void Dashboard::on_booksButton_clicked()
{
    loadCSV("data/Books.csv");
}

void Dashboard::on_historyButton_clicked()
{
    loadCSV("data/History.csv");
}


void Dashboard::on_userButton_clicked()
{
    loadCSV("data/Users.csv");
}

void Dashboard::on_facultyButton_clicked()
{
    loadCSV("data/Faculty.csv");
}


void Dashboard::on_saveButton_clicked()
{
    saveCSV("data/Books.csv");
}

