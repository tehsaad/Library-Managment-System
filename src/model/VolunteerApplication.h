#ifndef VOLUNTEERAPPLICATION_H
#define VOLUNTEERAPPLICATION_H

#include "CsvSerializable.h"
#include "Date.h"
#include "Enums.h"

#include <string>

// =========================================================
// VOLUNTEER APPLICATION
//
// Anyone can apply from the welcome screen; an Admin then
// approves or rejects it.
// Volunteers.csv:  ID,Name,Email,Phone,Availability,Reason,Status,AppliedOn
// =========================================================

class VolunteerApplication : public CsvSerializable
{
public:
    VolunteerApplication(int id,
                         const std::string &name,
                         const std::string &email,
                         const std::string &phone,
                         const std::string &availability,
                         const std::string &reason,
                         ApplicationStatus status = ApplicationStatus::Pending,
                         const Date &appliedOn = Date::today());

    static std::vector<std::string> csvHeader();
    static VolunteerApplication fromCsvRow(const std::vector<std::string> &row);
    std::vector<std::string> toCsvRow() const override;

    int getId() const;
    const std::string &getName() const;
    const std::string &getEmail() const;
    const std::string &getPhone() const;
    const std::string &getAvailability() const;
    const std::string &getReason() const;
    ApplicationStatus getStatus() const;
    const Date &getAppliedOn() const;

    void setId(int id);
    void setStatus(ApplicationStatus status);

    void validate() const;   // throws std::invalid_argument

private:
    int m_id;
    std::string m_name;
    std::string m_email;
    std::string m_phone;
    std::string m_availability;
    std::string m_reason;
    ApplicationStatus m_status;
    Date m_appliedOn;
};

#endif // VOLUNTEERAPPLICATION_H
