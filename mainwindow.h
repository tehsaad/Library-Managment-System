#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class LoginUI;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_studentButton_clicked();

    void on_adminButton_clicked();

    void on_facultyButton_clicked();

    void on_volunteerButton_clicked();

private:
    Ui::MainWindow *ui;

    LoginUI *logUI;
};

#endif // MAINWINDOW_H