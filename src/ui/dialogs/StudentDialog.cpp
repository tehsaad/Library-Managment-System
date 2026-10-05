#include "StudentDialog.h"
#include "core/Library.h"
#include "ui/Theme.h"

#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>


StudentDialog::StudentDialog(Library &library, const Person &user, const Student *existing, QWidget *parent)
    : FormDialog(existing ? "Edit member" : "Add a member",
                 existing ? "Leave the password empty to keep the current one."
                          : "The student can sign in straight away with this username and password.",
                 existing ? "Save changes" : "Add member",
                 parent)
    , m_library(library)
    , m_user(user)
    , m_studentId(existing ? existing->getId() : "")
{
    m_name = new QLineEdit;
    m_name->setPlaceholderText("Full name");

    m_username = new QLineEdit;
    m_username->setPlaceholderText("Used to sign in");

    m_password = new QLineEdit;
    m_password->setEchoMode(QLineEdit::Password);
    m_password->setPlaceholderText(existing ? "Unchanged" : "At least 3 characters");

    // The combo box items come straight from the enum
    m_fee = new QComboBox;
    for (FeeStatus status : { FeeStatus::Paid, FeeStatus::Pending })
    {
        m_fee->addItem(Theme::qs(EnumText::toString(status)), static_cast<int>(status));
    }

    m_warnings = new QSpinBox;
    m_warnings->setRange(0, 99);

    form()->addRow("Name", m_name);
    form()->addRow("Username", m_username);
    form()->addRow("Password", m_password);
    form()->addRow("Fee status", m_fee);

    if (existing != nullptr)
    {
        m_name->setText(Theme::qs(existing->getName()));
        m_username->setText(Theme::qs(existing->getUsername()));
        m_fee->setCurrentIndex(m_fee->findData(static_cast<int>(existing->getFeeStatus())));
        m_warnings->setValue(existing->getWarnings());

        form()->addRow("Warnings", m_warnings);
    }
}

QString StudentDialog::submit()
{
    const FeeStatus fee = static_cast<FeeStatus>(m_fee->currentData().toInt());

    try
    {
        if (m_studentId.empty())
        {
            m_library.addStudent(Theme::str(m_name->text()),
                                 Theme::str(m_username->text()),
                                 Theme::str(m_password->text()),
                                 fee,
                                 m_user);
        }
        else
        {
            m_library.updateStudent(m_studentId,
                                    Theme::str(m_name->text()),
                                    Theme::str(m_username->text()),
                                    Theme::str(m_password->text()),
                                    fee,
                                    m_warnings->value(),
                                    m_user);
        }
    }
    catch (const std::exception &e)
    {
        return e.what();
    }

    return QString();
}
