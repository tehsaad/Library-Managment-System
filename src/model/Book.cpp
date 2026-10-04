#include "Book.h"
#include "storage/CsvParser.h"

#include <stdexcept>


Book::Book()
    : m_id(0), m_year(0), m_status(BookStatus::Available)
{
}

Book::Book(int id,
           const std::string &title,
           const std::string &author,
           const std::string &genre,
           int year,
           const std::string &isbn,
           BookStatus status)
    : m_id(id)
    , m_title(title)
    , m_author(author)
    , m_genre(genre)
    , m_year(year)
    , m_isbn(isbn)
    , m_status(status)
{
}


// =========================================================
// CSV
// =========================================================

std::vector<std::string> Book::csvHeader()
{
    return { "ID", "Title", "Author", "Genre", "Year", "ISBN", "Status" };
}

Book Book::fromCsvRow(const std::vector<std::string> &row)
{
    CsvParser::requireColumns(row, 6, "book");

    // Status column is optional (old files only have 6 columns)
    BookStatus status = BookStatus::Available;
    if (row.size() > 6 && !row[6].empty())
    {
        status = EnumText::bookStatusFromString(row[6]);
    }

    return Book(CsvParser::toInt(row[0], "ID"),
                row[1],
                row[2],
                row[3],
                CsvParser::toInt(row[4], "Year"),
                row[5],
                status);
}

std::vector<std::string> Book::toCsvRow() const
{
    return { std::to_string(m_id),
             m_title,
             m_author,
             m_genre,
             std::to_string(m_year),
             m_isbn,
             EnumText::toString(m_status) };
}


// =========================================================
// GETTERS
// =========================================================

int Book::getId() const { return m_id; }
const std::string &Book::getTitle() const { return m_title; }
const std::string &Book::getAuthor() const { return m_author; }
const std::string &Book::getGenre() const { return m_genre; }
int Book::getYear() const { return m_year; }
const std::string &Book::getIsbn() const { return m_isbn; }
BookStatus Book::getStatus() const { return m_status; }
bool Book::isAvailable() const { return m_status == BookStatus::Available; }


// =========================================================
// SETTERS
// =========================================================

void Book::setId(int id) { m_id = id; }
void Book::setTitle(const std::string &title) { m_title = title; }
void Book::setAuthor(const std::string &author) { m_author = author; }
void Book::setGenre(const std::string &genre) { m_genre = genre; }
void Book::setYear(int year) { m_year = year; }
void Book::setIsbn(const std::string &isbn) { m_isbn = isbn; }

void Book::markIssued() { m_status = BookStatus::Issued; }
void Book::markReturned() { m_status = BookStatus::Available; }


// =========================================================
// SEARCH & VALIDATION
// =========================================================

bool Book::matches(const std::string &query) const
{
    if (query.empty())
    {
        return true;
    }

    return CsvParser::containsIgnoreCase(m_title, query) ||
           CsvParser::containsIgnoreCase(m_author, query) ||
           CsvParser::containsIgnoreCase(m_genre, query) ||
           CsvParser::containsIgnoreCase(m_isbn, query);
}

void Book::validate() const
{
    if (m_title.empty())
    {
        throw std::invalid_argument("Title is required.");
    }
    if (m_author.empty())
    {
        throw std::invalid_argument("Author is required.");
    }
    if (m_year < 1000 || m_year > 2100)
    {
        throw std::invalid_argument("Year must be between 1000 and 2100.");
    }
}
