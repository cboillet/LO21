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

    AffichageCatalogueCategorie(Categorie& cat,Cursus& curs,QWidget* parent);

};

class AffichageCatalogue:public QWidget{
Q_OBJECT
    QSqlDatabase& mydb;
     QComboBox* cursus;
     QComboBox* uv;
public:

    explicit AffichageCatalogue(QSqlDatabase &db,QWidget* parent = 0);
    // explicit AffichageCatalogue(QSqlDatabase &db,Profiler* parent = 0);
    //AffichageCatalogue(Cursus& curs,Profiler* parent){
    //    Categorie TM;
    //    AffichageCatalogueCategorie* affichage=new AffichageCatalogueCategorie(TM, curs,parent);}//(const Cursus&,Profiler&){}
private :



    QSqlTableModel *model;
};

#endif // AFFICHAGE_H
