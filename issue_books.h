#ifndef ISSUE_BOOKS_H
#define ISSUE_BOOKS_H

#include <QDialog>

namespace Ui {
class add_Books;
}

class add_Books : public QDialog
{
    Q_OBJECT

public:
    explicit add_Books(QWidget *parent = nullptr);
    ~add_Books();

private:
    Ui::add_Books *ui;
};

#endif // ISSUE_BOOKS_H
