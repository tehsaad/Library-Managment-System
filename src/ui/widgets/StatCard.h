#ifndef STATCARD_H
#define STATCARD_H

#include <QFrame>

class QLabel;

// =========================================================
// STAT CARD
//
// A small card with a title, a big number and a caption,
// used on the Overview page.
// =========================================================

class StatCard : public QFrame
{
    Q_OBJECT

public:
    explicit StatCard(const QString &title, QWidget *parent = nullptr);

    void setValue(const QString &value, const QString &caption = QString());

private:
    QLabel *m_value;
    QLabel *m_caption;
};

#endif // STATCARD_H
