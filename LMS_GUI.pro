QT += widgets

CONFIG += c++17

TARGET = LMS_GUI

# Lets us write #include "model/Book.h" from anywhere
INCLUDEPATH += src

# =========================================================
# MODEL - plain C++ classes (no Qt)
# =========================================================

SOURCES += \
    src/model/Admin.cpp \
    src/model/Book.cpp \
    src/model/Date.cpp \
    src/model/Enums.cpp \
    src/model/Faculty.cpp \
    src/model/HistoryEntry.cpp \
    src/model/Loan.cpp \
    src/model/Person.cpp \
    src/model/Student.cpp \
    src/model/VolunteerApplication.cpp

HEADERS += \
    src/model/Admin.h \
    src/model/Book.h \
    src/model/CsvSerializable.h \
    src/model/Date.h \
    src/model/Enums.h \
    src/model/Faculty.h \
    src/model/HistoryEntry.h \
    src/model/Loan.h \
    src/model/Person.h \
    src/model/Student.h \
    src/model/VolunteerApplication.h

# =========================================================
# STORAGE - CSV parsing and file handling (no Qt)
# =========================================================

SOURCES += \
    src/storage/CsvParser.cpp \
    src/storage/FileHandler.cpp

HEADERS += \
    src/storage/CsvParser.h \
    src/storage/Exceptions.h \
    src/storage/FileHandler.h

# =========================================================
# CORE - library rules (no Qt)
# =========================================================

SOURCES += src/core/Library.cpp
HEADERS += src/core/Library.h

# =========================================================
# USER INTERFACE - Qt widgets
# =========================================================

SOURCES += \
    main.cpp \
    src/ui/DashboardPage.cpp \
    src/ui/DataSetup.cpp \
    src/ui/LoginPage.cpp \
    src/ui/MainWindow.cpp \
    src/ui/Theme.cpp \
    src/ui/WelcomePage.cpp \
    src/ui/dialogs/BookDialog.cpp \
    src/ui/dialogs/FormDialog.cpp \
    src/ui/dialogs/IssueBookDialog.cpp \
    src/ui/dialogs/ProfileDialog.cpp \
    src/ui/dialogs/StudentDialog.cpp \
    src/ui/dialogs/VolunteerDialog.cpp \
    src/ui/pages/BasePage.cpp \
    src/ui/pages/BooksPage.cpp \
    src/ui/pages/HistoryPage.cpp \
    src/ui/pages/LoansPage.cpp \
    src/ui/pages/MembersPage.cpp \
    src/ui/pages/OverviewPage.cpp \
    src/ui/pages/VolunteersPage.cpp \
    src/ui/widgets/RoleCard.cpp \
    src/ui/widgets/StatCard.cpp \
    src/ui/widgets/WrapLabel.cpp

HEADERS += \
    src/ui/DashboardPage.h \
    src/ui/DataSetup.h \
    src/ui/LoginPage.h \
    src/ui/MainWindow.h \
    src/ui/Theme.h \
    src/ui/WelcomePage.h \
    src/ui/dialogs/BookDialog.h \
    src/ui/dialogs/FormDialog.h \
    src/ui/dialogs/IssueBookDialog.h \
    src/ui/dialogs/ProfileDialog.h \
    src/ui/dialogs/StudentDialog.h \
    src/ui/dialogs/VolunteerDialog.h \
    src/ui/pages/BasePage.h \
    src/ui/pages/BooksPage.h \
    src/ui/pages/HistoryPage.h \
    src/ui/pages/LoansPage.h \
    src/ui/pages/MembersPage.h \
    src/ui/pages/OverviewPage.h \
    src/ui/pages/VolunteersPage.h \
    src/ui/widgets/RoleCard.h \
    src/ui/widgets/StatCard.h \
    src/ui/widgets/WrapLabel.h

# Stylesheet + sample CSV files built into the program
RESOURCES += resources/resources.qrc

DISTFILES += \
    resources/theme.qss \
    resources/seed/*.csv

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
