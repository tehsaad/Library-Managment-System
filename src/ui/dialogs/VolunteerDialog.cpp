#include "VolunteerDialog.h"
#include "core/Library.h"
#include "ui/Theme.h"

#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>


VolunteerDialog::VolunteerDialog(Library &library, QWidget *parent)
    : FormDialog("Volunteer with us",
                 "Help shelve books, run reading sessions or digitise the catalog. "
                 "An administrator will review your application.",
                 "Submit application",
                 parent)
    , m_library(library)
{
    m_name = new QLineEdit;
    m_name->setPlaceholderText("Your full name");

    m_email = new QLineEdit;
    m_email->setPlaceholderText("name@example.com");

    m_phone = new QLineEdit;
    m_phone->setPlaceholderText("Optional");

    m_availability = new QComboBox;
    m_availability->addItems({ "Weekdays", "Weekday evenings", "Weekends", "Flexible" });

    m_reason = new QPlainTextEdit;
    m_reason->setPlaceholderText("Why would you like to volunteer?");
    m_reason->setFixedHeight(90);

    form()->addRow("Name", m_name);
    form()->addRow("Email", m_email);
    form()->addRow("Phone", m_phone);
    form()->addRow("Availability", m_availability);
    form()->addRow("Reason", m_reason);
}

QString VolunteerDialog::submit()
{
    VolunteerApplication application(0,
                                     Theme::str(m_name->text()),
                                     Theme::str(m_email->text()),
                                     Theme::str(m_phone->text()),
                                     Theme::str(m_availability->currentText()),
                                     Theme::str(m_reason->toPlainText()));

    try
    {
        m_library.submitApplication(application);
    }
    catch (const std::exception &e)
    {
        return e.what();
    }

    return QString();
}

QString VolunteerDialog::applicantName() const
{
    return m_name->text().trimmed();
}
