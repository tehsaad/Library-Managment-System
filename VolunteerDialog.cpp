#include "VolunteerDialog.h"
#include "ui_VolunteerDialog.h"

#include <QMessageBox>


VolunteerDialog::VolunteerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::VolunteerDialog)
{
    ui->setupUi(this);
}


VolunteerDialog::~VolunteerDialog()
{
    delete ui;
}


// =========================================================
// SUBMIT APPLICATION
// =========================================================

void VolunteerDialog::on_submitButton_clicked()
{
    QString name =
        ui->nameTextBox->text().trimmed();


    if (name.isEmpty())
    {
        QMessageBox::warning(
            this,
            "Volunteer Application",
            "Please enter your name."
            );

        return;
    }


    QMessageBox::information(
        this,
        "Application Submitted",
        "Thank you, " + name +
            "!\n\n"
            "Your volunteer application has been submitted.\n\n"
            "Please wait for administrator approval."
        );


    accept();
}


// =========================================================
// CANCEL
// =========================================================

void VolunteerDialog::on_cancelButton_clicked()
{
    reject();
}