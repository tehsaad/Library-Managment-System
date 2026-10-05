#ifndef HISTORYENTRY_H
#define HISTORYENTRY_H

#include "CsvSerializable.h"
#include "Enums.h"

#include <string>

// =========================================================
// HISTORY ENTRY
//
// One line of the activity log.
// History.csv:  Timestamp,User,Action,Details
// =========================================================

class HistoryEntry : public CsvSerializable
{
public:
    HistoryEntry(const std::string &timestamp,
                 const std::string &username,
                 ActionType action,
                 const std::string &details);

    static std::vector<std::string> csvHeader();
    static HistoryEntry fromCsvRow(const std::vector<std::string> &row);
    std::vector<std::string> toCsvRow() const override;

    const std::string &getTimestamp() const;
    const std::string &getUsername() const;
    ActionType getAction() const;
    const std::string &getDetails() const;

private:
    std::string m_timestamp;
    std::string m_username;
    ActionType m_action;
    std::string m_details;
};

#endif // HISTORYENTRY_H
