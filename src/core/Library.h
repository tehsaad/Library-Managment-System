#ifndef LIBRARY_H
#define LIBRARY_H

#include "model/Book.h"
#include "model/HistoryEntry.h"
#include "model/Loan.h"
#include "model/Person.h"
#include "model/Student.h"
#include "model/VolunteerApplication.h"
#include "storage/Exceptions.h"
#include "storage/FileHandler.h"

#include <memory>
#include <string>
#include <vector>

// =========================================================
// LIBRARY
//
// The "brain" of the program. It owns all the data, applies
// the library rules and saves every change through the
// FileHandler. The GUI never edits data directly - it calls
// a Library function and shows the result (or the error).
//
// Rule violations throw LibraryException with a message that
// can be shown to the user as-is.
// =========================================================

// Numbers for the overview cards
struct LibraryStatistics
{
    int totalBooks = 0;
    int availableBooks = 0;
    int issuedBooks = 0;
    int activeLoans = 0;
    int overdueLoans = 0;
    int totalStudents = 0;
    int pendingFees = 0;
    int pendingApplications = 0;
};

class Library
{
public:
    explicit Library(const std::string &dataDirectory);

    // Library owns unique_ptrs, so copying makes no sense
    Library(const Library &) = delete;
    Library &operator=(const Library &) = delete;

    // ---- files ----
    void load();
    const std::vector<std::string> &loadWarnings() const;
    const std::string &dataDirectory() const;

    // ---- login ----
    Person *login(const std::string &username, const std::string &password, Role role);
    void logout(const Person &user);
    void changePassword(Person &user, const std::string &oldPassword, const std::string &newPassword);

    // ---- books ----
    const std::vector<Book> &books() const;
    const Book *findBook(int id) const;
    std::vector<const Book *> searchBooks(const std::string &query,
                                          const std::string &genre,
                                          bool availableOnly) const;
    std::vector<std::string> genres() const;

    int addBook(Book book, const Person &by);          // returns new ID
    void updateBook(const Book &book, const Person &by);
    void removeBook(int id, const Person &by);

    // ---- members (students) ----
    std::vector<const Student *> students() const;
    const Student *findStudent(const std::string &id) const;
    std::vector<const Student *> searchStudents(const std::string &query) const;

    std::string addStudent(const std::string &name,
                           const std::string &username,
                           const std::string &password,
                           FeeStatus feeStatus,
                           const Person &by);             // returns new ID
    void updateStudent(const std::string &id,
                       const std::string &name,
                       const std::string &username,
                       const std::string &newPassword,    // "" = keep old
                       FeeStatus feeStatus,
                       int warnings,
                       const Person &by);
    void removeStudent(const std::string &id, const Person &by);

    // ---- loans ----
    const std::vector<Loan> &loans() const;
    std::vector<const Loan *> loansForStudent(const std::string &studentId) const;
    const Loan &issueBook(int bookId, const std::string &studentId, const Person &by);
    int returnBook(const std::string &loanId, const Person &by);   // returns days late

    // ---- volunteers ----
    const std::vector<VolunteerApplication> &applications() const;
    int submitApplication(VolunteerApplication application);
    void reviewApplication(int id, ApplicationStatus decision, const Person &by);

    // ---- history ----
    const std::vector<HistoryEntry> &history() const;

    // ---- display helpers ----
    std::string bookTitle(int bookId) const;
    std::string studentName(const std::string &studentId) const;
    LibraryStatistics statistics() const;

    // ---- file names ----
    static const std::string BOOKS_FILE;
    static const std::string STUDENTS_FILE;
    static const std::string FACULTY_FILE;
    static const std::string LOANS_FILE;
    static const std::string HISTORY_FILE;
    static const std::string VOLUNTEERS_FILE;

private:
    // ---- generic load/save (templates work for any CsvSerializable type) ----
    template <typename T>
    std::vector<T> loadTable(const std::string &fileName);

    template <typename T>
    void saveTable(const std::string &fileName, const std::vector<T> &items) const;

    void saveBooks() const;
    void saveStudents() const;
    void saveFaculty() const;
    void saveLoans() const;
    void saveHistory() const;
    void saveApplications() const;
    void savePerson(const Person &person) const;

    void syncWithLoans();
    void record(const std::string &username, ActionType action, const std::string &details);
    void require(bool allowed, const std::string &whatFor) const;

    Book *findBookMutable(int id);
    Student *findStudentMutable(const std::string &id);
    Loan *findLoanMutable(const std::string &id);
    bool usernameTaken(const std::string &username, const std::string &exceptId) const;

    int nextBookId() const;
    std::string nextStudentId() const;
    std::string nextLoanId() const;

    FileHandler m_files;

    std::vector<Book> m_books;
    std::vector<std::unique_ptr<Person>> m_people;    // Students, Faculty and Admins together
    std::vector<Loan> m_loans;
    std::vector<HistoryEntry> m_history;
    std::vector<VolunteerApplication> m_applications;

    std::vector<std::string> m_loadWarnings;
};

#endif // LIBRARY_H
