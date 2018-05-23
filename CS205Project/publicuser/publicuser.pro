TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

QT += core sql

SOURCES += \
        main.cpp \
    puser.cpp \
    ..\DB\userdb.cpp \
    post.cpp \
    ..\DB\eventdb.cpp \
    allpost.cpp \
    fresponder.cpp \
    planner.cpp \
    task.cpp \
    ..\DB\frtaskdb.cpp \
    alltask.cpp

HEADERS += \
    puser.h \
    ..\DB\userdb.h \
    post.h \
    ..\DB\eventdb.h \
    allpost.h \
    fresponder.h \
    planner.h \
    task.h \
    ..\DB\frtaskdb.h \
    alltask.h
