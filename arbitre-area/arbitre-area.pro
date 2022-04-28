QT       += core gui widgets sql
QT       += bluetooth

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basededonnees.cpp \
    club.cpp \
    communicationbluetooth.cpp \
    main.cpp \
    ihmarbitre.cpp \
    rencontre.cpp

HEADERS += \
    basededonnees.h \
    club.h \
    communicationbluetooth.h \
    ihmarbitre.h \
    rencontre.h

FORMS += \
    ihmarbitre.ui

RESOURCES += \
    ressources.qrc

COPIES += bd
bd.files = areapi.sqlite
bd.path = $$OUT_PWD/
bd.base = $$PWD/

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
