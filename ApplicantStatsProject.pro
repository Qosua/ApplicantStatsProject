QT += quick core gui widgets charts

CONFIG += c++17

SOURCES += \
        src/applicant.cpp \
        src/facultycell.cpp \
        src/magichat.cpp \
        src/main.cpp \
        src/mainwindow.cpp \
        src/tableparserbachelor.cpp \
#        src/tableparsermaster.cpp

resources.files +=  styles/white_style.qss
resources.files += programInfo/KCP.xlsx
resources.files += programInfo/columnsNames.xlsx
resources.files += data/maintable.xlsx
resources.prefix = /
RESOURCES += resources

INCLUDEPATH += $$PWD/src/QXlsx/source
LIBS += -L$$PWD/src/QXlsx/lib -lQXlsx

# Default rules for deployment.
# qnx: target.path = /tmp/$${TARGET}/bin
# else: unix:!android: target.path = /opt/$${TARGET}/bin
# !isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/applicant.h \
    src/facultycell.h \
    src/magichat.h \
    src/mainwindow.h \
    src/namespaces.h \
    src/tableparserbachelor.h \
#    src/tableparsermaster.h \
    src/xlsx.h

FORMS += \
    src/mainwindow.ui
