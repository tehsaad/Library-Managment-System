// =========================================================
// CORE TESTS
//
// Checks the non-GUI classes (CSV parsing, dates, library
// rules) without needing Qt. Build and run from the project
// folder with:
//
//   g++ -std=c++17 -Isrc tests/core_tests.cpp src/model/*.cpp src/storage/*.cpp src/core/*.cpp -o core_tests
//   ./core_tests
// =========================================================

#include "core/Library.h"
#include "model/Admin.h"
#include "model/Date.h"
#include "storage/CsvParser.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

static int failures = 0;
static int checks = 0;

#define CHECK(condition)                                                     \
    do {                                                                     \
        checks++;                                                            \
        if (!(condition)) {                                                  \
            failures++;                                                      \
            std::cerr << "FAILED line " << __LINE__ << ": " #condition "\n"; \
        }                                                                    \
    } while (false)

template <typename Function>
bool throwsLibraryException(Function function)
{
    try
    {
        function();
    }
    catch (const LibraryException &)
    {
        return true;
    }
    return false;
}

static void writeFile(const fs::path &path, const std::string &text)
{
    std::ofstream(path) << text;
}

// ---------------------------------------------------------

static void testCsvParser()
{
    auto fields = CsvParser::parseLine("1, Hello ,\"Smith, John\",\"He said \"\"hi\"\"\",");
    CHECK(fields.size() == 5);
    CHECK(fields[0] == "1");
    CHECK(fields[1] == "Hello");
    CHECK(fields[2] == "Smith, John");
    CHECK(fields[3] == "He said \"hi\"");
    CHECK(fields[4].empty());

    // Round trip: format then parse gives the same fields back
    const std::vector<std::string> original = { "a,b", "quote\"inside", " spaced ", "plain" };
    CHECK(CsvParser::parseLine(CsvParser::formatLine(original)) == original);

    CHECK(CsvParser::toInt("42", "x") == 42);
    bool threw = false;
    try { CsvParser::toInt("4x", "x"); } catch (const std::invalid_argument &) { threw = true; }
    CHECK(threw);
}

static void testDate()
{
    const Date d(2024, 2, 28);
    CHECK(d.addDays(1).toString() == "2024-02-29");   // leap year
    CHECK(d.addDays(2).toString() == "2024-03-01");
    CHECK(Date(2026, 12, 31).addDays(1).toString() == "2027-01-01");
    CHECK(Date(2026, 10, 5) - Date(2026, 9, 24) == 11);
    CHECK(Date(2026, 1, 1) < Date(2026, 1, 2));
    CHECK(Date::fromString("2026-10-05") == Date(2026, 10, 5));
    CHECK(!Date::fromString("").isValid());

    bool threw = false;
    try { Date::fromString("2026-02-30"); } catch (const std::invalid_argument &) { threw = true; }
    CHECK(threw);
}

static void testPolymorphism()
{
    Admin admin("1", "admin", "Admin", "pw1");
    Faculty faculty("2", "t", "Teacher", "pw2");
    Student student("STU1", "s", "Student", "pw3");

    const Person *people[] = { &admin, &faculty, &student };

    CHECK(people[0]->canManageMembers());
    CHECK(people[0]->canManageBooks());       // inherited from Faculty
    CHECK(!people[1]->canManageMembers());
    CHECK(people[1]->canIssueBooks());
    CHECK(!people[2]->canIssueBooks());
    CHECK(admin.toCsvRow()[4] == "Admin");    // virtual roleName()
    CHECK(student.profileDetails().size() == 7);
}

