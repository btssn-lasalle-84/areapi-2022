QT       += core gui widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    joueur.cpp \
    equipe.cpp \
    partie.cpp \
    rencontre.cpp \
    ihmafficheur.cpp \
    main.cpp

HEADERS += \
    joueur.h \
    equipe.h \
    partie.h \
    ihmafficheur.h \
    rencontre.h \

FORMS += \
    ihmafficheur.ui

RESOURCES += \
    ressources.qrc

CONFIG(release, debug|release):DEFINES+=QT_NO_DEBUG_OUTPUT
