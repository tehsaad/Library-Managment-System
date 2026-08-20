#include "Dashboard.h"
#include "ui_Dashboard.h"

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
void Dashboard::on_logoutButton_clicked()
{
    close();
}

