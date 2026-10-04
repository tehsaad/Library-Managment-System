#ifndef CSVSERIALIZABLE_H
#define CSVSERIALIZABLE_H

#include <string>
#include <vector>

// =========================================================
// CSV SERIALIZABLE (interface)
//
// An abstract class with only pure virtual functions acts
// like an "interface": every class that can be written to a
// CSV file promises to implement toCsvRow().
//
// By convention each class also has two static functions:
//     static std::vector<std::string> csvHeader();
//     static T fromCsvRow(const std::vector<std::string> &row);
// (static functions cannot be virtual, so the Library uses a
// template to call them - see Library::loadTable).
// =========================================================

class CsvSerializable
{
public:
    virtual ~CsvSerializable() = default;

    virtual std::vector<std::string> toCsvRow() const = 0;
};

#endif // CSVSERIALIZABLE_H
