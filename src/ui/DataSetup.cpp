#include "DataSetup.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QStringList>


QString DataSetup::prepareDataDirectory()
{
    const QString dataPath = QDir(QCoreApplication::applicationDirPath()).filePath("data");
    QDir().mkpath(dataPath);

    const QStringList seedFiles = {
        "Books.csv", "Users.csv", "Faculty.csv", "Loans.csv", "History.csv", "Volunteers.csv"
    };

    for (const QString &fileName : seedFiles)
    {
        const QString target = QDir(dataPath).filePath(fileName);

        if (!QFile::exists(target) && QFile::copy(":/seed/" + fileName, target))
        {
            // Files copied out of resources are read-only; make them writable
            QFile::setPermissions(target, QFile::ReadOwner | QFile::WriteOwner |
                                              QFile::ReadGroup | QFile::ReadOther);
        }
    }

    return dataPath;
}
