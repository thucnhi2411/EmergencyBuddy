#-------------------------------------------------
#
# Project created by QtCreator 2018-04-22T17:48:52
#
#-------------------------------------------------



QT       += core gui
QT += webengine webenginewidgets
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp\
        ..\DB\userdb.cpp\
        ..\DB\eventdb.cpp\
        ..\DB\frtaskdb.cpp \
        ..\publicuser\puser.cpp \
        ..\publicuser\post.cpp \
        ..\publicuser\allpost.cpp \
        ..\publicuser\fresponder.cpp \
        ..\publicuser\planner.cpp \
        ..\publicuser\task.cpp \
        ..\publicuser\alltask.cpp \
    postui.cpp \
    postviewui.cpp \
    plaview2pui.cpp \
    taskui.cpp \
    taskviewui.cpp


HEADERS += \
        mainwindow.h\
        ..\DB\userdb.h\
        ..\DB\eventdb.h\
        ..\DB\frtaskdb.h \
        ..\publicuser\puser.h \
        ..\publicuser\post.h \
        ..\publicuser\allpost.h \
        ..\publicuser\fresponder.h \
        ..\publicuser\planner.h \
        ..\publicuser\task.h \
        ..\publicuser\alltask.h \
    postui.h \
    postviewui.h \
    plaview2pui.h \
    taskui.h \
    taskviewui.h

FORMS += \
        mainwindow.ui \
    postui.ui \
    postviewui.ui \
    plaview2pui.ui \
    taskui.ui \
    taskviewui.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    pfaffnick.png
