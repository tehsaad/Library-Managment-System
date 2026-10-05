#ifndef HISTORYPAGE_H
#define HISTORYPAGE_H

#include "BasePage.h"

class QComboBox;
class QLabel;
class QLineEdit;
class QTableWidget;

// =========================================================
// HISTORY PAGE - read-only activity log
// =========================================================

class HistoryPage : public BasePage
{
    Q_OBJECT

public:
    HistoryPage(Library &library, Person &user, QWidget *parent = nullptr);

    void refresh() override;

private:
    static QString readable(const QString &actionName);

    QLineEdit *m_search;
    QComboBox *m_action;
    QTableWidget *m_table;
    QLabel *m_count;
};

#endif // HISTORYPAGE_H
