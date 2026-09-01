#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QWidget *parent = nullptr);

    ~Dashboard();

private slots:
    void on_logoutButton_clicked();

    void on_booksButton_clicked();

    void on_historyButton_clicked();

    void on_userButton_clicked();

    void on_facultyButton_clicked();

    void on_saveButton_clicked();

private:
    Ui::Dashboard *ui;
    void loadCSV(const QString &fileName);
    void saveCSV(const QString &fileName);
};

#endif // DASHBOARD_H