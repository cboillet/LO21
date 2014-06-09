#ifndef PROFILER_H
#define PROFILER_H
#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>
#include <QStackedWidget>

#include "UVEditeur.h"
#include "UTProfiler.h"
#include "CursusEditeur.h"

class Profiler : public QMainWindow{
Q_OBJECT
    StrategieSQL* stratSQL;
    QWidget *centralWidget;
    CursusEditeurNew* addcursus;
public:
explicit Profiler(QWidget *parent = 0);

signals:
public slots:
    void quit();
    void openChargerUV();
    void NewUV();
    void ChangeUV();
    void NewCursus();
    void ChangeCursus();
};
#endif
