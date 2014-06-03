#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include <QTextStream>
#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QCombobox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <type_traits>
#include <QFileDialog>

#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QLabel>
#include <QDebug>

using namespace std;


class UTProfilerException{
public:
    UTProfilerException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

template<typename T>
class Manager{
   protected: //    ttribut accessible uniquement par les classes filles
    Manager(const Manager& m);
    Manager& operator=(const Manager& m);
    Manager():t(0),nb(0),nbMax(0),file(""),modification(false){}
    virtual ~Manager(){}
    T** t;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(T* t);
    bool modification;
   // T* trouver(const QString& c) const=0;
    QString file;
    friend struct Handler;
    struct Handler{
        Manager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;
    QSqlDatabase mydb;

 public:
    bool connect();
    void disconnect();
    static void libererInstance();
    class Iterator {
        friend class Manager;
        T** currentT;
        unsigned int nbRemain;
        Iterator(T** t, unsigned nb):currentT(t),nbRemain(nb){}
    public:
       static Manager<T>& getInstance(){if (!handler.instance) handler.instance = new Manager<T>; /* instance créée une seule fois lors de la première utilisation*/
            return *handler.instance;}
       static void libererInstance();


        Iterator():nbRemain(0),currentT(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            nbRemain--;
            currentT++;
        }
        T& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentT;
        }
    };
    Iterator getIterator() {
        return Iterator(t,nb);
    }

    class iterator { //defini avec les opérateurs de surchages STD
        T** current;
        iterator(T** t):current(t){}
        friend class Manager;
    public:
        iterator():current(0){};
        T& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(t); }
    iterator end() { return iterator(t+nb); }
};


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


#endif // MANAGER_H
