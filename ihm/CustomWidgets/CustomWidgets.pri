INCLUDEPATH += ./
DEPENDPATH += $$PWD

HEADERS += $$PWD/slidingstackedwidget.h\
    $$PWD/connection.h \
    $$PWD/playersonline.h \
    $$PWD/rightmenu.h \
    CustomWidgets/chatroom.h \
    CustomWidgets/checkerobject.h \
    CustomWidgets/checkerboardwidget.h \
    CustomWidgets/checkerboardobject.h

SOURCES += $$PWD/slidingstackedwidget.cpp\
    $$PWD/connection.cpp \
    $$PWD/playersonline.cpp \
    $$PWD/rightmenu.cpp \
    CustomWidgets/chatroom.cpp \
    CustomWidgets/checkerobject.cpp \
    CustomWidgets/checkerboardwidget.cpp \
    CustomWidgets/checkerboardobject.cpp

FORMS += \
    $$PWD/connection.ui \
    $$PWD/playersonline.ui \
    $$PWD/rightmenu.ui \
    CustomWidgets/chatroom.ui \
    CustomWidgets/checkerboardwidget.ui