static void testLibrary(const fs::path &dir)
{
    writeFile(dir / "Books.csv",
              "ID,Title,Author,Genre,Year,ISBN\n"           // old 6-column format
              "1,Book One,Author A,Fantasy,2018,111\n"
              "2,\"Book, Two\",Author B,Mystery,2019,222\n"
              "3,Broken,Author C,Mystery,notayear,333\n");  // bad row
    writeFile(dir / "Users.csv",
              "ID,Username,Name,Password,Books_Borrowed,Warnings,Fee_Status\n"
              "STU001,saad,Saad,123,9,0,Paid\n"
              "STU002,late,Late Larry,123,0,0,Pending\n");
    writeFile(dir / "Faculty.csv",
              "ID,Username,Name,Password,Role\n"
              "1,admin,Admin,admin123,Admin\n"
              "2,teacher,Teacher,1234,Faculty\n");

    Library library(dir.u8string());
    library.load();

    CHECK(library.books().size() == 2);
    CHECK(library.loadWarnings().size() == 1);              // the "notayear" row
    CHECK(library.findStudent("STU001")->getBooksBorrowed() == 0);   // recomputed from loans
    CHECK(fs::exists(dir / "Loans.csv"));                   // created when missing

    // ---- login checks role as well as password ----
    CHECK(library.login("admin", "admin123", Role::Faculty) == nullptr);
    Person *admin = library.login("admin", "admin123", Role::Admin);
    Person *teacher = library.login("teacher", "1234", Role::Faculty);
    Person *saad = library.login("saad", "123", Role::Student);
    CHECK(admin != nullptr && teacher != nullptr && saad != nullptr);

    // ---- permissions ----
    CHECK(throwsLibraryException([&] { library.addBook(Book(0, "X", "Y", "Z", 2000, ""), *saad); }));
    CHECK(throwsLibraryException([&] { library.addStudent("N", "u", "pw1", FeeStatus::Paid, *teacher); }));
    CHECK(throwsLibraryException([&] { library.issueBook(1, "STU002", *saad); }));   // not for others

    // ---- issuing ----
    const int newId = library.addBook(Book(0, "New Book", "Someone", "Poetry", 2020, "999"), *teacher);
    CHECK(newId == 3);

    const Loan &loan = library.issueBook(1, "STU001", *saad);       // student borrows for self
    const std::string loanId = loan.getId();
    CHECK(loanId == "L0001");
    CHECK(loan.getDueDate() == Date::today().addDays(Loan::LOAN_PERIOD_DAYS));
    CHECK(!library.findBook(1)->isAvailable());
    CHECK(library.findStudent("STU001")->getBooksBorrowed() == 1);

    CHECK(throwsLibraryException([&] { library.issueBook(1, "STU001", *teacher); }));  // already issued
    CHECK(throwsLibraryException([&] { library.issueBook(2, "STU002", *teacher); }));  // fee pending
    CHECK(throwsLibraryException([&] { library.removeBook(1, *teacher); }));           // issued
    CHECK(throwsLibraryException([&] { library.removeStudent("STU001", *admin); }));   // has a book

    // ---- returning ----
    CHECK(library.returnBook(loanId, *teacher) == 0);
    CHECK(library.findBook(1)->isAvailable());
    CHECK(library.findStudent("STU001")->getBooksBorrowed() == 0);
    CHECK(throwsLibraryException([&] { library.returnBook(loanId, *teacher); }));

    // ---- members ----
    const std::string newStudent = library.addStudent("New Kid", "newkid", "abc", FeeStatus::Paid, *admin);
    CHECK(newStudent == "STU003");
    CHECK(throwsLibraryException([&] { library.addStudent("Dup", "saad", "abc", FeeStatus::Paid, *admin); }));
    CHECK(throwsLibraryException([&] { library.addStudent("Short", "pw", "a", FeeStatus::Paid, *admin); }));
    library.updateStudent("STU002", "Larry", "late", "", FeeStatus::Paid, 0, *admin);
    CHECK(library.findStudent("STU002")->getFeeStatus() == FeeStatus::Paid);

    // ---- passwords ----
    CHECK(throwsLibraryException([&] { library.changePassword(*saad, "wrong", "newpass"); }));
    library.changePassword(*saad, "123", "newpass");

    // ---- volunteers ----
    const int appId = library.submitApplication(
        VolunteerApplication(0, "Vol", "vol@example.com", "", "Weekends", "Because"));
    CHECK(throwsLibraryException([&] {
        library.submitApplication(VolunteerApplication(0, "Bad", "not-an-email", "", "", ""));
    }));
    CHECK(throwsLibraryException([&] { library.reviewApplication(appId, ApplicationStatus::Approved, *teacher); }));
    library.reviewApplication(appId, ApplicationStatus::Approved, *admin);

    // ---- everything was saved: a fresh Library sees the same data ----
    Library reloaded(dir.u8string());
    reloaded.load();
    CHECK(reloaded.books().size() == 3);
    CHECK(reloaded.books()[1].getTitle() == "Book, Two");          // comma survived save
    CHECK(reloaded.loans().size() == 1);
    CHECK(!reloaded.loans()[0].isActive());
    CHECK(reloaded.students().size() == 3);
    CHECK(reloaded.login("saad", "newpass", Role::Student) != nullptr);
    CHECK(reloaded.applications()[0].getStatus() == ApplicationStatus::Approved);
    CHECK(reloaded.history().size() >= 10);
    CHECK(reloaded.loadWarnings().empty());                         // bad row was dropped on save

    LibraryStatistics stats = reloaded.statistics();
    CHECK(stats.totalBooks == 3 && stats.availableBooks == 3 && stats.totalStudents == 3);
}

static void testOverdueReturn(const fs::path &dir)
{
    const Date today = Date::today();

    writeFile(dir / "Books.csv", "ID,Title,Author,Genre,Year,ISBN,Status\n1,Old,A,G,2000,1,Issued\n");
    writeFile(dir / "Users.csv",
              "ID,Username,Name,Password,Books_Borrowed,Warnings,Fee_Status\nSTU001,s,S,123,1,2,Paid\n");
    writeFile(dir / "Faculty.csv", "ID,Username,Name,Password,Role\n1,t,T,123,Faculty\n");
    writeFile(dir / "Loans.csv",
              "LoanID,BookID,StudentID,IssueDate,DueDate,ReturnDate,Status\n"
              "L0001,1,STU001," + today.addDays(-20).toString() + "," +
                  today.addDays(-6).toString() + ",,Active\n");

    Library library(dir.u8string());
    library.load();
    Person *teacher = library.login("t", "123", Role::Faculty);

    CHECK(library.statistics().overdueLoans == 1);
    CHECK(library.returnBook("L0001", *teacher) == 6);

    const Student *student = library.findStudent("STU001");
    CHECK(student->getWarnings() == 3);
    CHECK(student->getFeeStatus() == FeeStatus::Pending);

    std::string reason;
    CHECK(!student->canBorrow(reason));
}

int main()
{
    const fs::path root = fs::temp_directory_path() / "lms_core_tests";
    fs::remove_all(root);
    fs::create_directories(root / "a");
    fs::create_directories(root / "b");

    try
    {
        testCsvParser();
        testDate();
        testPolymorphism();
        testLibrary(root / "a");
        testOverdueReturn(root / "b");
    }
    catch (const std::exception &e)
    {
        std::cerr << "Unexpected exception: " << e.what() << "\n";
        failures++;
    }

    fs::remove_all(root);

    std::cout << (checks - failures) << " / " << checks << " checks passed\n";
    return failures == 0 ? 0 : 1;
}
