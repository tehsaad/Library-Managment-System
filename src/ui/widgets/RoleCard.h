#ifndef ROLECARD_H
#define ROLECARD_H

#include <QPushButton>

// =========================================================
// ROLE CARD
//
// A big clickable card on the welcome screen. It inherits
// QPushButton, so it already has clicked(), focus and
// keyboard support - we only change how it looks.
// =========================================================

class RoleCard : public QPushButton
{
    Q_OBJECT

public:
    RoleCard(const QString &letter,
             const QString &title,
             const QString &description,
             QWidget *parent = nullptr);

    // QPushButton normally sizes itself from its text. Our text is in
    // labels that wrap onto two lines, so the height depends on the
    // width: we override these to ask the inner layout instead.
    bool hasHeightForWidth() const override;
    int heightForWidth(int width) const override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
};

#endif // ROLECARD_H
