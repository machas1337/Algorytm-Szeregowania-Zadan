TEMPLATE = app

QT += qml quick
QT += widgets
QT += testlib

CONFIG += c++11

SOURCES += main.cpp \
    zdarzenie.cpp \
    okno.cpp \
    silnik.cpp \
    oknododawania.cpp \
    wykres.cpp \
    definicje.cpp

RESOURCES += \
    zasoby.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    zdarzenie.h \
    okno.h \
    silnik.h \
    oknododawania.h \
    wykres.h

DISTFILES +=

