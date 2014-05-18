#include "manager.h"

template <class T>
bool Manager<T>::connect(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/SQlite/DataBase/UTProfiler.db");
    mydb.setHostName("localhost");
    mydb.setUserName("root");
    mydb.setPassword("");
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

template <class T>
void Manager<T>::disconnect(){
    QString connection;
    connection=mydb.connectionName();
    QSqlDatabase::removeDatabase(connection);
}


template <class T>
void Manager<T>::addItem(T* tem){
    if (nb==nbMax){
        T** newtab=new T*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=t[i];
        nbMax+=10;
        T** old=t;
        t=newtab;
        delete[] old;
    }
    t[nb++]=tem;
}

template <class T>
typename Manager<T>::Handler Manager<T>::handler=Handler();


template <class T>
void Manager<T>::libererInstance(){
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}
