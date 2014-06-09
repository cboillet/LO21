#ifndef PROFILER_H
#define PROFILER_H
#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>
#include <QStackedWidget>

#include "UVEditeur.h"
#include "UTProfiler.h"

class Profiler : public QMainWindow{
Q_OBJECT
    StrategieSQL* stratSQL;
public:
explicit Profiler(QWidget *parent = 0);

signals:
public slots:
    void quit();
    void openChargerUV();
    void openUV();
};
#endif
