#ifndef DOSSIER_H
#define DOSSIER_H
#include<vector>
#include "UTProfiler.h"


/*******INSCRIPTION*******/
class Inscription {
    const UV* uv;
    Semestre semestre;
    Note resultat;
public:
    Inscription(const UV& u, const Semestre& s, Note res=Note::EC):uv(&u),semestre(s),resultat(res){}
    const UV& getUV() const { return *uv; }
    const Semestre& getSemestre() const { return semestre; }
   // UV& getUV(){return &uv;}
    Semestre& getSemestre(){return semestre;}
    Note getResultat() const { return resultat; }
    void setResultat(Note newres) { resultat=newres; }
};

/**********Dossier*********/
class Dossier{
    unsigned int numero;
    bool valide;
    Cursus* cursus;
    class InscriptionManager: public Manager<Inscription,InscriptionManager>{
        private:
            //StrategieAddUvToDossierSQL* stratUV;
            Inscription* trouver(const UV& u, const Semestre& s) const; //peut ï¿½tre mettre T en paramï¿½tre
        protected:
            ~InscriptionManager();
        public:
            InscriptionManager():Manager<Inscription,InscriptionManager>(){/*stratUV=new StrategieAddUvToDossierSQL;*/}
            //void ajouter(const QString& c, QSqlDatabase& db) {stratUV->ajouterUvToDossier(*this,c,db);} //utiliser l'itérateur sur les UV
        };
protected:
    Dossier(){}
    Dossier(const Dossier& cu){}
    Dossier& operator=(const Dossier& cu){}
    Dossier(unsigned int i):numero(i),valide(false){}
    friend class DossierManager;

 public:
    unsigned int getNumero() const {return numero;}
    bool getValidation() const {return valide;}
    Cursus* getCursus() const {return cursus;}
    void valider() { valide=true; }
    void setCursus(const QString& cur);
};

/*******DossierManager*******/
class DossierManager: public Manager<Dossier,DossierManager>{
private:
        Dossier* trouver(unsigned int num) const; //peut ï¿½tre mettre T en paramï¿½tre

public:
   void load(QSqlDatabase& db){}
   ~DossierManager(){}
   DossierManager():Manager<Dossier,DossierManager>(){}
   Dossier& getDossier(unsigned int nb);
   const Dossier& getDossier(unsigned int) const;
   void addDossier(unsigned int n,QSqlDatabase& db){}
};




#endif // DOSSIER_H
