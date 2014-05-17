#ifndef MANAGER_H
#define MANAGER_H
#include "UTProfiler.h"
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

template<class T>
class Manager{
 private:
    T** t;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(T* t);
    bool modification;
    T* trouver(const QString& c) const=0;
    Manager(const Manager& m);
    Manager& operator=(const Manager& m);
    Manager():t(0),nb(0),nbMax(0),file(""),modification(false){}
    ~Manager()=0;
    QString file;
    friend struct Handler;
    struct Handler{
        Manager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

 public:

    void load(const QString& f);
    void save(const QString& f);
    static Manager& getInstance();
    static void libererInstance();
    //void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    const T& get(const QString& code) const=0;
    T& get(const QString& code)=0; //marche pour UV et Cursus car on tout les deux un attributs noms
    class Iterator {
        friend class Manager;
        T** currentT;
        unsigned int nbRemain;
        Iterator(T** t, unsigned nb):currentT(t),nbRemain(nb){}
    public:
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

   /* class FilterIterator {
        friend class UVManager;
        UV** currentUV;
        unsigned int nbRemain;
        Categorie categorie;
        FilterIterator(UV** u, unsigned nb, Categorie c):currentUV(u),nbRemain(nb),categorie(c){
            while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie){
                nbRemain--; currentUV++;
            }
        }
    public:
        FilterIterator():nbRemain(0),currentUV(0){}
        bool isDone() const { return nbRemain==0; }
        void next() {
            if (isDone())
                throw UTProfilerException("error, next on an iterator which is done");
            do {
                nbRemain--; currentUV++;
            }while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie);
        }
        UV& current() const {
            if (isDone())
                throw UTProfilerException("error, indirection on an iterator which is done");
            return **currentUV;
        }
    };
    FilterIterator getFilterIterator(Categorie c) {
        return FilterIterator(uvs,nbUV,c);
    }
    */
};


#endif // MANAGER_H
