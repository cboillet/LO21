#ifndef DOSSIER_H
#define DOSSIER_H
#include "UTProfiler.h"

class Inscription;
class Etudiant;
class Dossier;

/**********Equivalence*********/
class Equivalence{
    QString nomEquivalence;
    Equival equivalence;
    unsigned int nCS;
    unsigned int nTM;
    unsigned int nTSH;
    unsigned int nSP;
    //CreditsManager creditsObtenus;
public:
    Equivalence(){}
    Equivalence(const QString& nom,const Equival& equi,unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP):nomEquivalence(nom), equivalence(equi),nCS(CS),nTM(TM),nTSH(TSH),nSP(SP){}
    Equival getEquivalence()const{return equivalence;}
    QString getNomE() const { return nomEquivalence; }
    const QString& geNomE() const {return const_cast<const QString&>(nomEquivalence);}
    ~Equivalence(){}
};

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
    unsigned int semestre; //numéro du semestre

protected:
    Etudiant(){}
    Etudiant(const Etudiant& etu){}
    Etudiant& operator=(const Etudiant& etu);
    Etudiant(const QString& n, const QString& p):nom(n),prenom(p){}
    friend class EtudiantManager;
public:
    std::vector<Dossier> dossiers;
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    const QString& geNom() const {return const_cast<const QString&>(nom);}
    const QString& gePrenom() const {return const_cast<const QString&>(prenom);}
    Cursus* getCursus() const { return cursus;}
   // std::vector<Dossier>& getDossiers{return dossiers;}
    void setCursus(const QString& cur);
    unsigned int getSemestre(){return semestre;}
    void setSemestre(unsigned int i){semestre=i;}
    void addDossierPasse(unsigned int n,QSqlDatabase& db);
    void addDossier(unsigned int n,QSqlDatabase& db){}
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
    void addEtudiant(const QString& nom, const QString& pre,const QString& cur,unsigned int s);
};

/**********Dossier*********/
class Dossier{
    unsigned int numero;
    bool valide;
    bool past; // dossier des uv obtenues par l'étudiant

protected:
    Dossier(){}
    Dossier& operator=(const Dossier& cu){}
    Dossier(unsigned int i):numero(i),valide(false),past(0){}
    friend class Etudiant;


public:
    std::vector<Inscription> inscriptions;
    std::vector<Equivalence> equivalences;
    Dossier(const Dossier& cu){}
    unsigned int getNumero() const {return numero;}
    bool getValidation() const {return valide;}
    bool getPasse() const {return past;}
    //std::vector<Equivalence>& getEquivalence{return (std::vector<Equivalence>&) equivalence;}
    //std::vector<Inscriptions>& getInscriptions{return (std::vector<Inscriptions>&) inscriptions;}
    void setValidation() { valide=true; }
    void setPasse() {past=true;}
    void addInscription(const UV& u, Semestre& s, Note res=Note::EC);
    void addEquivalence(const QString& titreE, const Equival& typeE, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP);
};


#endif // DOSSIER_H
