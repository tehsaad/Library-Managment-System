#include "CsvParser.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>


// =========================================================
// PARSE ONE LINE
// =========================================================

std::vector<std::string> CsvParser::parseLine(const std::string &line, char delimiter)
{
    std::vector<std::string> fields;
    std::string current;
    bool inQuotes = false;
    bool wasQuoted = false;

    for (std::size_t i = 0; i < line.size(); i++)
    {
        const char c = line[i];

        if (inQuotes)
        {
            if (c == '"')
            {
                // "" inside quotes means one real quote character
                if (i + 1 < line.size() && line[i + 1] == '"')
                {
                    current += '"';
                    i++;
                }
                else
                {
                    inQuotes = false;
                }
            }
            else
            {
                current += c;
            }
        }
        else if (c == '"')
        {
            inQuotes = true;
            wasQuoted = true;
        }
        else if (c == delimiter)
        {
            // Quoted fields keep their spaces exactly
            fields.push_back(wasQuoted ? current : trim(current));
            current.clear();
            wasQuoted = false;
        }
        else if (c != '\r' && c != '\n')
        {
            current += c;
        }
    }

    fields.push_back(wasQuoted ? current : trim(current));
    return fields;
}


// =========================================================
// FORMAT ONE LINE
// =========================================================

std::string CsvParser::formatLine(const std::vector<std::string> &fields, char delimiter)
{
    std::string line;

    for (std::size_t i = 0; i < fields.size(); i++)
    {
        if (i > 0)
        {
            line += delimiter;
        }
        line += escapeField(fields[i], delimiter);
    }

    return line;
}

std::string CsvParser::escapeField(const std::string &field, char delimiter)
{
    const bool needsQuotes =
        field.find(delimiter) != std::string::npos ||
        field.find('"') != std::string::npos ||
        field.find('\n') != std::string::npos ||
        (!field.empty() && (std::isspace(static_cast<unsigned char>(field.front())) ||
                            std::isspace(static_cast<unsigned char>(field.back()))));

    if (!needsQuotes)
    {
        return field;
    }

    std::string escaped = "\"";
    for (char c : field)
    {
        if (c == '"')
        {
            escaped += "\"\"";
        }
        else if (c == '\n' || c == '\r')
        {
            escaped += ' ';   // one record = one line, keep it simple
        }
        else
        {
            escaped += c;
        }
    }
    escaped += '"';
    return escaped;
}


// =========================================================
// HELPERS
// =========================================================

std::string CsvParser::trim(const std::string &text)
{
    std::size_t start = 0;
    std::size_t end = text.size();

    while (start < end && std::isspace(static_cast<unsigned char>(text[start])))
    {
        start++;
    }
    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])))
    {
        end--;
    }

    return text.substr(start, end - start);
}

int CsvParser::toInt(const std::string &text, const std::string &fieldName)
{
    try
    {
        std::size_t used = 0;
        const int value = std::stoi(text, &used);

        if (used != text.size())
        {
            throw std::invalid_argument("extra characters");
        }
        return value;
    }
    catch (const std::exception &)
    {
        throw std::invalid_argument(fieldName + " must be a whole number (got \"" + text + "\")");
    }
}

void CsvParser::requireColumns(const std::vector<std::string> &row,
                               std::size_t count,
                               const std::string &recordName)
{
    if (row.size() < count)
    {
        throw std::invalid_argument("A " + recordName + " row needs " + std::to_string(count) +
                                    " columns but has " + std::to_string(row.size()));
    }
}

bool CsvParser::containsIgnoreCase(const std::string &text, const std::string &query)
{
    auto equalIgnoreCase = [](char a, char b) {
        return std::tolower(static_cast<unsigned char>(a)) ==
               std::tolower(static_cast<unsigned char>(b));
    };

    return std::search(text.begin(), text.end(),
                       query.begin(), query.end(),
                       equalIgnoreCase) != text.end();
}
