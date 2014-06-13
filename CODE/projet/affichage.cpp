#include"affichage.h"

AffichageCatalogue::AffichageCatalogue(QSqlDatabase &db,QWidget* parent):mydb(db)
{
   /* QHBoxLayout* couche=new QHBoxLayout;
    QVBoxLayout* couchecode=new QVBoxLayout;
    QVBoxLayout* couchetitre=new QVBoxLayout;
    QVBoxLayout* couchenbcredits=new QVBoxLayout;
    QVBoxLayout* coucheouverture=new QVBoxLayout;
    QVBoxLayout* coucheannee=new QVBoxLayout;

    QLabel* code= new QLabel("code",this);
    QLabel* titre= new QLabel("titre",this);
    QLabel* nbcredits= new QLabel("nombre de crédits",this);
    QLabel* ouverture= new QLabel("semestre d'ouverture",this);
    QLabel* annee=new QLabel ("annee", this);

    couche->addLayout(couchetitre);
    couche->addLayout(couchecode);
    couche->addLayout(couchenbcredits);
    couche->addLayout(coucheouverture);
    couche->addLayout(coucheannee);
    //delete layout();
    //setLayout(couche);*/

    model = new QSqlTableModel(parent,mydb);
    model->setTable("UV");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->removeColumn(0); // don't show the ID
    model->setSort(model->fieldIndex("uvCategorie"),Qt::AscendingOrder);
    model->setHeaderData(0, Qt::Horizontal, tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, tr("Titre"));
    model->setHeaderData(2, Qt::Horizontal, tr("Categorie"));
    model->setHeaderData(3, Qt::Horizontal, tr("Credits"));
    model->setHeaderData(4, Qt::Horizontal, tr("Saison"));

    QTableView *view = new QTableView;
    view->setModel(model);
    view->setWindowTitle("Catalogue UVs");
    view->width();
    //view->setMaximumHeight(50000);
    view->show();
}

AffichageCatalogueCategorie::AffichageCatalogueCategorie(Categorie& categorie,Cursus& cursus,QWidget* parent):QWidget(parent){
    QHBoxLayout* couche=new QHBoxLayout;
    QVBoxLayout* couchecode=new QVBoxLayout;
    QVBoxLayout* couchetitre=new QVBoxLayout;
    QVBoxLayout* couchenbcredits=new QVBoxLayout;
    QVBoxLayout* coucheouverture=new QVBoxLayout;
    QVBoxLayout* coucheannee=new QVBoxLayout;
    QLabel* code= new QLabel("code",this);
    QLabel* titre= new QLabel("titre",this);
    QLabel* nbcredits= new QLabel("nombre de crédits",this);
    QLabel* ouverture= new QLabel("semestre d'ouverture",this);
    QLabel* annee=new QLabel ("annee",this);

    couche->addLayout(couchetitre);
    couche->addLayout(couchecode);
    couche->addLayout(couchenbcredits);
    couche->addLayout(coucheouverture);
    couche->addLayout(coucheannee);
    delete layout();
    setLayout(couche);
}
