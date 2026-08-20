#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "loginui.h"
#include <QMainWindow>

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
    ~MainWindow() override;

private slots:
    void on_studentButton_clicked();

private:
    Ui::MainWindow *ui;

    LoginUI *logUI;


};
#endif // MAINWINDOW_H
