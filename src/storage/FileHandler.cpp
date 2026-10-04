#include "FileHandler.h"
#include "CsvParser.h"
#include "Exceptions.h"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace
{
// u8path keeps non-English folder names working on Windows
fs::path toPath(const std::string &utf8)
{
    return fs::u8path(utf8);
}
}


FileHandler::FileHandler(const std::string &dataDirectory)
    : m_directory(dataDirectory)
{
}

const std::string &FileHandler::directory() const
{
    return m_directory;
}

std::string FileHandler::fullPath(const std::string &fileName) const
{
    return (toPath(m_directory) / toPath(fileName)).u8string();
}

bool FileHandler::exists(const std::string &fileName) const
{
    return fs::exists(toPath(fullPath(fileName)));
}


// =========================================================
// READ
// =========================================================

CsvTable FileHandler::readCsv(const std::string &fileName) const
{
    const std::string path = fullPath(fileName);
    std::ifstream file(toPath(path));

    if (!file.is_open())
    {
        throw FileException("Could not open file for reading:", path);
    }

    CsvTable table;
    std::string line;
    bool firstLine = true;

    while (std::getline(file, line))
    {
        if (firstLine)
        {
            // Files saved by Excel/Notepad may start with a UTF-8 "BOM"
            if (line.size() >= 3 && line.compare(0, 3, "\xEF\xBB\xBF") == 0)
            {
                line.erase(0, 3);
            }
        }

        if (CsvParser::trim(line).empty())
        {
            continue;
        }

        if (firstLine)
        {
            table.header = CsvParser::parseLine(line);
            firstLine = false;
        }
        else
        {
            table.rows.push_back(CsvParser::parseLine(line));
        }
    }

    if (file.bad())
    {
        throw FileException("Error while reading file:", path);
    }

    return table;
}


// =========================================================
// WRITE
// =========================================================

void FileHandler::writeCsv(const std::string &fileName,
                           const std::vector<std::string> &header,
                           const std::vector<std::vector<std::string>> &rows) const
{
    const fs::path finalPath = toPath(fullPath(fileName));
    fs::path tempPath = finalPath;
    tempPath += ".tmp";

    {
        std::ofstream file(tempPath, std::ios::trunc);

        if (!file.is_open())
        {
            throw FileException("Could not open file for writing:", tempPath.u8string());
        }

        file << CsvParser::formatLine(header) << '\n';
        for (const auto &row : rows)
        {
            file << CsvParser::formatLine(row) << '\n';
        }

        file.flush();
        if (!file)
        {
            throw FileException("Error while writing file:", tempPath.u8string());
        }
    } // file is closed here (destructor = RAII)

    std::error_code error;
    fs::rename(tempPath, finalPath, error);

    if (error)
    {
        throw FileException("Could not replace file (" + error.message() + "):",
                            finalPath.u8string());
    }
}

void FileHandler::createIfMissing(const std::string &fileName,
                                  const std::vector<std::string> &header) const
{
    std::error_code error;
    fs::create_directories(toPath(m_directory), error);

    if (!exists(fileName))
    {
        writeCsv(fileName, header, {});
    }
}
