#include "Library.h"
#include "model/Faculty.h"
#include "storage/CsvParser.h"

#include <algorithm>
#include <cstdio>
#include <set>


// =========================================================
// FILE NAMES
// =========================================================

const std::string Library::BOOKS_FILE = "Books.csv";
const std::string Library::STUDENTS_FILE = "Users.csv";
const std::string Library::FACULTY_FILE = "Faculty.csv";
const std::string Library::LOANS_FILE = "Loans.csv";
const std::string Library::HISTORY_FILE = "History.csv";
const std::string Library::VOLUNTEERS_FILE = "Volunteers.csv";


Library::Library(const std::string &dataDirectory)
    : m_files(dataDirectory)
{
}


// =========================================================
// GENERIC LOAD / SAVE
//
// One template instead of six almost identical functions.
// T must have:  static csvHeader(), static fromCsvRow(row)
// and toCsvRow() - i.e. follow the CsvSerializable rules.
// =========================================================

template <typename T>
std::vector<T> Library::loadTable(const std::string &fileName)
{
    m_files.createIfMissing(fileName, T::csvHeader());

    const CsvTable table = m_files.readCsv(fileName);
    std::vector<T> items;

    for (std::size_t i = 0; i < table.rows.size(); i++)
    {
        try
        {
            items.push_back(T::fromCsvRow(table.rows[i]));
        }
        catch (const std::exception &e)
        {
            // One bad row should not stop the whole program
            m_loadWarnings.push_back(fileName + ", row " + std::to_string(i + 1) + ": " + e.what());
        }
    }

    return items;
}

template <typename T>
void Library::saveTable(const std::string &fileName, const std::vector<T> &items) const
{
    std::vector<std::vector<std::string>> rows;
    rows.reserve(items.size());

    for (const T &item : items)
    {
        rows.push_back(item.toCsvRow());
    }

    m_files.writeCsv(fileName, T::csvHeader(), rows);
}


// =========================================================
// LOAD EVERYTHING
// =========================================================

void Library::load()
{
    m_loadWarnings.clear();
    m_people.clear();

    m_books = loadTable<Book>(BOOKS_FILE);
    m_loans = loadTable<Loan>(LOANS_FILE);
    m_history = loadTable<HistoryEntry>(HISTORY_FILE);
    m_applications = loadTable<VolunteerApplication>(VOLUNTEERS_FILE);

    // Students: every row becomes a Student object
    for (const Student &student : loadTable<Student>(STUDENTS_FILE))
    {
        m_people.push_back(std::make_unique<Student>(student));
    }

    // Faculty.csv: the factory decides between Faculty and Admin
    m_files.createIfMissing(FACULTY_FILE, Faculty::csvHeader());
    const CsvTable staff = m_files.readCsv(FACULTY_FILE);

    for (std::size_t i = 0; i < staff.rows.size(); i++)
    {
        try
        {
            m_people.push_back(Faculty::fromCsvRow(staff.rows[i]));
        }
        catch (const std::exception &e)
        {
            m_loadWarnings.push_back(FACULTY_FILE + ", row " + std::to_string(i + 1) + ": " + e.what());
        }
    }

    syncWithLoans();
}

const std::vector<std::string> &Library::loadWarnings() const
{
    return m_loadWarnings;
}

const std::string &Library::dataDirectory() const
{
    return m_files.directory();
}

// The Loans file is the "source of truth": a book is Issued only
// if an active loan exists, and a student's Books_Borrowed is the
// number of their active loans.
void Library::syncWithLoans()
{
    for (Book &book : m_books)
    {
        book.markReturned();
    }

    for (const auto &person : m_people)
    {
        if (auto *student = dynamic_cast<Student *>(person.get()))
        {
            student->setBooksBorrowed(0);
        }
    }

    for (const Loan &loan : m_loans)
    {
        if (!loan.isActive())
        {
            continue;
        }

        if (Book *book = findBookMutable(loan.getBookId()))
        {
            book->markIssued();
        }
        if (Student *student = findStudentMutable(loan.getStudentId()))
        {
            student->borrowOne();
        }
    }
}


// =========================================================
// SAVE
// =========================================================

