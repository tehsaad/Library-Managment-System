#ifndef BOOK_H
#define BOOK_H

#include "CsvSerializable.h"
#include "Enums.h"

#include <string>

// =========================================================
// BOOK
//
// Books.csv:  ID,Title,Author,Genre,Year,ISBN,Status
// (Older files without the Status column still load; the
// status is then worked out from the active loans.)
// =========================================================

class Book : public CsvSerializable
{
public:
    Book();
    Book(int id,
         const std::string &title,
         const std::string &author,
         const std::string &genre,
         int year,
         const std::string &isbn,
         BookStatus status = BookStatus::Available);

    // ---- CSV ----
    static std::vector<std::string> csvHeader();
    static Book fromCsvRow(const std::vector<std::string> &row);
    std::vector<std::string> toCsvRow() const override;

    // ---- getters ----
    int getId() const;
    const std::string &getTitle() const;
    const std::string &getAuthor() const;
    const std::string &getGenre() const;
    int getYear() const;
    const std::string &getIsbn() const;
    BookStatus getStatus() const;
    bool isAvailable() const;

    // ---- setters ----
    void setId(int id);
    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setGenre(const std::string &genre);
    void setYear(int year);
    void setIsbn(const std::string &isbn);

    void markIssued();
    void markReturned();

    // Case-insensitive search in title, author, genre and ISBN
    bool matches(const std::string &query) const;

    // Throws std::invalid_argument when a field is not acceptable
    void validate() const;

private:
    int m_id;
    std::string m_title;
    std::string m_author;
    std::string m_genre;
    int m_year;
    std::string m_isbn;
    BookStatus m_status;
};

#endif // BOOK_H
