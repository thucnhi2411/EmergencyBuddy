TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

QT += core                # this should be added
QT += sql                 # this should be added

SOURCES += main.cpp \
    userdb.cpp \
    firstresponderdb.cpp \
    frtaskdb.cpp \
    simulationdb.cpp \
    simulationresultdb.cpp \
    eventdb.cpp

HEADERS += \
    userdb.h \
    firstresponderdb.h \
    frtaskdb.h \
    simulationdb.h \
    simulationresultdb.h \
    eventdb.h
