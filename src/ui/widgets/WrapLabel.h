#ifndef WRAPLABEL_H
#define WRAPLABEL_H

#include <QLabel>

// =========================================================
// WRAP LABEL
//
// A QLabel whose text wraps onto several lines. Plain QLabel
// often gets squeezed to one line by Qt layouts, cutting the
// text off. This subclass overrides two virtual functions so
// its minimum height is always "enough lines for my width".
//
// Because WrapLabel "is a" QLabel, it can be used anywhere a
// QLabel* is expected (see Theme::label).
// =========================================================

class WrapLabel : public QLabel
{
    Q_OBJECT

public:
    explicit WrapLabel(const QString &text = QString(), QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;

protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // WRAPLABEL_H
