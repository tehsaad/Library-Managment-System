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


// ==========================================
// ADMIN LOGIN
// ==========================================

void MainWindow::on_adminButton_clicked()
{
    hide();

    logUI = new LoginUI("Admin", this);
    logUI->show();
}


// ==========================================
// STUDENT LOGIN
// ==========================================

void MainWindow::on_studentButton_clicked()
{
    hide();

    logUI = new LoginUI("Student", this);
    logUI->show();
}


// ==========================================
// FACULTY LOGIN
// ==========================================

void MainWindow::on_facultyButton_clicked()
{
    hide();

    logUI = new LoginUI("Faculty", this);
    logUI->show();
}


// ==========================================
// VOLUNTEER LOGIN
// ==========================================

void MainWindow::on_volunteerButton_clicked()
{
    hide();

    logUI = new LoginUI("Volunteer", this);
    logUI->show();
}