#ifndef VOLUNTEERDIALOG_H
#define VOLUNTEERDIALOG_H

#include <QDialog>

namespace Ui {
class VolunteerDialog;
}

class VolunteerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VolunteerDialog(QWidget *parent = nullptr);
    ~VolunteerDialog();

private slots:
    void on_submitButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::VolunteerDialog *ui;
};

#endif // VOLUNTEERDIALOG_H