void Library::saveBooks() const { saveTable(BOOKS_FILE, m_books); }
void Library::saveLoans() const { saveTable(LOANS_FILE, m_loans); }
void Library::saveHistory() const { saveTable(HISTORY_FILE, m_history); }
void Library::saveApplications() const { saveTable(VOLUNTEERS_FILE, m_applications); }

void Library::saveStudents() const
{
    std::vector<std::vector<std::string>> rows;

    for (const Student *student : students())
    {
        rows.push_back(student->toCsvRow());
    }
    m_files.writeCsv(STUDENTS_FILE, Student::csvHeader(), rows);
}

void Library::saveFaculty() const
{
    std::vector<std::vector<std::string>> rows;

    for (const auto &person : m_people)
    {
        if (person->getRole() != Role::Student)
        {
            // toCsvRow() is virtual: Faculty and Admin both write themselves
            rows.push_back(person->toCsvRow());
        }
    }
    m_files.writeCsv(FACULTY_FILE, Faculty::csvHeader(), rows);
}

void Library::savePerson(const Person &person) const
{
    if (person.getRole() == Role::Student)
    {
        saveStudents();
    }
    else
    {
        saveFaculty();
    }
}


// =========================================================
// HISTORY & PERMISSIONS
// =========================================================

void Library::record(const std::string &username, ActionType action, const std::string &details)
{
    m_history.emplace_back(Date::currentTimestamp(), username, action, details);
    saveHistory();
}

void Library::require(bool allowed, const std::string &whatFor) const
{
    if (!allowed)
    {
        throw LibraryException("You do not have permission to " + whatFor + ".");
    }
}

const std::vector<HistoryEntry> &Library::history() const
{
    return m_history;
}


// =========================================================
// LOGIN
// =========================================================

Person *Library::login(const std::string &username, const std::string &password, Role role)
{
    for (const auto &person : m_people)
    {
        if (person->getUsername() == username &&
            person->getRole() == role &&
            person->checkPassword(password))
        {
            record(username, ActionType::Login, person->roleName() + " signed in");
            return person.get();
        }
    }

    return nullptr;
}

void Library::logout(const Person &user)
{
    record(user.getUsername(), ActionType::Logout, user.roleName() + " signed out");
}

void Library::changePassword(Person &user, const std::string &oldPassword, const std::string &newPassword)
{
    if (!user.checkPassword(oldPassword))
    {
        throw LibraryException("Your current password is not correct.");
    }

    try
    {
        user.setPassword(newPassword);
    }
    catch (const std::invalid_argument &e)
    {
        throw LibraryException(e.what());
    }

    savePerson(user);
    record(user.getUsername(), ActionType::ChangePassword, "Password changed");
}


// =========================================================
// BOOKS
// =========================================================

const std::vector<Book> &Library::books() const
{
    return m_books;
}

const Book *Library::findBook(int id) const
{
    for (const Book &book : m_books)
    {
        if (book.getId() == id)
        {
            return &book;
        }
    }
    return nullptr;
}

Book *Library::findBookMutable(int id)
{
    // Reuse the const version instead of writing the loop twice
    return const_cast<Book *>(static_cast<const Library *>(this)->findBook(id));
}

std::vector<const Book *> Library::searchBooks(const std::string &query,
                                               const std::string &genre,
                                               bool availableOnly) const
{
    std::vector<const Book *> results;

    for (const Book &book : m_books)
    {
        if (!genre.empty() && book.getGenre() != genre)
        {
            continue;
        }
        if (availableOnly && !book.isAvailable())
        {
            continue;
        }
        if (book.matches(query))
        {
            results.push_back(&book);
        }
    }

    return results;
}

std::vector<std::string> Library::genres() const
{
    std::set<std::string> unique;   // std::set keeps them sorted and unique

    for (const Book &book : m_books)
    {
        if (!book.getGenre().empty())
        {
            unique.insert(book.getGenre());
        }
    }

    return std::vector<std::string>(unique.begin(), unique.end());
}

int Library::nextBookId() const
{
    int highest = 0;
    for (const Book &book : m_books)
    {
        highest = std::max(highest, book.getId());
    }
    return highest + 1;
}

int Library::addBook(Book book, const Person &by)
{
    require(by.canManageBooks(), "add books");

    try
    {
        book.validate();
    }
    catch (const std::invalid_argument &e)
    {
        throw LibraryException(e.what());
    }

    book.setId(nextBookId());
    book.markReturned();
    m_books.push_back(book);
    saveBooks();

    record(by.getUsername(), ActionType::AddBook,
           "Added \"" + book.getTitle() + "\" (#" + std::to_string(book.getId()) + ")");
    return book.getId();
}

