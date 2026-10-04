#include "Theme.h"
#include "widgets/WrapLabel.h"

#include <QApplication>
#include <QFile>
#include <QFont>
#include <QLabel>
#include <QPushButton>


void Theme::apply(QApplication &app)
{
    // Georgia is the heading font; fall back to similar serif
    // fonts on computers that do not have it.
    QFont::insertSubstitutions("Georgia",
                               { "Charter", "Noto Serif", "DejaVu Serif",
                                 "Liberation Serif", "Times New Roman" });

    QFont body = app.font();
    body.setFamilies({ "Segoe UI", "Inter", "Noto Sans", "Helvetica Neue", "Arial" });
    body.setPointSize(10);
    app.setFont(body);

    QFile file(":/theme.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        app.setStyleSheet(QString::fromUtf8(file.readAll()));
    }
}

QColor Theme::color(Tone tone)
{
    switch (tone)
    {
    case Tone::Good:    return QColor("#4E7A51");
    case Tone::Warning: return QColor("#A86B1E");
    case Tone::Bad:     return QColor("#B23B3B");
    case Tone::Accent:  return QColor("#C96442");
    case Tone::Neutral: break;
    }
    return QColor("#6E6A60");
}

QLabel *Theme::label(const QString &text, const QString &role, QWidget *parent)
{
    const bool boxed = role == "error" || role == "notice" || role == "success";
    const bool wraps = boxed || role == "muted" || role == "small";

    // Text that may need several lines gets a WrapLabel (a QLabel subclass)
    QLabel *label = wraps ? new WrapLabel(text, parent) : new QLabel(text, parent);
    label->setProperty("textRole", role);

    if (boxed)
    {
        // Margins (not stylesheet padding) so the height calculation includes them
        label->setContentsMargins(10, 8, 10, 8);
    }
    return label;
}

QPushButton *Theme::button(const QString &text, const QString &variant, QWidget *parent)
{
    auto *button = new QPushButton(text, parent);
    button->setCursor(Qt::PointingHandCursor);

    if (!variant.isEmpty())
    {
        button->setProperty("variant", variant);
    }
    return button;
}

QString Theme::qs(const std::string &text)
{
    return QString::fromStdString(text);
}

std::string Theme::str(const QString &text)
{
    return text.trimmed().toStdString();
}
