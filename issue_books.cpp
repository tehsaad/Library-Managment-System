#include "issue_books.h"
#include "ui_issue_books.h"

add_Books::add_Books(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_Books)
{
    ui->setupUi(this);
}

add_Books::~add_Books()
{
    delete ui;
}
