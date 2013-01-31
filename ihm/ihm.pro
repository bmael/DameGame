#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T09:52:26
#
#-------------------------------------------------
DEPENDPATH += $$PWD
INCLUDEPATH += . ..
WARNINGS += -Wall

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../Game
TEMPLATE = app

include($$PWD/CustomWidgets/CustomWidgets.pri)
include($$PWD/Threads/Threads.pri)

LIBS += ../DameGame/libDameGame.a

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

OBJECTS_DIR = .cmp/obj
MOC_DIR = .cmp/moc
RCC_DIR = .cmp/rcc
UI_DIR = .cmp/ui

INCLUDEPATH += $$PWD/../DameGame
DEPENDPATH += $$PWD/../DameGame
