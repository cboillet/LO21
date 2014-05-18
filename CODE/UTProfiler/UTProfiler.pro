#-------------------------------------------------
#
# Project created by QtCreator 2014-05-11T19:02:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTProfiler
TEMPLATE = app


SOURCES += main.cpp\
        mainutprofiler.cpp \
    uvadddialog.cpp \
    dialogupdatedeleteuv.cpp

HEADERS  += mainutprofiler.h \
    uvadddialog.h \
    dialogupdatedeleteuv.h

FORMS    += mainutprofiler.ui \
    uvadddialog.ui \
    dialogupdatedeleteuv.ui
