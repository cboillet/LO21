#ifndef DOSSIER_H
#define DOSSIER_H
#include<vector>
#include "UTProfiler.h"

class Inscription;
class Etudiant;
class DossierManager;

/*******INSCRIPTION*******/
class Inscription {
    const UV* uv;
    Semestre* semestre;
    Note resultat;
public:
    Inscription(const UV& u, Semestre& s, Note res=Note::EC):uv(&u),semestre(&s),resultat(res){}
    const UV& getUV() const { return *uv; }
    //const Semestre& getSemestre() const { return *semestre; }
   // UV& getUV(){return &uv;}
    Semestre* getSemestre(){return semestre;}
    Note getResultat() const { return resultat; }
    void setResultat(Note newres) { resultat=newres; }
};


class Etudiant{
    QString nom;
    QString prenom;
    Cursus* cursus;
    class DossierManager;
protected:
    Etudiant(){}
    Etudiant(const Etudiant& etu){}
    Etudiant& operator=(const Etudiant& etu);
    Etudiant(const QString& n, const QString& p):nom(n),prenom(p){}
    friend class EtudiantManager;
public:
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    const QString& geNom() const {return const_cast<const QString&>(nom);}
    const QString& gePrenom() const {return const_cast<const QString&>(prenom);}
    Cursus* getCursus() const {return cursus;}
    void setCursus(const QString& cur);
};

/*********UTProfiler (=Etudiant Manager)*********/
class EtudiantManager: public Manager<Etudiant,EtudiantManager> {
    Etudiant* trouver(QString n) const; //peut ï¿½tre mettre T en paramï¿½tre
    public:
    void load(QSqlDatabase& db);
    ~EtudiantManager(){}
    EtudiantManager():Manager<Etudiant,EtudiantManager>(){}
    Etudiant& getEtudiant(QString n);
    const Etudiant& getEtudiant(QString n) const;
    void addEtudiant(const QString& nom, const QString& pre,const QString& cur);
};




/**********Dossier*********/
class Dossier{
    unsigned int numero;
    bool valide;
    bool past; // dossier des uv obtenues par l'étudiant
    class InscriptionManager;
protected:
    Dossier(){}
    Dossier(const Dossier& cu){}
    Dossier& operator=(const Dossier& cu){}
    Dossier(unsigned int i,unsigned int fini=0):numero(i),valide(false),past(0){}
    friend class DossierManager;

 public:
    unsigned int getNumero() const {return numero;}
    bool getValidation() const {return valide;}
    bool getPasse() const {return past;}
    void valider() { valide=true; }
    void passe() {past=true;}
};


/*******DossierManager*******/
class Etudiant::DossierManager: public Manager<Dossier,DossierManager>{
private:
        Dossier* trouver(unsigned int num) const; //peut ï¿½tre mettre T en paramï¿½tre

public:
   void load(QSqlDatabase& db){}
   ~DossierManager(){}
   DossierManager():Manager<Dossier,DossierManager>(){}
   Dossier& getDossier(unsigned int nb);
   const Dossier& getDossier(unsigned int nb) const;
   void addDossier(unsigned int n,QSqlDatabase& db){}
};

/******InscriptionManager*******/
class Dossier::InscriptionManager: public Manager<Inscription,InscriptionManager>{
    private:
        //StrategieAddUvToDossierSQL* stratUV;
        Inscription* trouver(const QString& u, unsigned int a, const QString& s) const; //peut ï¿½tre mettre T en paramï¿½tre
    protected:
        ~InscriptionManager();
    public:
        InscriptionManager():Manager<Inscription,InscriptionManager>(){}
        Inscription& getInscription(const QString& u, unsigned int a, const QString& s);
        const Inscription& getInscription(const QString& u, unsigned int a, const QString& s) const;
        void ajouter(const QString& c, QSqlDatabase& db) {} //utiliser l'itérateur sur les UV
    };

#endif // DOSSIER_H
