#include "Profiler.h"
#include "UVEditeur.h"
#include "UTProfiler.h"
#include "affichage.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QStackedWidget>
Profiler::Profiler(QWidget *parent):QMainWindow(parent){
    setWindowTitle("LO21 UTProfiler");

    QMenu* mFichier = menuBar()->addMenu("&Fichier");
    QMenu* mCharger=mFichier->addMenu("&Charger");
    QAction * actionChargerUV=mCharger->addAction("Catalogue UVs");
    QAction * actionChargerCursus=mCharger->addAction("Catalogue Cursus");
    QAction * actionChargerDossier=mCharger->addAction("Dossier");
    mFichier->addSeparator();
    QAction *actionQuitter = mFichier->addAction("&Quitter");
    QMenu* mEdition = menuBar()->addMenu("&Edition");
    QAction* actionUV=mEdition->addAction("&UV");
    QAction* actionCursus=mEdition->addAction("&Cursus");
    QAction* actionDossier=mEdition->addAction("&Dossier");

    //stratSQL->connect();
    //connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    //connect(actionUV, SIGNAL(triggered()),this,SLOT(openUV());
}

void Profiler::quit(){
    //stratSQL->disconnect();
    delete stratSQL;
}

/*
void Profiler::openUV(){
    QString code=QInputDialog::getText(this,"Entrez le code de l’UV à éditer","UV")
    ;
    if (code!="")
    try {
    UV& uv=UVManager::getInstance().getUV(code);
    UVEditeur* fenetre=new UVEditeur(uv,this);
    setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
    QMessageBox::warning(this, "Edition UV", QString("Erreur : l’UV ")+code+" n
    ’existe pas.");
    }
}
*/

void Profiler::openChargerUV(){

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
    //setLayout(couche);
/*
    QString titre=QInputDialog::getText(this,"Entrez le cursus que vous souhaitez consulter","Cursus, par défaut nous vous affichons les TSH");
    if (titre!="")
    try {
    Cursus& cursus=CursusManager::getInstance().getCursus(titre);
    AffichageCatalogue* fenetre=new AffichageCatalogue(cursus,this);//AffichageCatalogue(cursus,this);
    setCentralWidget(fenetre);
    }
    catch(UTProfilerException& e){
    QMessageBox::warning(this, "Affichage Catalogue du Cursus", QString("Erreur : le Cursus ")+titre+" n’existe pas.");
    }
    */
}

