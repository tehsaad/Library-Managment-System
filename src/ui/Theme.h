#ifndef THEME_H
#define THEME_H

#include <QColor>
#include <QString>

#include <string>

class QApplication;
class QLabel;
class QPushButton;
class QWidget;

// =========================================================
// THEME
//
// Loads the stylesheet (resources/theme.qss) and offers small
// helpers so every screen builds labels and buttons the same
// way. Also converts between std::string (used by the model)
// and QString (used by Qt).
// =========================================================

// Colours used for status text in tables
enum class Tone
{
    Neutral,
    Good,
    Warning,
    Bad,
    Accent
};

class Theme
{
public:
    static void apply(QApplication &app);

    static QColor color(Tone tone);

    // ---- widget factories ----
    // role: "display", "title", "heading", "eyebrow", "muted", "small",
    //       "error", "notice", "success"
    static QLabel *label(const QString &text, const QString &role, QWidget *parent = nullptr);
    static QPushButton *button(const QString &text, const QString &variant = QString(),
                               QWidget *parent = nullptr);

    // ---- std::string <-> QString ----
    static QString qs(const std::string &text);
    static std::string str(const QString &text);
};

#endif // THEME_H
