#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

// =========================================================
// FILE HANDLER
//
// The ONLY class that touches the disk. Everything else asks
// it for rows of text, so changing the storage later (e.g. to
// a database) would only change this class.
//
// Uses plain C++ (std::ifstream / std::ofstream), no Qt.
// Throws FileException when something goes wrong.
// =========================================================

// One CSV file in memory: the header line + all data rows
struct CsvTable
{
    std::vector<std::string> header;
    std::vector<std::vector<std::string>> rows;
};

class FileHandler
{
public:
    explicit FileHandler(const std::string &dataDirectory);

    const std::string &directory() const;
    std::string fullPath(const std::string &fileName) const;
    bool exists(const std::string &fileName) const;

    CsvTable readCsv(const std::string &fileName) const;

    // Writes to "<file>.tmp" first and then renames it, so a crash
    // half-way through never leaves a broken file behind.
    void writeCsv(const std::string &fileName,
                  const std::vector<std::string> &header,
                  const std::vector<std::vector<std::string>> &rows) const;

    // Creates the file with just a header line if it is missing
    void createIfMissing(const std::string &fileName,
                         const std::vector<std::string> &header) const;

private:
    std::string m_directory;
};

#endif // FILEHANDLER_H
