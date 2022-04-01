QT       += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    equipe.cpp \
    main.cpp \
    ihmafficheur.cpp

HEADERS += \
    equipe.h \
    ihmafficheur.h

FORMS += \
    ihmafficheur.ui

RESOURCES += \
    ressources.qrc

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
