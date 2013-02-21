TEMPLATE = lib
CONFIG += staticlib
CONFIG += console
CONFIG -= qt

INCLUDEPATH += . ..
WARNINGS += -Wall

HEADERS += include/structures.h \
            include/command.h \
            include/frame.h \
            include/client.h \
            gameboard.h


SOURCES += main.c \
            gameboard.c \
            include/frame.c \
            include/client.c