void Library::updateBook(const Book &book, const Person &by)
{
    require(by.canManageBooks(), "edit books");

    Book *existing = findBookMutable(book.getId());
    if (existing == nullptr)
    {
        throw LibraryException("That book no longer exists.");
    }

    try
    {
        book.validate();
    }
    catch (const std::invalid_argument &e)
    {
        throw LibraryException(e.what());
    }

    // Only the catalog details change; the status stays as it is
    existing->setTitle(book.getTitle());
    existing->setAuthor(book.getAuthor());
    existing->setGenre(book.getGenre());
    existing->setYear(book.getYear());
    existing->setIsbn(book.getIsbn());
    saveBooks();

    record(by.getUsername(), ActionType::EditBook,
           "Edited \"" + book.getTitle() + "\" (#" + std::to_string(book.getId()) + ")");
}

void Library::removeBook(int id, const Person &by)
{
    require(by.canManageBooks(), "remove books");

    auto it = std::find_if(m_books.begin(), m_books.end(),
                           [id](const Book &book) { return book.getId() == id; });

    if (it == m_books.end())
    {
        throw LibraryException("That book no longer exists.");
    }
    if (!it->isAvailable())
    {
        throw LibraryException("\"" + it->getTitle() + "\" is issued right now. "
                               "It can be removed after it is returned.");
    }

    const std::string title = it->getTitle();
    m_books.erase(it);
    saveBooks();

    record(by.getUsername(), ActionType::RemoveBook,
           "Removed \"" + title + "\" (#" + std::to_string(id) + ")");
}


// =========================================================
// MEMBERS
// =========================================================

std::vector<const Student *> Library::students() const
{
    std::vector<const Student *> result;

    for (const auto &person : m_people)
    {
        // dynamic_cast returns nullptr when the Person is not a Student
        if (const auto *student = dynamic_cast<const Student *>(person.get()))
        {
            result.push_back(student);
        }
    }
    return result;
}

const Student *Library::findStudent(const std::string &id) const
{
    for (const Student *student : students())
    {
        if (student->getId() == id)
        {
            return student;
        }
    }
    return nullptr;
}

Student *Library::findStudentMutable(const std::string &id)
{
    return const_cast<Student *>(static_cast<const Library *>(this)->findStudent(id));
}

std::vector<const Student *> Library::searchStudents(const std::string &query) const
{
    std::vector<const Student *> result;

    for (const Student *student : students())
    {
        if (query.empty() ||
            CsvParser::containsIgnoreCase(student->getId(), query) ||
            CsvParser::containsIgnoreCase(student->getUsername(), query) ||
            CsvParser::containsIgnoreCase(student->getName(), query))
        {
            result.push_back(student);
        }
    }
    return result;
}

bool Library::usernameTaken(const std::string &username, const std::string &exceptId) const
{
    for (const auto &person : m_people)
    {
        if (person->getUsername() == username && person->getId() != exceptId)
        {
            return true;
        }
    }
    return false;
}

std::string Library::nextStudentId() const
{
    int highest = 0;

    for (const Student *student : students())
    {
        const std::string &id = student->getId();
        if (id.size() > 3 && id.compare(0, 3, "STU") == 0)
        {
            try
            {
                highest = std::max(highest, std::stoi(id.substr(3)));
            }
            catch (const std::exception &)
            {
                // ignore IDs that do not follow the pattern
            }
        }
    }

    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "STU%03d", highest + 1);
    return buffer;
}

std::string Library::addStudent(const std::string &name,
                                const std::string &username,
                                const std::string &password,
                                FeeStatus feeStatus,
                                const Person &by)
{
    require(by.canManageMembers(), "add members");

    if (usernameTaken(username, ""))
    {
        throw LibraryException("The username \"" + username + "\" is already taken.");
    }

    auto student = std::make_unique<Student>(nextStudentId(), username, name, "", 0, 0, feeStatus);

    try
    {
        student->setName(name);
        student->setUsername(username);
        student->setPassword(password);
    }
    catch (const std::invalid_argument &e)
    {
        throw LibraryException(e.what());
    }

    const std::string id = student->getId();
    m_people.push_back(std::move(student));
    saveStudents();

    record(by.getUsername(), ActionType::AddMember, "Added student " + name + " (" + id + ")");
    return id;
}

