#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T23:33:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet
QT += widgets
QT += xml
QT += sql
QT += testlib
CONFIG += c++11

SOURCES += main.cpp\
    UTProfiler.cpp \
    UVEditeur.cpp

HEADERS  +=UTProfiler.h \
    UVEditeur.h \
    manager.h \
    TEST/testUV.h \
    TEST/testManager.h

