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

private:
    Ui::Dashboard *ui;
    void loadCSV(const QString &fileName);
};

#endif // DASHBOARD_H