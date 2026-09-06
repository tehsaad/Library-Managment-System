#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(
        const QString &id,
        const QString &username,
        const QString &name,
        const QString &role,
        const QString &books,
        const QString &warnings,
        const QString &feeStatus,
        QWidget *parent = nullptr
        );

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

    // ==========================================
    // CURRENT USER
    // ==========================================

    QString userID;
    QString username;
    QString userName;
    QString userRole;
    QString userBooks;
    QString userWarnings;
    QString userFeeStatus;
};

#endif // DASHBOARD_H