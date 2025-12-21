QT += quick core gui widgets charts

SOURCES += \
        applicantandfaculthy/applicant.cpp \
        applicantandfaculthy/facultycell.cpp \
        magichat.cpp \
        main.cpp \
        mainwindow.cpp \
        tableparserbachelor.cpp \
#        tableparsermaster.cpp

resources.files =  styles/white_style.qss
resources.files += programInfo/KCP.xlsx
resources.files += programInfo/columnsNames.xlsx
resources.files += data/maintable.xlsx
resources.prefix = /
RESOURCES += resources

INCLUDEPATH += $$PWD/QXlsx/source
LIBS += -L$$PWD/QXlsx/lib -lQXlsx

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

HEADERS += \
    applicantandfaculthy/applicant.h \
    applicantandfaculthy/facultycell.h \
    magichat.h \
    mainwindow.h \
    namespaces.h \
    tableparserbachelor.h \
#    tableparsermaster.h \
    xlsx.h

FORMS += \
    mainwindow.ui
