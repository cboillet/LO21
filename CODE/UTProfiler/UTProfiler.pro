#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T19:02:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTProfiler
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainutprofiler.cpp \
    uvadddialog.cpp \
    dialogupdatedeleteuv.cpp \
    UTProfiler.cpp

HEADERS  += mainutprofiler.h \
    uvadddialog.h \
    dialogupdatedeleteuv.h \
    manager.h \
    UTProfiler.h

FORMS    += mainutprofiler.ui \
    uvadddialog.ui \
    dialogupdatedeleteuv.ui
