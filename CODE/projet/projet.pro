#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T23:33:33
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet
QT += widgets
QT += xml
QT += sql
QT += testlib
CONFIG += c++11
CONFIG += console debug

SOURCES += main.cpp\
    UTProfiler.cpp \
    UVEditeur.cpp \
    profiler.cpp \
    affichage.cpp \
    CursusEditeur.cpp \
    dossier.cpp \
    EtudiantEditeur.cpp

HEADERS  +=UTProfiler.h \
    UVEditeur.h \
    manager.h \
    TEST/testUV.h \
    TEST/testManager.h \
    profiler.h \
    affichage.h \
    CursusEditeur.h \
    dossier.h \
    EtudiantEditeur.h