void Library::updateStudent(const std::string &id,
                            const std::string &name,
                            const std::string &username,
                            const std::string &newPassword,
                            FeeStatus feeStatus,
                            int warnings,
                            const Person &by)
{
    require(by.canManageMembers(), "edit members");

    Student *student = findStudentMutable(id);
    if (student == nullptr)
    {
        throw LibraryException("That student no longer exists.");
    }
    if (usernameTaken(username, id))
    {
        throw LibraryException("The username \"" + username + "\" is already taken.");
    }

    // Work on a copy first, so a bad value leaves the real student unchanged
    Student updated = *student;
    try
    {
        updated.setName(name);
        updated.setUsername(username);
        updated.setWarnings(warnings);
        updated.setFeeStatus(feeStatus);
        if (!newPassword.empty())
        {
            updated.setPassword(newPassword);
        }
    }
    catch (const std::invalid_argument &e)
    {
        throw LibraryException(e.what());
    }

    *student = updated;
    saveStudents();

    record(by.getUsername(), ActionType::EditMember, "Updated student " + name + " (" + id + ")");
}

void Library::removeStudent(const std::string &id, const Person &by)
{
    require(by.canManageMembers(), "remove members");

    const Student *student = findStudent(id);
    if (student == nullptr)
    {
        throw LibraryException("That student no longer exists.");
    }
    if (student->getBooksBorrowed() > 0)
    {
        throw LibraryException(student->getName() + " still has " +
                               std::to_string(student->getBooksBorrowed()) +
                               " book(s). They must be returned first.");
    }

    const std::string name = student->getName();

    m_people.erase(std::remove_if(m_people.begin(), m_people.end(),
                                  [&id](const std::unique_ptr<Person> &person) {
                                      return person->getRole() == Role::Student &&
                                             person->getId() == id;
                                  }),
                   m_people.end());
    saveStudents();

    record(by.getUsername(), ActionType::RemoveMember, "Removed student " + name + " (" + id + ")");
}


// =========================================================
// LOANS
// =========================================================

const std::vector<Loan> &Library::loans() const
{
    return m_loans;
}

std::vector<const Loan *> Library::loansForStudent(const std::string &studentId) const
{
    std::vector<const Loan *> result;

    for (const Loan &loan : m_loans)
    {
        if (loan.getStudentId() == studentId)
        {
            result.push_back(&loan);
        }
    }
    return result;
}

Loan *Library::findLoanMutable(const std::string &id)
{
    for (Loan &loan : m_loans)
    {
        if (loan.getId() == id)
        {
            return &loan;
        }
    }
    return nullptr;
}

std::string Library::nextLoanId() const
{
    int highest = 0;

    for (const Loan &loan : m_loans)
    {
        const std::string &id = loan.getId();
        if (id.size() > 1 && id[0] == 'L')
        {
            try
            {
                highest = std::max(highest, std::stoi(id.substr(1)));
            }
            catch (const std::exception &)
            {
            }
        }
    }

    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "L%04d", highest + 1);
    return buffer;
}

const Loan &Library::issueBook(int bookId, const std::string &studentId, const Person &by)
{
    // Staff can issue to anyone; a student can only borrow for themselves
    const bool borrowingForSelf = by.getRole() == Role::Student && by.getId() == studentId;
    require(by.canIssueBooks() || borrowingForSelf, "issue books to other members");

    Book *book = findBookMutable(bookId);
    if (book == nullptr)
    {
        throw LibraryException("That book no longer exists.");
    }
    if (!book->isAvailable())
    {
        throw LibraryException("\"" + book->getTitle() + "\" is already issued.");
    }

    Student *student = findStudentMutable(studentId);
    if (student == nullptr)
    {
        throw LibraryException("That student no longer exists.");
    }

    std::string reason;
    if (!student->canBorrow(reason))
    {
        throw LibraryException(reason);
    }

    const Date today = Date::today();
    m_loans.emplace_back(nextLoanId(), bookId, studentId, today,
                         today.addDays(Loan::LOAN_PERIOD_DAYS));

    book->markIssued();
    student->borrowOne();

    saveLoans();
    saveBooks();
    saveStudents();

    const Loan &loan = m_loans.back();
    record(by.getUsername(), ActionType::IssueBook,
           "\"" + book->getTitle() + "\" to " + student->getName() +
               ", due " + loan.getDueDate().toString());
    return loan;
}

