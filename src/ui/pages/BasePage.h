#ifndef BASEPAGE_H
#define BASEPAGE_H

#include "ui/Theme.h"

#include <QWidget>

class Library;
class Person;
class QHBoxLayout;
class QLabel;
class QTableWidget;
class QTableWidgetItem;
class QTimer;
class QVBoxLayout;

// =========================================================
// BASE PAGE (abstract base class)
//
// Every screen inside the dashboard (Overview, Catalog,
// Loans, ...) inherits from BasePage. It gets:
//   - a title + subtitle header
//   - a "flash" message line for short confirmations
//   - helpers to build tables and ask questions
//
// Each page MUST implement refresh(), which re-reads the data
// from the Library. The dashboard calls refresh() on whatever
// page is opened, without knowing which page it is
// (polymorphism through a BasePage pointer).
// =========================================================

class BasePage : public QWidget
{
    Q_OBJECT

public:
    BasePage(Library &library,
             Person &user,
             const QString &title,
             const QString &subtitle,
             QWidget *parent = nullptr);

    virtual void refresh() = 0;

protected:
    // ---- layout ----
    QVBoxLayout *content() const;
    QHBoxLayout *addToolbar();
    void setTitle(const QString &title);
    void setSubtitle(const QString &subtitle);

    // ---- feedback ----
    void flash(const QString &message, bool warning = false);
    void showError(const QString &message);
    bool confirm(const QString &title, const QString &question);

    // ---- tables ----
    static QTableWidget *createTable(const QStringList &headers);
    static void beginFill(QTableWidget *table, int rowCount);
    static void endFill(QTableWidget *table);
    static QTableWidgetItem *cell(const QString &text, Tone tone = Tone::Neutral);
    static QTableWidgetItem *numberCell(int value);
    static void setRowKey(QTableWidget *table, int row, const QString &key);
    static QString selectedKey(const QTableWidget *table);
    static void selectKey(QTableWidget *table, const QString &key);

    Library &m_library;
    Person &m_user;

private:
    QLabel *m_title;
    QLabel *m_subtitle;
    QLabel *m_flash;
    QTimer *m_flashTimer;
    QVBoxLayout *m_content;
};

#endif // BASEPAGE_H
