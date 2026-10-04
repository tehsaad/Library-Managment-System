#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include "model/Enums.h"

#include <QWidget>

// =========================================================
// WELCOME PAGE
//
// "Who are you?" - Student, Faculty, Admin, or apply to
// volunteer. It only emits signals; MainWindow decides what
// happens next.
// =========================================================

class WelcomePage : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomePage(QWidget *parent = nullptr);

signals:
    void roleChosen(Role role);
    void volunteerChosen();
};

#endif // WELCOMEPAGE_H
