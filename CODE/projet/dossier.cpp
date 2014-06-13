#include "dossier.h"

void Etudiant::setCursus(const QString& cur){
    CursusManager& c=CursusManager::getInstance();
    cursus=&(c.getCursus(cur));
}

Dossier* Etudiant::DossierManager::trouver(unsigned int nb)const{
    for(unsigned int i=0; i<nb; i++)
        if (nb==t[i]->getNumero()) return t[i];
    return 0;
}

Dossier& Etudiant::DossierManager::getDossier(unsigned int nb){
    Dossier* dossier=trouver(nb);
    if (!dossier) throw UTProfilerException("erreur, DossierManager, dossier inexistante");
    return *dossier;
}

const Dossier& Etudiant::DossierManager::getDossier(unsigned int nb)const{
    return const_cast<DossierManager*>(this)->getDossier(nb);
}

/*******Inscription********/
/*
Inscription* Dossier::InscriptionManager::trouver(const UV& u, const Semestre& s)const{
    for(unsigned int i=0; i<nb; i++)
        if (u==t[i]->getUV() && s==t[i]->getSemestre()) return t[i];
    return 0;
}

Inscription& Dossier::InscriptionManager::getInscription(const UV& u, const Semestre& s){
    Inscription* inscription=trouver(u,s);
    if (!inscription) throw UTProfilerException("erreur, DossierManager, dossier inexistante");
    return *inscription;
}

const Inscription& Dossier::InscriptionManager::getInscription(const UV& u, const Semestre& s)const{
    return const_cast<EtudiantManager*>(this)->getInscription(u,s);
}
*/
/******ETUDIANT_MANAGER******/
Etudiant* EtudiantManager::trouver(QString n, QString p)const{
    for(unsigned int i=0; i<nb; i++)
        if (n==t[i]->getNom() && p==t[i]->getPrenom()) return t[i];
    return 0;
}

Etudiant& EtudiantManager::getEtudiant(QString n, QString p){
    Etudiant* etudiant=trouver(n,p);
    if (!etudiant) throw UTProfilerException("erreur, DossierManager, dossier inexistante");
    return *etudiant;
}

const Etudiant& EtudiantManager::getEtudiant(QString n, QString p)const{
    return const_cast<EtudiantManager*>(this)->getEtudiant(n,p);
}
