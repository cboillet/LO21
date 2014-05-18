#ifndef MAINUTPROFILER_H
#define MAINUTPROFILER_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QLabel>
#include <QDebug>

namespace Ui {
class MainUTProfiler;
}

class MainUTProfiler : public QMainWindow
{
    Q_OBJECT

public :
    QSqlDatabase mydb;

    // Connexion et déconnexion à la base
    bool connectDb(){


        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("C:/SQlite/DataBase/UTProfiler.db");
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
        //mydb.close();
       // mydb.removeDatabase(QSqlDatabase::defaultConnection);

    }

public:
    ~MainUTProfiler();

private:
    Ui::MainUTProfiler *ui;
    static MainUTProfiler *utProfiler;
    explicit MainUTProfiler(QWidget *parent = 0);
    MainUTProfiler& operator=(const MainUTProfiler& ut);
    MainUTProfiler(const MainUTProfiler&);


public :
    static MainUTProfiler& getUTProfiler(){
            if(!utProfiler){
                utProfiler = new MainUTProfiler();
                return *utProfiler;
            }
            return *utProfiler;
    }
    static void deleteUTProfiler(){
        delete utProfiler;
    }


private slots:
    void on_addUV_clicked();
    void on_updateDeleteUV_clicked();
};

#endif // MAINUTPROFILER_H
