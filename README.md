# Library Management System

A desktop library system written in **C++17** with a **Qt 6** user interface.
Students borrow books, faculty run the catalog and loans, an administrator
manages members and volunteers — and every change is saved to **CSV files**
through a hand-written CSV parser and file handler.

Built as a first-year Object-Oriented Programming project, so the code tries
to show each OOP idea clearly (see the table below).

---

## Testing the ready-made Windows .exe

This branch (`windows-exe`) contains a pre-built program, so you can try it
without installing Qt:

1. Download `release/LMS_GUI-windows-x64.zip` from this branch
   (open the file on GitHub and click **Download raw file**).
2. Right-click the zip, choose **Extract All...**.
3. Open the extracted `LMS_GUI` folder and double-click **`LMS_GUI.exe`**.
   Keep the `.dll` files and the `platforms` folder next to it.

Windows SmartScreen may say "Windows protected your PC" because the exe is
not signed: click **More info → Run anyway**. Requires 64-bit Windows 10 or 11.

The exe was cross-compiled from Linux with `scripts/build-windows-exe.sh`
(Qt 6.10.2, llvm-mingw).

## Running it

1. Open `LMS_GUI.pro` in **Qt Creator** (Qt 6, MinGW or GCC kit).
2. Press **Run**.

On the first run the program creates a `data/` folder next to the `.exe` and
copies in the sample CSV files. After that it only reads and writes those
files, so your changes are kept between runs. Delete the `data/` folder to
start fresh.

### Sample accounts

| Role    | Username     | Password   |
|---------|--------------|------------|
| Admin   | `admin`      | `admin123` |
| Faculty | `teacher1`   | `1234`     |
| Student | `saad`       | `123`      |
| Student | `student002` | `pass002`  |

The **Volunteer** card on the welcome screen needs no account — it opens an
application form that the admin reviews.

---

## What each role can do

| Feature                           | Student | Faculty | Admin |
|-----------------------------------|:-------:|:-------:|:-----:|
| Search the catalog                | ✓       | ✓       | ✓     |
| Borrow / return own books         | ✓       |         |       |
| Add, edit, remove books           |         | ✓       | ✓     |
| Issue / return books for students |         | ✓       | ✓     |
| View members                      |         | ✓       | ✓     |
| Add, edit, remove members         |         |         | ✓     |
| Review volunteer applications     |         |         | ✓     |
| Activity history                  |         | ✓       | ✓     |

### Library rules (in `Library.cpp` and `Student.cpp`)

- A loan lasts **14 days**.
- A student can hold at most **5 books**.
- A student with a **pending fee** or **3 warnings** cannot borrow.
- Returning a book **late** adds a warning and sets the fee to *Pending*.
- A book that is out cannot be deleted; a student with books cannot be removed.

---

## Project layout

```
main.cpp                  starts Qt, loads the Library, opens MainWindow
src/
  model/                  plain C++ classes (no Qt)
    Enums.h               Role, FeeStatus, BookStatus, LoanStatus, ...
    Date.h                date value class with operator overloading
    CsvSerializable.h     interface: toCsvRow()
    Person.h              abstract base class
    Student.h  Faculty.h  Admin.h
    Book.h  Loan.h  HistoryEntry.h  VolunteerApplication.h
  storage/                plain C++ (no Qt)
    CsvParser.h           splits/joins CSV lines (quotes, commas, "")
    FileHandler.h         reads/writes CSV files with fstream
    Exceptions.h          FileException, LibraryException
  core/
    Library.h             all data + all rules; the GUI only calls this
  ui/                     Qt widgets
    MainWindow            Welcome -> Login -> Dashboard
    WelcomePage, LoginPage, DashboardPage
    pages/                BasePage + Overview, Books, Loans, Members, ...
    dialogs/              FormDialog + Book, Student, IssueBook, ...
    widgets/              RoleCard, StatCard, WrapLabel
    Theme                 loads resources/theme.qss
resources/
  theme.qss               the look: warm ivory, clay accent, serif headings
  seed/*.csv              sample data copied on first run
tests/
  core_tests.cpp          tests for the non-GUI classes
```

