#ifndef LOANSPAGE_H
#define LOANSPAGE_H

#include "BasePage.h"

class Loan;
class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

// =========================================================
// LOANS PAGE
//
// Staff: every loan in the library ("Loans").
// Student: only their own loans ("My books").
// Same class, two behaviours, chosen in the constructor.
// =========================================================

class LoansPage : public BasePage
{
    Q_OBJECT

public:
    // Which loans the filter box shows
    enum class LoanFilter
    {
        Current,
        Overdue,
        Returned,
        All
    };

    LoansPage(Library &library, Person &user, QWidget *parent = nullptr);

    void refresh() override;

private slots:
    void returnSelected();
    void issueBook();
    void updateButtons();

private:
    bool passesFilter(const Loan &loan) const;

    bool m_ownLoansOnly;

    QComboBox *m_filter;
    QLineEdit *m_search = nullptr;
    QPushButton *m_return;
    QPushButton *m_issue = nullptr;
    QTableWidget *m_table;
    QLabel *m_count;
};

#endif // LOANSPAGE_H
