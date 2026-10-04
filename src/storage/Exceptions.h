#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

// =========================================================
// CUSTOM EXCEPTIONS
//
// Both inherit from std::runtime_error, so a GUI can catch
// them separately (to show a nice message) or together with
// catch (const std::exception &e).
// =========================================================

// Something went wrong reading or writing a file
class FileException : public std::runtime_error
{
public:
    FileException(const std::string &message, const std::string &path)
        : std::runtime_error(message + "\n" + path)
        , m_path(path)
    {
    }

    const std::string &path() const { return m_path; }

private:
    std::string m_path;
};

// A library rule was broken (book already issued, no permission, ...)
class LibraryException : public std::runtime_error
{
public:
    explicit LibraryException(const std::string &message)
        : std::runtime_error(message)
    {
    }
};

#endif // EXCEPTIONS_H
