#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include <QApplication>
#include <QMainWindow>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
    explicit AffichageCatalogue(Cursus& curs,Profiler* parent = 0);
    //AffichageCatalogue(Cursus& curs,Profiler* parent){
    //    Categorie TM;
    //    AffichageCatalogueCategorie* affichage=new AffichageCatalogueCategorie(TM, curs,parent);}//(const Cursus&,Profiler&){}

};

#endif // AFFICHAGE_H
