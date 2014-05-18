#ifndef UT_PROFILER_h
#define UT_PROFILER_h

#include "manager.h"
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


enum Categorie {
	/* Connaissances Scientifiques */ CS,  /* Techniques et M�thodes */ TM, 
    /* Technologies et Sciences de l'Homme */ TSH, /* Stage et Projet */ SP, /* Projet */ TX
};

QTextStream& operator<<(QTextStream& f, const Categorie& s);
Categorie StringToCategorie(const QString& s);
QString CategorieToString(Categorie c);
QTextStream& operator>>(QTextStream& f, Categorie& cat);

enum Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC};


/*class NoteIterator {
    Note value;
    NoteIterator(Note val):value(val){}
public:
    static NoteIterator getFirst() { return NoteIterator(first); }
    bool isDone() const { return value>last; }
    Note operator*() const { return value; }
    void next() { std::underlying_type<Note>::type(value)++; }
};*/

enum Saison {Automne, Printemps};
inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Automne) f<<"A"; else f<<"P"; return f;}

/*
template<typename EnumType>
class EnumIterator {
    static_assert(is_enum<EnumType>::value, "EnumType have to be an enum"); //affiche le message d'erreur si is_enum est false
    EnumType value;
    EnumIterator(EnumType val):value(val){}
public:
    static EnumIterator getFirst() { return EnumIterator(EnumType::first); } //prblm first& last
    bool isDone() const { return value>EnumType::last; }
    EnumType operator*() const { return value; }
    void next() { value=(EnumType)(std::underlying_type<EnumType>::type(value)+1); }
};

typedef EnumIterator<Note> NoteIterator;
typedef EnumIterator<Categorie> CategorieIterator;
typedef EnumIterator<Saison> SaisonIterator;
*/

class Semestre {
	Saison saison;
	unsigned int annee;
public:
	Semestre(Saison s, unsigned int a):saison(s),annee(a){ if (annee<1972||annee>2099) throw UTProfilerException("annee non valide"); }
	Saison getSaison() const { return saison; }
	unsigned int getAnnee() const { return annee; }
};

inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison()<<s.getAnnee()%100; }

class UV {
    QString code;
    QString titre;
	unsigned int nbCredits;
	Categorie categorie;
    bool automne;
    bool printemps;
	UV(const UV& u);
	UV& operator=(const UV& u);
    UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p):
      code(c),titre(t),nbCredits(nbc),categorie(cat),automne(a),printemps(p){}
	friend class UVManager;
public:
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
	unsigned int getNbCredits() const { return nbCredits; }
	Categorie getCategorie() const { return categorie; }
    bool ouvertureAutomne() const { return automne; }
    bool ouverturePrintemps() const { return printemps; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setNbCredits(unsigned int n) { nbCredits=n; }
    void setCategorie(Categorie c) { categorie=c; }
    void setOuvertureAutomne(bool b) { automne=b; }
    void setOuverturePrintemps(bool b) { printemps=b; }
};

QTextStream& operator<<(QTextStream& f, const UV& uv);

class StrategieUv{
    public:
    virtual void load(Manager<UV>& man, const QString& f) =0;
    virtual void save(Manager<UV>& man, const QString& f) =0;
    virtual void ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p)=0;
};

class StrategieUvXML: public StrategieUv{
    public:
    void load(Manager<UV>& man, const QString& f){;}
    void save(Manager<UV>& man, const QString& f){;}
    void ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){;}
};
class StrategieUvSQL: public StrategieUv{
    public:
    void load(Manager<UV>& man){}
    void save(Manager<UV>& man){}
    void ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){}
};



class UVManager: public Manager<UV>{
    private:
        StrategieUv* stratUV;
        UV* trouver(const QString& c) const; //peut �tre mettre T en param�tre
        ~UVManager();

    public:
        UVManager():Manager<UV>(),stratUV(0){};
        void load(const QString& f){stratUV->load(*this,f);} //downcasting
        void save(const QString& f){stratUV->save(*this,f);}
        void ajouter(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p) {stratUV->ajouterUV(*this,c,t,nbc,cat,a,p);}
        UV& getUV(const QString& code);
        const UV& getUV(const QString& code) const;

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
             return FilterIterator(t,nb,c);
         }
};

class Inscription {
	const UV* uv;
	Semestre semestre;
	Note resultat;
public:
    Inscription(const UV& u, const Semestre& s, Note res=EC):uv(&u),semestre(s),resultat(res){}
	const UV& getUV() const { return *uv; }
	Semestre getSemestre() const { return semestre; }
	Note getResultat() const { return resultat; }
	void setResultat(Note newres) { resultat=newres; }
};

class Dossier {
};

class Formation{
};


#endif