int Library::returnBook(const std::string &loanId, const Person &by)
{
    Loan *loan = findLoanMutable(loanId);
    if (loan == nullptr)
    {
        throw LibraryException("That loan no longer exists.");
    }

    const bool ownLoan = by.getRole() == Role::Student && by.getId() == loan->getStudentId();
    require(by.canIssueBooks() || ownLoan, "return other members' books");

    if (!loan->isActive())
    {
        throw LibraryException("This book has already been returned.");
    }

    const Date today = Date::today();
    const int daysLate = loan->daysOverdue(today);

    loan->markReturned(today);

    if (Book *book = findBookMutable(loan->getBookId()))
    {
        book->markReturned();
    }

    Student *student = findStudentMutable(loan->getStudentId());
    if (student != nullptr)
    {
        student->returnOne();

        // Late return: one warning and a fine to pay
        if (daysLate > 0)
        {
            student->addWarning();
            student->setFeeStatus(FeeStatus::Pending);
        }
    }

    saveLoans();
    saveBooks();
    saveStudents();

    std::string details = "\"" + bookTitle(loan->getBookId()) + "\" from " +
                          studentName(loan->getStudentId());
    if (daysLate > 0)
    {
        details += " (" + std::to_string(daysLate) + " days late)";
    }
    record(by.getUsername(), ActionType::ReturnBook, details);

    return daysLate;
}


// =========================================================
// VOLUNTEERS
// =========================================================

const std::vector<VolunteerApplication> &Library::applications() const
{
    return m_applications;
}

int Library::submitApplication(VolunteerApplication application)
{
    try
    {
        application.validate();
    }
    catch (const std::invalid_argument &e)
    {
        throw LibraryException(e.what());
    }

    int highest = 0;
    for (const VolunteerApplication &existing : m_applications)
    {
        highest = std::max(highest, existing.getId());
    }

    application.setId(highest + 1);
    application.setStatus(ApplicationStatus::Pending);
    m_applications.push_back(application);
    saveApplications();

    record("guest", ActionType::VolunteerApplied, application.getName() + " applied to volunteer");
    return application.getId();
}

void Library::reviewApplication(int id, ApplicationStatus decision, const Person &by)
{
    require(by.canReviewVolunteers(), "review volunteer applications");

    for (VolunteerApplication &application : m_applications)
    {
        if (application.getId() == id)
        {
            application.setStatus(decision);
            saveApplications();

            record(by.getUsername(), ActionType::VolunteerReviewed,
                   application.getName() + ": " + EnumText::toString(decision));
            return;
        }
    }

    throw LibraryException("That application no longer exists.");
}


// =========================================================
// DISPLAY HELPERS
// =========================================================

std::string Library::bookTitle(int bookId) const
{
    const Book *book = findBook(bookId);
    return book ? book->getTitle() : "Book #" + std::to_string(bookId) + " (removed)";
}

std::string Library::studentName(const std::string &studentId) const
{
    const Student *student = findStudent(studentId);
    return student ? student->getName() : studentId + " (removed)";
}

LibraryStatistics Library::statistics() const
{
    LibraryStatistics stats;
    const Date today = Date::today();

    stats.totalBooks = static_cast<int>(m_books.size());
    for (const Book &book : m_books)
    {
        if (book.isAvailable())
        {
            stats.availableBooks++;
        }
    }
    stats.issuedBooks = stats.totalBooks - stats.availableBooks;

    for (const Loan &loan : m_loans)
    {
        if (loan.isActive())
        {
            stats.activeLoans++;
        }
        if (loan.isOverdue(today))
        {
            stats.overdueLoans++;
        }
    }

    for (const Student *student : students())
    {
        stats.totalStudents++;
        if (student->getFeeStatus() == FeeStatus::Pending)
        {
            stats.pendingFees++;
        }
    }

    for (const VolunteerApplication &application : m_applications)
    {
        if (application.getStatus() == ApplicationStatus::Pending)
        {
            stats.pendingApplications++;
        }
    }

    return stats;
}
