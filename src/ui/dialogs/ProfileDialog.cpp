#include "ProfileDialog.h"
#include "core/Library.h"
#include "ui/Theme.h"

#include <QFormLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>


ProfileDialog::ProfileDialog(Library &library, Person &user, QWidget *parent)
    : FormDialog("Your profile", "", "Save", parent)
    , m_library(library)
    , m_user(user)
    , m_passwordChanged(false)
{
    // ---- details card (polymorphic) ----
    auto *card = new QFrame;
    card->setProperty("card", true);

    auto *details = new QFormLayout(card);
    details->setContentsMargins(18, 14, 18, 14);
    details->setHorizontalSpacing(24);
    details->setVerticalSpacing(8);

    for (const auto &[label, value] : user.profileDetails())
    {
        auto *valueLabel = new QLabel(Theme::qs(value));
        valueLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
        details->addRow(Theme::label(Theme::qs(label), "muted"), valueLabel);
    }

    form()->addRow(card);

    // ---- change password ----
    m_current = new QLineEdit;
    m_new = new QLineEdit;
    m_confirm = new QLineEdit;

    for (QLineEdit *edit : { m_current, m_new, m_confirm })
    {
        edit->setEchoMode(QLineEdit::Password);
    }
    m_current->setPlaceholderText("Leave empty to keep your password");

    auto *heading = Theme::label("Change password", "heading");
    heading->setContentsMargins(0, 12, 0, 0);
    form()->addRow(heading);
    form()->addRow("Current", m_current);
    form()->addRow("New", m_new);
    form()->addRow("Confirm", m_confirm);
}

QString ProfileDialog::submit()
{
    const bool nothingTyped =
        m_current->text().isEmpty() && m_new->text().isEmpty() && m_confirm->text().isEmpty();

    if (nothingTyped)
    {
        return QString();   // just closing the profile
    }

    if (m_new->text() != m_confirm->text())
    {
        return "The new passwords do not match.";
    }

    try
    {
        m_library.changePassword(m_user, m_current->text().toStdString(), m_new->text().toStdString());
    }
    catch (const std::exception &e)
    {
        return e.what();
    }

    m_passwordChanged = true;
    return QString();
}

bool ProfileDialog::passwordChanged() const
{
    return m_passwordChanged;
}
