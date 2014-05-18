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

template<typename T>
class Manager{
 private:
    T** t;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(T* t);
    bool modification;
    T* trouver<T>(const QString& c) const=0;
    Manager(const Manager& m);
    Manager& operator=(const Manager& m);
    Manager():t(0),nb(0),nbMax(0),file(""),modification(false){}
    virtual ~Manager();
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

template <typename T> class StrategieUv<T>{
    public:
    void load(Manager<T>& man, const QString& f)=0;
    void save(Manager<T>& man, const QString& f)=0;
    void ajouterUV(Manager<T>&, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
};

template <typename T> class StrategieUvXML<T>: public StrategieUv{
    public:
    void load(Manager<T>& man, const QString& f){}
    void save(Manager<T>& man, const QString& f){}
    void ajouterUV(Manager<T>&, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){}
};
template <typename T> class StrategieUvSQL<T>: public StrategieUv{
    public:
    void load(Manager<T>& man, const QString& f){=0;}
    void save(Manager<T>& man, const QString& f){=0;}
    void ajouterUV(Manager<T>&, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){}
};

template <typename T>
class UVManager: public Manager<T>{
    private:
        StrategieUV stratUV;
        UVManager():Manager<T>(),stratUV(StrategieXML){}
        UV* trouver<T>(const QString& c) const; //peut être mettre T en paramètre
        ~Manager();

    public:
        void load(const StrategieUv& stategie, const QString& f){strat.load(*this,const QString& f);}
        void save(const StrategieUv& strategieSave, const QString& f){strat.save(*this,const QString& f);}
        void ajouter<T>(const Strategie& strat,const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p) {strat.ajouterUV(*this,const QString& f);}
        UV& get<T>(const Strategie& strat, const QString& code);
        const UV& get<T>(const QString& code) const;

        class FilterIterator {
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
};

#endif // MANAGER_H
