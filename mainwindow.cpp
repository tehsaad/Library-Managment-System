#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_studentButton_clicked()
{
    hide();
    logUI  = new LoginUI(this);
    logUI->show();

}

