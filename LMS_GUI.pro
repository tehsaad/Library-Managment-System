QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dashboard.cpp \
    VolunteerDialog.cpp \
    issue_books.cpp \
    loginui.cpp \
    main.cpp \
    mainwindow.cpp \
    profiledialog.cpp

HEADERS += \
    Dashboard.h \
    VolunteerDialog.h \
    issue_books.h \
    loginui.h \
    mainwindow.h \
    profiledialog.h

FORMS += \
    Dashboard.ui \
    VolunteerDialog.ui \
    issue_books.ui \
    loginui.ui \
    mainwindow.ui \
    profiledialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Books.csv