The model, storage and core folders use **only standard C++** (`std::string`,
`std::vector`, `std::fstream`). Qt is only used for the windows. That split
means the library logic can be tested without opening a window.

---

## Where each OOP concept is used

| Concept | Where to look |
|---|---|
| **Classes & encapsulation** | Every model class keeps its data `private` and offers getters/setters. `Person::setPassword()` refuses short passwords; `Date` can never hold 30 February. |
| **Abstract class / pure virtual** | `Person::getRole() = 0`, `BasePage::refresh() = 0`, `FormDialog::submit() = 0`, `CsvSerializable::toCsvRow() = 0`. |
| **Inheritance** | `Student : Person`, `Faculty : Person`, `Admin : Faculty` (multilevel). In the GUI: `BooksPage : BasePage`, `BookDialog : FormDialog`, `RoleCard : QPushButton`. |
| **Polymorphism (virtual functions)** | The dashboard asks `user.canManageBooks()`, `canReviewVolunteers()`… and each subclass answers differently — no `if (role == "Admin")` in the GUI. `profileDetails()` shows extra rows only for students. `DashboardPage` calls `refresh()` through `BasePage*` pointers. |
| **Interface** | `CsvSerializable` — anything that can become a CSV row. |
| **Enums** | `enum class Role`, `FeeStatus`, `BookStatus`, `LoanStatus`, `ApplicationStatus`, `ActionType`, plus `LoansPage::LoanFilter` and `Tone`. |
| **Function overloading** | `EnumText::toString(Role)`, `toString(FeeStatus)`, … same name, different parameter. |
| **Operator overloading** | `Date`: `==  !=  <  <=  >  >=` and `-` (days between dates). |
| **Static members** | `Student::MAX_BOOKS`, `Loan::LOAN_PERIOD_DAYS`, `Library::BOOKS_FILE`, static `CsvParser` functions, static `fromCsvRow()` factories. |
| **Factory method** | `Faculty::fromCsvRow()` reads the Role column and returns a `Faculty` *or* an `Admin`. |
| **Templates** | `Library::loadTable<T>()` / `saveTable<T>()` load and save any model class with one function. |
| **Exceptions** | `FileException` and `LibraryException` (both derive from `std::runtime_error`); the GUI catches them and shows the message. |
| **Composition** | `Library` *has a* `FileHandler` and *has* vectors of books, loans and people. |
| **Smart pointers / RAII** | `std::vector<std::unique_ptr<Person>>` owns Students, Faculty and Admins together; files close automatically when the stream goes out of scope. |
| **`dynamic_cast`** | `Library::students()` picks the `Student` objects out of the `Person` list. |
| **Design pattern: template method** | `FormDialog::accept()` calls the subclass's `submit()`. |

---

## CSV files

| File | Columns |
|---|---|
| `Books.csv` | ID, Title, Author, Genre, Year, ISBN, Status |
| `Users.csv` | ID, Username, Name, Password, Books_Borrowed, Warnings, Fee_Status |
| `Faculty.csv` | ID, Username, Name, Password, Role *(Faculty or Admin)* |
| `Loans.csv` | LoanID, BookID, StudentID, IssueDate, DueDate, ReturnDate, Status |
| `History.csv` | Timestamp, User, Action, Details |
| `Volunteers.csv` | ID, Name, Email, Phone, Availability, Reason, Status, AppliedOn |

The parser handles commas inside quotes (`"Smith, John"`) and doubled quotes
(`"He said ""hi"""`). Each file is written to a `.tmp` file first and then
renamed, so a crash never leaves half a file. Rows that cannot be read are
skipped and listed in a warning when the program starts.

`Loans.csv` is the source of truth: on start-up each book's status and each
student's `Books_Borrowed` are recalculated from the active loans.

---

## Running the tests

The tests need only a C++17 compiler (no Qt):

```
g++ -std=c++17 -Isrc tests/core_tests.cpp src/model/*.cpp src/storage/*.cpp src/core/*.cpp -o core_tests
./core_tests
```

They cover CSV parsing, date maths, permissions, borrowing limits, late
returns, and that everything survives a save + reload.

---

## Known simplifications

- Passwords are stored as plain text in the CSV files (fine for a class
  project, never for a real system).
- A CSV field cannot contain a line break (it is turned into a space).
