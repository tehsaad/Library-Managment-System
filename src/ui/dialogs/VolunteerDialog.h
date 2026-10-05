#ifndef VOLUNTEERDIALOG_H
#define VOLUNTEERDIALOG_H

#include "FormDialog.h"

class Library;
class QComboBox;
class QLineEdit;
class QPlainTextEdit;

// =========================================================
// VOLUNTEER DIALOG - anyone can apply from the welcome screen
// =========================================================

class VolunteerDialog : public FormDialog
{
    Q_OBJECT

public:
    explicit VolunteerDialog(Library &library, QWidget *parent = nullptr);

    QString applicantName() const;

protected:
    QString submit() override;

private:
    Library &m_library;

    QLineEdit *m_name;
    QLineEdit *m_email;
    QLineEdit *m_phone;
    QComboBox *m_availability;
    QPlainTextEdit *m_reason;
};

#endif // VOLUNTEERDIALOG_H
