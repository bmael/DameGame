TEMPLATE = lib
CONFIG += staticlib
CONFIG += console
CONFIG -= qt

INCLUDEPATH += . ..
WARNINGS += -Wall

HEADERS += structures.h \
    gameboard.h \
    client.h

SOURCES += main.c \
    gameboard.c \
    client.c

