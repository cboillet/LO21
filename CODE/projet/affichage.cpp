#include"affichage.h"

AffichageCatalogueCategorie::AffichageCatalogueCategorie(Categorie& categorie,Cursus& cursus,Profiler* fenetre){
    QHBoxLayout* couche=new QHBoxLayout;
    QVBoxLayout* couchecode=new QVBoxLayout;
    QVBoxLayout* couchetitre=new QVBoxLayout;
    QVBoxLayout* couchenbcredits=new QVBoxLayout;
    QVBoxLayout* coucheouverture=new QVBoxLayout;
    QLabel* code= new QLabel("code",fenetre);
    QLabel* titre= new QLabel("titre",fenetre);
    QLabel* nbcredits= new QLabel("nombre de crédits",fenetre);
    QLabel* ouverture= new QLabel("semestre d'ouverture",fenetre);

    couche->addLayout(couchetitre);
    couche->addLayout(couchecode);
    couche->addLayout(couchenbcredits);
    couche->addLayout(coucheouverture);
    delete layout();
    setLayout(couche);
}
