#ifndef DOSSIER_H
#define DOSSIER_H
#include<vector>
#include "UTProfiler.h"

///*******INSCRIPTION*******/
//class Inscription {
//    const UV* uv;
//    Semestre semestre;
//    Note resultat;
//public:
//    Inscription(const UV& u, const Semestre& s, Note res=Note::EC):uv(&u),semestre(s),resultat(res){}
//    const UV& getUV() const { return *uv; }
//    Semestre getSemestre() const { return semestre; }
//    Note getResultat() const { return resultat; }
//    void setResultat(Note newres) { resultat=newres; }
//};


//template < class Inscription, class Alloc = allocator<Inscription> > class Dossier{

//};

///**********Dossier*********/
//class Dossier{
//    unsigned int numero;
//    bool valider;
//    Cursus* cursus;
//    class InscriptionManager: public Manager<Inscription,InscriptionManager>{
//        /*
//        private:
//            //StrategieAddUvToDossierSQL* stratUV;
//            Inscription* trouver(const QString& c) const; //peut ï¿½tre mettre T en paramï¿½tre
//        protected:
//            ~InscriptionManager();
//        public:
//            InscriptionManager():Manager<UV,UVManager>(){/*stratUV=new StrategieAddUvToDossierSQL;*/}
//            //void ajouter(const QString& c, QSqlDatabase& db) {stratUV->ajouterUvToDossier(*this,c,db);} //utiliser l'itérateur sur les UV
//        };
//protected:
//    Dossier(){}
//    Dossier(const Dossier& cu);
//    Dossier& operator=(const Dossier& cu);
//    Dossier(unsigned int i):numero(i),valider(0){}
//    friend class DossierManager;

// public:
//    unsigned int getNumero() const {return duree;}
//    bool getValidation() const {return valider;}
//    Cursus* getCursus() const {return cursus;}
//    void valider() { valider=1; }
//    void setCursus(const QString& cursus){}
//};

///*******DossierManager*******/
//class DossierManager: public Manager<Dossier,DossierManager>{
//private:
//        Dossier* trouver(const QString& code) const; //peut ï¿½tre mettre T en paramï¿½tre

//public:
//   void load(QSqlDatabase& db);
//   ~DossierManager();
//   DossierManager():Manager<Dossier,DossierManager>(){}
//   Dossier& getDossier(const QString& c);
//   const Dossier& getDossier(const QString& c) const;
//   void addDossier(const QString& c,const QString& t, unsigned int duree,unsigned int Ccs,unsigned int Ctm,unsigned int Ctsh,unsigned int Csp,QSqlDatabase& db);
///*
//   class FilterIterator {
//        friend class UVManager;
//        UV** currentUV;
//        unsigned int nbRemain;
//        Categorie categorie;
//        FilterIterator(UV** u, unsigned nb, Categorie c):currentUV(u),nbRemain(nb),categorie(c){
//            while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie){
//                nbRemain--; currentUV++;
//            }
//        }
//    public:
//        FilterIterator():nbRemain(0),currentUV(0){}
//        bool isDone() const { return nbRemain==0; }
//        void next() {
//            if (isDone())
//                throw UTProfilerException("error, next on an iterator which is done");
//            do {
//                nbRemain--; currentUV++;
//            }while(nbRemain>0 && (*currentUV)->getCategorie()!=categorie);
//        }
//        UV& current() const {
//            if (isDone())
//                throw UTProfilerException("error, indirection on an iterator which is done");
//            return **currentUV;
//        }
//    };
//    FilterIterator getFilterIterator(Categorie c) {
//        return FilterIterator(t,nb,c);
//    }
//*/
//};


#endif // DOSSIER_H
