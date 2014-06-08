#include"affichage.h"

AffichageCatalogue::AffichageCatalogue(Cursus& curs,Profiler* parent){
    QHBoxLayout* couche=new QHBoxLayout;
    QVBoxLayout* couchecode=new QVBoxLayout;
    QVBoxLayout* couchetitre=new QVBoxLayout;
    QVBoxLayout* couchenbcredits=new QVBoxLayout;
    QVBoxLayout* coucheouverture=new QVBoxLayout;
    QLabel* code= new QLabel("code",this);
    QLabel* titre= new QLabel("titre",this);
    QLabel* nbcredits= new QLabel("nombre de crédits",this);
    QLabel* ouverture= new QLabel("semestre d'ouverture",this);

    couche->addLayout(couchetitre);
    couche->addLayout(couchecode);
    couche->addLayout(couchenbcredits);
    couche->addLayout(coucheouverture);
    //delete layout();
    //setLayout(couche);
}

AffichageCatalogueCategorie::AffichageCatalogueCategorie(Categorie& categorie,Cursus& cursus,Profiler* parent):QWidget(parent){
    QHBoxLayout* couche=new QHBoxLayout;
    QVBoxLayout* couchecode=new QVBoxLayout;
    QVBoxLayout* couchetitre=new QVBoxLayout;
    QVBoxLayout* couchenbcredits=new QVBoxLayout;
    QVBoxLayout* coucheouverture=new QVBoxLayout;
    QLabel* code= new QLabel("code",this);
    QLabel* titre= new QLabel("titre",this);
    QLabel* nbcredits= new QLabel("nombre de crédits",this);
    QLabel* ouverture= new QLabel("semestre d'ouverture",this);

    couche->addLayout(couchetitre);
    couche->addLayout(couchecode);
    couche->addLayout(couchenbcredits);
    couche->addLayout(coucheouverture);
    delete layout();
    setLayout(couche);
}
