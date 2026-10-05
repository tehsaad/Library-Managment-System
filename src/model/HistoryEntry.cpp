#include "HistoryEntry.h"
#include "storage/CsvParser.h"


HistoryEntry::HistoryEntry(const std::string &timestamp,
                           const std::string &username,
                           ActionType action,
                           const std::string &details)
    : m_timestamp(timestamp)
    , m_username(username)
    , m_action(action)
    , m_details(details)
{
}

std::vector<std::string> HistoryEntry::csvHeader()
{
    return { "Timestamp", "User", "Action", "Details" };
}

HistoryEntry HistoryEntry::fromCsvRow(const std::vector<std::string> &row)
{
    CsvParser::requireColumns(row, 4, "history");

    return HistoryEntry(row[0], row[1], EnumText::actionFromString(row[2]), row[3]);
}

std::vector<std::string> HistoryEntry::toCsvRow() const
{
    return { m_timestamp, m_username, EnumText::toString(m_action), m_details };
}

const std::string &HistoryEntry::getTimestamp() const { return m_timestamp; }
const std::string &HistoryEntry::getUsername() const { return m_username; }
ActionType HistoryEntry::getAction() const { return m_action; }
const std::string &HistoryEntry::getDetails() const { return m_details; }
