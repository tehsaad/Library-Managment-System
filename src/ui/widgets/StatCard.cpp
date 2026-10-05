#include "StatCard.h"
#include "ui/Theme.h"

#include <QLabel>
#include <QVBoxLayout>


StatCard::StatCard(const QString &title, QWidget *parent)
    : QFrame(parent)
{
    setProperty("card", true);
    setMinimumWidth(170);

    m_value = new QLabel("-");
    m_value->setProperty("statValue", true);

    m_caption = Theme::label("", "small");

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(18, 16, 18, 16);
    layout->setSpacing(4);
    layout->addWidget(Theme::label(title, "muted"));
    layout->addWidget(m_value);
    layout->addWidget(m_caption);
}

void StatCard::setValue(const QString &value, const QString &caption)
{
    m_value->setText(value);
    m_caption->setText(caption);
    m_caption->setVisible(!caption.isEmpty());
}
