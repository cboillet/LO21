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

enum Equival{FormationPrecedente,SejourEtranger};
enum Categorie {
	/* Connaissances Scientifiques */ CS,  /* Techniques et Mï¿½thodes */ TM, 
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
/************UV*********/
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
class Credits{
    Categorie categorie;
    unsigned int nbcredits;
};


QTextStream& operator<<(QTextStream& f, const UV& uv);
 /*******Strategie*******/
class StrategieSQL{
protected:
    QSqlDatabase mydb;
public:
    bool connect();
    void disconnect();
};
class StrategieUv{
 public:
    virtual void ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p)=0;
    virtual void deleteUV()=0;
};

class StrategieUvXML: public StrategieUv{
 public:
    void load(Manager<UV>& man, const QString& f){;}
    void save(Manager<UV>& man, const QString& f){;}
    void ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){;}
};

class StrategieUvSQL: public StrategieUv, public StrategieSQL{
  public:
    void ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    void deleteUV(){}
};

class StrategieCredits{
 public:
    virtual void ajouterCredits(Manager<Credits>& man, const Categorie& cat, unsigned int nbcredits)=0;
    virtual void deleteUV()=0;
};

class StrategieCreditsXML: public StrategieCredits{
 public:
    void load(Manager<UV>& man, const QString& f){;}
    void save(Manager<UV>& man, const QString& f){;}
    virtual void ajouterCredits(Manager<Credits>& man, const Categorie& cat, unsigned int nbcredits){;}
    virtual void deleteUV(){;}
};

class StrategieCreditsSQL: public StrategieSQL, public StrategieCredits{
  public:
    void ajouterCredits(Manager<Credits>& man, const Categorie& cat, unsigned int nbcredits);
    void deleteCredits(){;}
};

class StrategieAddUvToCursusSQL:public StrategieSQL{
public:
    void ajouterUvToCursus(Manager<UV>& man, const QString& c);
    void deleteUvToCursus(){;}
};

class StrategieAddCreditsToCursusSQL:public StrategieSQL{
public:
    void ajouterCreditsToCursus(Manager<Credits>& man, const Credits& cursus);
    void deleteCreditsToCursus(){;}
};

/*******UVManager*******/
class UVManager: public Manager<UV>{
    private:
        StrategieUvSQL* stratUV;
        UV* trouver(const QString& c) const; //peut ï¿½tre mettre T en paramï¿½tre
     protected:
        ~UVManager();

    public:
        UVManager():Manager<UV>(),stratUV(0){};
        //void load(const QString& f){stratUV->load(*this,f);} //downcasting
        //void save(const QString& f){stratUV->save(*this,f);}
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

/********CreditsManager**********/
class CreditsManager: public Manager<Credits>{
private:
    StrategieCreditsSQL* stratCredits;

public:
    ~CreditsManager();
    CreditsManager():Manager<Credits>(),stratCredits(0){};
    void ajouterCredits(const Categorie& cat, unsigned int n) {stratCredits->ajouterCredits(*this,cat,n);}
};

/**********Equivalence*********/
class Equivalence{
    Equival equivalence;
    CreditsManager creditsObtenus;
public:
    Equivalence(){}
    Equivalence(const Equival& equi):equivalence(equi){}
    Equival getEquivalence()const{return equivalence;}
    ~Equivalence();
};

/**********Cursus*********/
class Cursus{
    QString titre;
    unsigned int duree;
    class UVObligatoire: public Manager<UV>{
    private:
        StrategieAddUvToCursusSQL* stratUV;
        UV* trouver(const QString& c) const; //peut ï¿½tre mettre T en paramï¿½tre
     protected:
        ~UVObligatoire();
    public:
        UVObligatoire():Manager<UV>(),stratUV(0){};
        void ajouter(const QString& c) {stratUV->ajouterUvToCursus(*this,c);} //utiliser l'itérateur sur les UV
         };

    class CreditsObligatoire: public Manager<Credits>{
    private:
        StrategieAddCreditsToCursusSQL* stratCredits;
     protected:
        ~CreditsObligatoire();
    public:
        CreditsObligatoire():Manager<Credits>(),stratCredits(0){};
        void ajouter(const Credits& c) {stratCredits->ajouterCreditsToCursus(*this,c);} //utiliser l'itérateur sur les UV
         };

    Cursus(const Cursus& cu);
    Cursus& operator=(const Cursus& cu);
    Cursus(const QString& t, unsigned int dur):titre(t),duree(dur){}
    friend class CursusManager;
    Equivalence equival;

 public:
    QString getTitre() const { return titre; }
    unsigned int getDuree() const { return duree; }
    void setTitre(const QString& t) { titre=t; }
    void setDuree(unsigned int n) { duree=n; }

};

/*******CursusManager*******/
class CursusManager: public Manager<Cursus>{
private:
        //StrategieCursusSQL* stratCursus;
        Cursus* trouver(const QString& t) const; //peut ï¿½tre mettre T en paramï¿½tre
protected:
   ~CursusManager();

public:
  // StrategieManager():Manager<Cursus>(),stratCursus(new StrategieCursusSQL){};
   //void ajouter(const QString& t, unsigned int duree, ,const Categorie& cat, unsigned int n) {stratUV->ajouterUV(*this,c,t,nbc,cat,a,p);}
   Cursus& getCursus(const QString& t);
   const Cursus& getCursus(const QString& t) const;
/*
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
*/
};


/*******INSCRIPTION*******/
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
