#ifndef PROFILER_H
#define PROFILER_H
#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>
#include <QStackedWidget>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QLabel>
#include <QDebug>

#include "UVEditeur.h"
#include "UTProfiler.h"
#include "CursusEditeur.h"

class Profiler : public QMainWindow{
Q_OBJECT
    QSqlDatabase mydb;
    QWidget *centralWidget;
    CursusEditeurNew* addcursus;
public:
explicit Profiler(QWidget *parent = 0);

signals:
public slots:
    bool connectDb(){ mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/SQLite/UTProfiler.s3db");
        if(!mydb.open()){
           qDebug()<<"failed";
           return false;
         }
         else
         {
            qDebug()<<"succes";
            return true;
         }
    }
    void deconnect(){
        QString connection;
        connection=mydb.connectionName();
        QSqlDatabase::removeDatabase(connection);
    }
    void quit();
    void openChargerUV();
    void openChargerCursus();
    void NewUV();
    void ChangeUV();
    void NewCursus();
    void SetUVCursus();
};
#endif
