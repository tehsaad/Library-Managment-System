#include "BasePage.h"

#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QStyle>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>


BasePage::BasePage(Library &library,
                   Person &user,
                   const QString &title,
                   const QString &subtitle,
                   QWidget *parent)
    : QWidget(parent)
    , m_library(library)
    , m_user(user)
{
    setObjectName("page");

    m_title = Theme::label(title, "title");
    m_subtitle = Theme::label(subtitle, "muted");
    m_subtitle->setVisible(!subtitle.isEmpty());

    m_flash = Theme::label("", "notice");
    m_flash->hide();

    m_flashTimer = new QTimer(this);
    m_flashTimer->setSingleShot(true);
    connect(m_flashTimer, &QTimer::timeout, m_flash, &QLabel::hide);

    m_content = new QVBoxLayout;
    m_content->setSpacing(14);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(36, 30, 36, 30);
    layout->setSpacing(4);
    layout->addWidget(m_title);
    layout->addWidget(m_subtitle);
    layout->addSpacing(16);
    layout->addWidget(m_flash);
    layout->addLayout(m_content, 1);
}


// =========================================================
// LAYOUT
// =========================================================

QVBoxLayout *BasePage::content() const
{
    return m_content;
}

QHBoxLayout *BasePage::addToolbar()
{
    auto *toolbar = new QHBoxLayout;
    toolbar->setSpacing(8);
    m_content->addLayout(toolbar);
    return toolbar;
}

void BasePage::setTitle(const QString &title)
{
    m_title->setText(title);
}

void BasePage::setSubtitle(const QString &subtitle)
{
    m_subtitle->setText(subtitle);
    m_subtitle->setVisible(!subtitle.isEmpty());
}


// =========================================================
// FEEDBACK
// =========================================================

void BasePage::flash(const QString &message, bool warning)
{
    // amber "notice" for warnings, green "success" otherwise
    m_flash->setProperty("textRole", warning ? "notice" : "success");
    m_flash->style()->unpolish(m_flash);
    m_flash->style()->polish(m_flash);

    m_flash->setText(warning ? message : "✓  " + message);
    m_flash->show();
    m_flashTimer->start(warning ? 9000 : 5000);
}

void BasePage::showError(const QString &message)
{
    QMessageBox::warning(this, "Not possible", message);
}

bool BasePage::confirm(const QString &title, const QString &question)
{
    return QMessageBox::question(this, title, question,
                                 QMessageBox::Yes | QMessageBox::Cancel,
                                 QMessageBox::Cancel) == QMessageBox::Yes;
}


// =========================================================
// TABLES
// =========================================================

QTableWidget *BasePage::createTable(const QStringList &headers)
{
    auto *table = new QTableWidget(0, headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);     // edit through dialogs
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setAlternatingRowColors(true);
    table->setShowGrid(false);
    table->setWordWrap(false);
    table->setFocusPolicy(Qt::StrongFocus);
    table->verticalHeader()->hide();
    table->verticalHeader()->setDefaultSectionSize(38);
    table->horizontalHeader()->setHighlightSections(false);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSortIndicator(-1, Qt::AscendingOrder);   // keep our order until a header is clicked
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    return table;
}

void BasePage::beginFill(QTableWidget *table, int rowCount)
{
    // Sorting while inserting would move rows around under us
    table->setSortingEnabled(false);
    table->clearContents();
    table->setRowCount(rowCount);
}

void BasePage::endFill(QTableWidget *table)
{
    table->setSortingEnabled(true);

    // Size every column to its text (max 320px). The last column is
    // left alone: it stretches to fill the rest of the table.
    for (int column = 0; column < table->columnCount() - 1; column++)
    {
        table->resizeColumnToContents(column);
        if (table->columnWidth(column) > 320)
        {
            table->setColumnWidth(column, 320);
        }
    }
}

QTableWidgetItem *BasePage::cell(const QString &text, Tone tone)
{
    auto *item = new QTableWidgetItem(text);

    if (tone != Tone::Neutral)
    {
        item->setForeground(Theme::color(tone));
        QFont font = item->font();
        font.setWeight(QFont::DemiBold);
        item->setFont(font);
    }
    return item;
}

QTableWidgetItem *BasePage::numberCell(int value)
{
    // Storing a number (not text) makes the column sort 2 < 10
    auto *item = new QTableWidgetItem;
    item->setData(Qt::DisplayRole, value);
    return item;
}

void BasePage::setRowKey(QTableWidget *table, int row, const QString &key)
{
    // The key is hidden inside column 0, so it survives sorting
    if (QTableWidgetItem *item = table->item(row, 0))
    {
        item->setData(Qt::UserRole, key);
    }
}

QString BasePage::selectedKey(const QTableWidget *table)
{
    const int row = table->currentRow();
    if (row < 0 || table->selectionModel()->selectedRows().isEmpty())
    {
        return QString();
    }

    const QTableWidgetItem *item = table->item(row, 0);
    return item ? item->data(Qt::UserRole).toString() : QString();
}

void BasePage::selectKey(QTableWidget *table, const QString &key)
{
    if (key.isEmpty())
    {
        return;
    }

    for (int row = 0; row < table->rowCount(); row++)
    {
        const QTableWidgetItem *item = table->item(row, 0);
        if (item && item->data(Qt::UserRole).toString() == key)
        {
            table->selectRow(row);
            return;
        }
    }
}
