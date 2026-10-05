#include "FormDialog.h"
#include "ui/Theme.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


FormDialog::FormDialog(const QString &title,
                       const QString &subtitle,
                       const QString &submitText,
                       QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(title);
    setModal(true);
    setMinimumWidth(460);

    m_form = new QFormLayout;
    m_form->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_form->setHorizontalSpacing(16);
    m_form->setVerticalSpacing(12);
    m_form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    m_body = new QVBoxLayout;
    m_body->setSpacing(10);

    m_error = Theme::label("", "error");
    m_error->hide();

    auto *cancel = Theme::button("Cancel");
    m_submit = Theme::button(submitText, "primary");
    m_submit->setDefault(true);

    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_submit, &QPushButton::clicked, this, &FormDialog::accept);

    auto *buttons = new QHBoxLayout;
    buttons->addStretch();
    buttons->addWidget(cancel);
    buttons->addWidget(m_submit);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(6);
    layout->addWidget(Theme::label(title, "title"));
    if (!subtitle.isEmpty())
    {
        layout->addWidget(Theme::label(subtitle, "muted"));
    }
    layout->addSpacing(14);
    layout->addLayout(m_form);
    layout->addLayout(m_body);
    layout->addSpacing(8);
    layout->addWidget(m_error);
    layout->addSpacing(8);
    layout->addLayout(buttons);
}

void FormDialog::accept()
{
    const QString error = submit();   // virtual call -> subclass

    if (error.isEmpty())
    {
        QDialog::accept();
    }
    else
    {
        showError(error);
    }
}

QFormLayout *FormDialog::form() const { return m_form; }
QVBoxLayout *FormDialog::body() const { return m_body; }
QPushButton *FormDialog::submitButton() const { return m_submit; }

void FormDialog::showError(const QString &message)
{
    m_error->setText(message);
    m_error->setVisible(!message.isEmpty());
    adjustSize();
}
