#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include <QDialog>

class QFormLayout;
class QLabel;
class QPushButton;
class QVBoxLayout;

// =========================================================
// FORM DIALOG (abstract base class)
//
// Every dialog in the program looks the same: a title, a short
// explanation, some fields, an error line and two buttons.
// This base class builds all of that once.
//
// Subclasses add their fields to form() and implement submit().
// When the user presses the main button, accept() calls
// submit():  "" means success (dialog closes), any other text
// is shown as an error and the dialog stays open.
// (This is the "template method" design pattern.)
// =========================================================

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    FormDialog(const QString &title,
               const QString &subtitle,
               const QString &submitText,
               QWidget *parent = nullptr);

    void accept() override;

protected:
    virtual QString submit() = 0;

    QFormLayout *form() const;
    QVBoxLayout *body() const;     // for widgets that are not "label: field"
    QPushButton *submitButton() const;

    void showError(const QString &message);

private:
    QFormLayout *m_form;
    QVBoxLayout *m_body;
    QLabel *m_error;
    QPushButton *m_submit;
};

#endif // FORMDIALOG_H
