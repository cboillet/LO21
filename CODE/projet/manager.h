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
    virtual ~Manager();
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

 public:
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



#endif // MANAGER_H
