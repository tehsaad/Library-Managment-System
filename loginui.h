#ifndef LOGINUI_H
#define LOGINUI_H

#include "Dashboard.h"
#include <QMainWindow>
#include <QString>

class MainWindow;

namespace Ui {
class LoginUI;
}

class LoginUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginUI(const QString &type,
    QWidget *parent = nullptr);

    ~LoginUI();

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();
    void on_showPasswordCheckBox_toggled(bool checked);

private:
    Ui::LoginUI *ui;

    Dashboard *Display;
    MainWindow *mainWindow;

    QString loginType;
};

#endif // LOGINUI_H