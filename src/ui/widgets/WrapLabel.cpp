#include "WrapLabel.h"

#include <QResizeEvent>


WrapLabel::WrapLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    setWordWrap(true);
}

QSize WrapLabel::minimumSizeHint() const
{
    QSize size = QLabel::minimumSizeHint();

    // Ask for as many lines as the text needs at the current width
    if (width() > 0 && !text().isEmpty())
    {
        size.setHeight(qMax(size.height(), heightForWidth(width())));
    }
    return size;
}

void WrapLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    // New width -> maybe a different number of lines -> tell the layout
    if (event->size().width() != event->oldSize().width())
    {
        updateGeometry();
    }
}
