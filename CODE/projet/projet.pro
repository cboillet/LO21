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
CONFIG += c++11

SOURCES += main.cpp\
    UTProfiler.cpp \
    UVEditeur.cpp \
    CursusEditeur.cpp \
    CursusProfiler.cpp \
    mainwindow.cpp

HEADERS  +=UTProfiler.h \
    UVEditeur.h \
    manager.h \
    CursusEditeur.h \
    CursusProfiler.h \
    mainwindow.h \
    ui_mainwindow.h \
    TestUV.h

FORMS += \
    CursusEditeur.ui \
    CatalogueUV.ui \
    CatalogueCursus.ui \
    mainwindow.ui

