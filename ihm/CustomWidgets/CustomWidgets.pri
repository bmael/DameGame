INCLUDEPATH += ./
DEPENDPATH += $$PWD

HEADERS += $$PWD/slidingstackedwidget.h\
    $$PWD/connection.h \
    $$PWD/playersonline.h \
    $$PWD/rightmenu.h \
    CustomWidgets/chatroom.h

SOURCES += $$PWD/slidingstackedwidget.cpp\
    $$PWD/connection.cpp \
    $$PWD/playersonline.cpp \
    $$PWD/rightmenu.cpp \
    CustomWidgets/chatroom.cpp

FORMS += \
    $$PWD/connection.ui \
    $$PWD/playersonline.ui \
    $$PWD/rightmenu.ui \
    CustomWidgets/chatroom.ui
