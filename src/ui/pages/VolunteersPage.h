#ifndef VOLUNTEERSPAGE_H
#define VOLUNTEERSPAGE_H

#include "BasePage.h"
#include "model/Enums.h"

class QCheckBox;
class QLabel;
class QPushButton;
class QTableWidget;

// =========================================================
// VOLUNTEERS PAGE - admin reviews applications
// =========================================================

class VolunteersPage : public BasePage
{
    Q_OBJECT

public:
    VolunteersPage(Library &library, Person &user, QWidget *parent = nullptr);

    void refresh() override;

private slots:
    void updateButtons();

private:
    void review(ApplicationStatus decision);

    QCheckBox *m_pendingOnly;
    QPushButton *m_approve;
    QPushButton *m_reject;
    QTableWidget *m_table;
    QLabel *m_reason;
};

#endif // VOLUNTEERSPAGE_H
