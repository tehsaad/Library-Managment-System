#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include <vector>

// =========================================================
// CSV PARSER
//
// Turns one line of text into a list of fields and back.
// Follows the usual CSV rules:
//   - fields are separated by commas
//   - a field containing a comma or quote is wrapped in "..."
//   - a quote inside a quoted field is written twice ("")
//
//   Hello,"Smith, John","He said ""hi"""
//   -> [Hello] [Smith, John] [He said "hi"]
//
// Every function is static: the parser has no data of its
// own, it is a toolbox.
// =========================================================

class CsvParser
{
public:
    static std::vector<std::string> parseLine(const std::string &line, char delimiter = ',');
    static std::string formatLine(const std::vector<std::string> &fields, char delimiter = ',');

    // ---- helpers used by the model classes ----
    static std::string trim(const std::string &text);
    static int toInt(const std::string &text, const std::string &fieldName);
    static void requireColumns(const std::vector<std::string> &row,
                               std::size_t count,
                               const std::string &recordName);
    static bool containsIgnoreCase(const std::string &text, const std::string &query);

private:
    static std::string escapeField(const std::string &field, char delimiter);
};

#endif // CSVPARSER_H
