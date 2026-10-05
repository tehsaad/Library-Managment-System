#ifndef DATASETUP_H
#define DATASETUP_H

#include <QString>

// =========================================================
// DATA SETUP
//
// Finds the "data" folder next to the program and, on the
// very first run, fills it with the sample CSV files that are
// built into the program (resources/seed). Existing files are
// never overwritten, so your changes are kept.
// =========================================================

class DataSetup
{
public:
    static QString prepareDataDirectory();
};

#endif // DATASETUP_H
