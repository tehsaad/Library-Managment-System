#include "RoleCard.h"
#include "ui/Theme.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>


RoleCard::RoleCard(const QString &letter,
                   const QString &title,
                   const QString &description,
                   QWidget *parent)
    : QPushButton(parent)
{
    setObjectName("roleCard");
    setCursor(Qt::PointingHandCursor);
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);
    setAccessibleName(title);
    setAccessibleDescription(description);

    auto *badge = new QLabel(letter);
    badge->setProperty("badge", true);
    badge->setFixedSize(36, 36);
    badge->setAlignment(Qt::AlignCenter);

    auto *titleLabel = Theme::label(title, "heading");
    auto *descriptionLabel = Theme::label(description, "muted");

    auto *text = new QVBoxLayout;
    text->setSpacing(4);
    text->addWidget(titleLabel);
    text->addWidget(descriptionLabel);

    auto *layout = new QHBoxLayout(this);
    layout->setContentsMargins(20, 18, 20, 18);
    layout->setSpacing(16);
    layout->addWidget(badge, 0, Qt::AlignTop);
    layout->addLayout(text, 1);

    // Let clicks on the labels reach the button underneath
    for (QLabel *label : { badge, titleLabel, descriptionLabel })
    {
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

bool RoleCard::hasHeightForWidth() const
{
    return true;
}

int RoleCard::heightForWidth(int width) const
{
    return layout()->totalHeightForWidth(width);
}

QSize RoleCard::sizeHint() const
{
    const int width = 360;
    return QSize(width, heightForWidth(width));
}

QSize RoleCard::minimumSizeHint() const
{
    const int width = 280;
    return QSize(width, heightForWidth(width));
}
