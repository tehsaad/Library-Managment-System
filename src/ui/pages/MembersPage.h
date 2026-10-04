#ifndef MEMBERSPAGE_H
#define MEMBERSPAGE_H

#include "BasePage.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

// =========================================================
// MEMBERS PAGE
//
// Faculty can look at students; only an Admin
// (canManageMembers()) gets the Add / Edit / Remove buttons.
// =========================================================

class MembersPage : public BasePage
{
    Q_OBJECT

public:
    MembersPage(Library &library, Person &user, QWidget *parent = nullptr);

    void refresh() override;

private slots:
    void addMember();
    void editMember();
    void removeMember();
    void updateButtons();

private:
    QLineEdit *m_search;
    QTableWidget *m_table;
    QLabel *m_count;

    QPushButton *m_add = nullptr;
    QPushButton *m_edit = nullptr;
    QPushButton *m_remove = nullptr;
};

#endif // MEMBERSPAGE_H
