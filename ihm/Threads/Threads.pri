INCLUDEPATH += ./
DEPENDPATH += $$PWD
 
HEADERS += \
    $$PWD/incomingconnectionthread.h \
     $$PWD/chatlistener.h \
    Threads/playerlistener.h \
    Threads/listener.h

SOURCES += \
    $$PWD/incomingconnectionthread.cpp \
     $$PWD/chatlistener.cpp \
    Threads/playerlistener.cpp \
    Threads/listener.cpp
