#ifndef OVERVIEWPAGE_H
#define OVERVIEWPAGE_H

#include "BasePage.h"

class QLabel;
class QTableWidget;
class StatCard;

// =========================================================
// OVERVIEW PAGE
//
// The first page after signing in. Students see their own
// borrowing status; staff see numbers for the whole library.
// =========================================================

class OverviewPage : public BasePage
{
    Q_OBJECT

public:
    OverviewPage(Library &library, Person &user, QWidget *parent = nullptr);

    void refresh() override;

private:
    void refreshStudent();
    void refreshStaff();
    static QString greeting();

    bool m_isStudent;

    StatCard *m_cards[4];
    QLabel *m_notice;
    QLabel *m_leftHeading;
    QLabel *m_rightHeading;
    QTableWidget *m_leftTable;
    QTableWidget *m_rightTable;
};

#endif // OVERVIEWPAGE_H
