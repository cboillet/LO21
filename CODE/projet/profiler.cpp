#include "Profiler.h"
#include "UVEditeur.h"
#include "UTProfiler.h"
#include "affichage.h"
#include "CursusEditeur.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QStackedWidget>
Profiler::Profiler(QWidget *parent):QMainWindow(parent){
    setWindowTitle("LO21 UTProfiler");
    centralWidget = new QWidget(this);
    this->setCentralWidget( centralWidget );
    QMenu* mFichier = menuBar()->addMenu("&Fichier");
    QMenu* mCharger=mFichier->addMenu("&Charger");
    QAction * actionChargerUV=mCharger->addAction("Catalogue UVs");
    QAction * actionChargerCursus=mCharger->addAction("Catalogue Cursus");
    QAction * actionChargerDossier=mCharger->addAction("Dossier");
    mFichier->addSeparator();
    QAction *actionQuitter = mFichier->addAction("&Quitter");
    QMenu* mEdition = menuBar()->addMenu("&Edition");
    QMenu* mUV=mEdition->addMenu("&UV");
    QAction * actionNewUV=mUV->addAction("Créer");
    QAction * actionChangeUV=mUV->addAction("Apporter des modifications");
    QMenu* mCursus=mEdition->addMenu("&Cursus");
    QAction * actionNewCursus=mCursus->addAction("Créer");
    QAction * actionChangeCursus=mCursus->addAction("Apporter des modifications");
    mEdition->addSeparator();
    QAction* actionDossier=mEdition->addAction("&Dossier");
    if(!connectDb()){
       qDebug()<<"failed";
    }
   /* try {
    stratSQL->connect();
    }catch(UTProfilerException& e){
    QMessageBox::warning(this, "Connexion", QString("connexion a la base de donnée impossible"));
    }
    */
    //connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionNewUV, SIGNAL(triggered()),this,SLOT(NewUV()));
    connect(actionChangeUV, SIGNAL(triggered()),this,SLOT(ChangeUV()));
    connect(actionNewCursus, SIGNAL(triggered()),this,SLOT(NewCursus()));
    connect(actionChangeCursus, SIGNAL(triggered()),this,SLOT(ChangeCursus()));
}

void Profiler::quit(){
    //deconnect();
    //stratSQL->disconnect();
    //delete stratSQL;
}


void Profiler::NewUV(){
    UVEditeurNew* fenetre=new UVEditeurNew(mydb,this);
    this->setCentralWidget(fenetre);
}

void Profiler::ChangeUV(){
}

void Profiler::NewCursus(){
    //addcursus = new CursusEditeurNew( centralWidget );
    CursusEditeurNew* cursus=new CursusEditeurNew(centralWidget);
    this->setCentralWidget(cursus);
}

void Profiler::ChangeCursus(){
}

void Profiler::openChargerUV(){
}

