#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>
#include "UVEditeur.h"
#include "UTProfiler.h"
#include "profiler.h"

class AffichageCatalogueCategorie:public QWidget{
Q_OBJECT
public:
    AffichageCatalogueCategorie(Categorie& cat,Cursus& curs,Profiler* fenetre);
};

class AffichageCatalogue:public QWidget{
Q_OBJECT
public:
    AffichageCatalogue(Cursus& curs,Profiler* fenetre){
        Categorie TM;
        AffichageCatalogueCategorie* affichage=new AffichageCatalogueCategorie(TM, curs,fenetre);}//(const Cursus&,Profiler&){}

};

#endif // AFFICHAGE_H
