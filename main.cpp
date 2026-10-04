#include "core/Library.h"
#include "ui/DataSetup.h"
#include "ui/MainWindow.h"
#include "ui/Theme.h"

#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("Library Management System");

    Theme::apply(app);

    // ---- load all CSV files ----
    Library library(Theme::str(DataSetup::prepareDataDirectory()));

    try
    {
        library.load();
    }
    catch (const std::exception &e)
    {
        QMessageBox::critical(nullptr, "Could not load library data", e.what());
        return 1;
    }

    // Bad rows are skipped, but tell the user about them
    if (!library.loadWarnings().empty())
    {
        QString details;
        for (const std::string &warning : library.loadWarnings())
        {
            details += "• " + Theme::qs(warning) + "\n";
        }

        QMessageBox box(QMessageBox::Warning, "Some rows were skipped",
                        "A few rows in the CSV files could not be read and were skipped.");
        box.setDetailedText(details);
        box.exec();
    }

    MainWindow window(library);
    window.show();

    return QApplication::exec();
}
