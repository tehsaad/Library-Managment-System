#ifndef LOGINUI_H
#define LOGINUI_H
#include "Dashboard.h"
#include <QMainWindow>

namespace Ui {
class LoginUI;
}

class LoginUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginUI(QWidget *parent = nullptr);
    ~LoginUI();

private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginUI *ui;

    Dashboard *Display;
};

#endif // LOGINUI_H
