#include "dossier.h"

void Dossier::setCursus(const QString& cur){
    CursusManager& c=CursusManager::getInstance();
    cursus=&(c.getCursus(cur));
}

Dossier* DossierManager::trouver(unsigned int nb)const{
    for(unsigned int i=0; i<nb; i++)
        if (nb==t[i]->getNumero()) return t[i];
    return 0;
}

Dossier& DossierManager::getDossier(unsigned int nb){
    Dossier* dossier=trouver(nb);
    if (!dossier) throw UTProfilerException("erreur, DossierManager, dossier inexistante");
    return *dossier;
}

const Dossier& DossierManager::getDossier(unsigned int nb)const{
    return const_cast<DossierManager*>(this)->getDossier(nb);
}

Inscription* Dossier::InscriptionManager::trouver(const UV& u, const Semestre& s)const{
    for(unsigned int i=0; i<nb; i++)
//        if (u==t[i]->getUV()) return t[i];
    return 0;
}
