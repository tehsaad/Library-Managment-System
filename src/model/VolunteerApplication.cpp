#include "VolunteerApplication.h"
#include "storage/CsvParser.h"

#include <stdexcept>


VolunteerApplication::VolunteerApplication(int id,
                                           const std::string &name,
                                           const std::string &email,
                                           const std::string &phone,
                                           const std::string &availability,
                                           const std::string &reason,
                                           ApplicationStatus status,
                                           const Date &appliedOn)
    : m_id(id)
    , m_name(name)
    , m_email(email)
    , m_phone(phone)
    , m_availability(availability)
    , m_reason(reason)
    , m_status(status)
    , m_appliedOn(appliedOn)
{
}

std::vector<std::string> VolunteerApplication::csvHeader()
{
    return { "ID", "Name", "Email", "Phone", "Availability", "Reason", "Status", "AppliedOn" };
}

VolunteerApplication VolunteerApplication::fromCsvRow(const std::vector<std::string> &row)
{
    CsvParser::requireColumns(row, 8, "volunteer");

    return VolunteerApplication(CsvParser::toInt(row[0], "ID"),
                                row[1],
                                row[2],
                                row[3],
                                row[4],
                                row[5],
                                EnumText::applicationStatusFromString(row[6]),
                                Date::fromString(row[7]));
}

std::vector<std::string> VolunteerApplication::toCsvRow() const
{
    return { std::to_string(m_id),
             m_name,
             m_email,
             m_phone,
             m_availability,
             m_reason,
             EnumText::toString(m_status),
             m_appliedOn.toString() };
}

int VolunteerApplication::getId() const { return m_id; }
const std::string &VolunteerApplication::getName() const { return m_name; }
const std::string &VolunteerApplication::getEmail() const { return m_email; }
const std::string &VolunteerApplication::getPhone() const { return m_phone; }
const std::string &VolunteerApplication::getAvailability() const { return m_availability; }
const std::string &VolunteerApplication::getReason() const { return m_reason; }
ApplicationStatus VolunteerApplication::getStatus() const { return m_status; }
const Date &VolunteerApplication::getAppliedOn() const { return m_appliedOn; }

void VolunteerApplication::setId(int id) { m_id = id; }
void VolunteerApplication::setStatus(ApplicationStatus status) { m_status = status; }

void VolunteerApplication::validate() const
{
    if (m_name.empty())
    {
        throw std::invalid_argument("Please enter your name.");
    }

    const std::size_t at = m_email.find('@');
    if (at == std::string::npos || at == 0 || m_email.find('.', at) == std::string::npos)
    {
        throw std::invalid_argument("Please enter a valid email address.");
    }
}
