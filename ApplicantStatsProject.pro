QT += quick core gui widgets charts

SOURCES += \
        applicant.cpp \
        facultycell.cpp \
        magichat.cpp \
        main.cpp \
        mainwindow.cpp \
        tableparser.cpp

resources.files += styles/white_style.qss
resources.prefix = /
RESOURCES += resources

INCLUDEPATH += QXlsx\source
LIBS += -L C:\Repos\Qt\ApplicantStatsProject\QXlsx\lib -lQXlsx

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    applicant.h \
    facultycell.h \
    magichat.h \
    mainwindow.h \
    tableparser.h \
    xlsx.h

DISTFILES += \
    CustomButton.qml \
    columnsNames

FORMS += \
    mainwindow.ui
