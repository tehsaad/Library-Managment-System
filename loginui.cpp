#include "loginui.h"
#include "ui_loginui.h"
#include "Dashboard.h"

LoginUI::LoginUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginUI)
{
    ui->setupUi(this);
}

LoginUI::~LoginUI()
{
    delete ui;
}

void LoginUI::on_loginButton_clicked()
{
    hide();
    Display  = new Dashboard(this);
    Display->show();
}