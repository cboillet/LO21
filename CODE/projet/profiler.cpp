#include "Profiler.h"
#include "UVEditeur.h"
#include "UTProfiler.h"
#include "affichage.h"
#include "dossier.h"
#include "CursusEditeur.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTableView>
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
    QAction * actionSetUVCursus=mCursus->addAction("Enregistrer les UV d'un cursus");
    mEdition->addSeparator();
    QAction* actionDossier=mEdition->addAction("&Dossier");
    if(!connectDb()){
       qDebug()<<"failed";
    }

    //UVManager& man=UVManager::getInstance();
    //man.load(mydb);
    CursusManager& cur=CursusManager::getInstance();
    cur.load(mydb);

   /* try {
    stratSQL->connect();
    }catch(UTProfilerException& e){
    QMessageBox::warning(this, "Connexion", QString("connexion a la base de donnée impossible"));
    }
    */
    //connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionChargerCursus, SIGNAL(triggered()),this,SLOT(openChargerCursus()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionNewUV, SIGNAL(triggered()),this,SLOT(NewUV()));
    connect(actionChangeUV, SIGNAL(triggered()),this,SLOT(ChangeUV()));
    connect(actionNewCursus, SIGNAL(triggered()),this,SLOT(NewCursus()));
    connect(actionSetUVCursus, SIGNAL(triggered()),this,SLOT(SetUVCursus()));
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
    QString code=QInputDialog::getText(this,"Entrez le code de l’UV à éditer","UV")
    ;
    if (code!="")
    try {
    UV& uv=UVManager::getInstance().getUV(code);
    //UVEditeur* fenetre=new UVEditeur(uv,this);
    //setCentralWidget(fenetre);
    }catch(UTProfilerException& e){
    QMessageBox::warning(this, "Edition UV", QString("Erreur : l’UV ")+code+" n’existe pas.");
    }

}

void Profiler::NewCursus(){
    //addcursus = new CursusEditeurNew( centralWidget );
    CursusEditeurNew* fenetre=new CursusEditeurNew(mydb,this);
    this->setCentralWidget(fenetre);
}

void Profiler::SetUVCursus(){
   /* QString code=QInputDialog::getText(this,"Entrez le code du Cursus auquel vous souhaitez enregistrer les UV","Cursus")
    ;
    if (code!="")
    try {
    CursusManager& cursusman =CursusManager::getInstance();
    Cursus& cursus=cursusman.getCursus(code);
    //CursusEditeurAddUV* fenetre=new CursusEditeurAddUV(cursus,mydb,this);
    //setCentralWidget(fenetre);
    }
    catch(UTProfilerException& e){
    QMessageBox::warning(this, "Edition Cursus", QString("Erreur : le Cursus ")+code+" n’existe pas.");
    }
    */
    CursusEditeurAddUV* fenetre=new CursusEditeurAddUV(mydb,this);
    setCentralWidget(fenetre);
}

void Profiler::openChargerUV(){
   AffichageCatalogue* affichage=new AffichageCatalogue(mydb,this);
   setCentralWidget(affichage);
}



void Profiler::openChargerCursus(){


    QSqlQueryModel *model = new QSqlQueryModel;
         model->setQuery("SELECT code, titre, duree,equivalence, codeUV, nbCS, nbTM, nbTSH, nbSP  FROM Cursus");
         model->setHeaderData(0, Qt::Horizontal, tr("Code"));
         model->setHeaderData(1, Qt::Horizontal, tr("Titre"));
         model->setHeaderData(2, Qt::Horizontal, tr("Duree en semestre"));
         model->setHeaderData(3, Qt::Horizontal, tr("Equivalence"));
         model->setHeaderData(4, Qt::Horizontal, tr("Credits CS"));
         model->setHeaderData(5, Qt::Horizontal, tr("Credits TM"));
         model->setHeaderData(6, Qt::Horizontal, tr("Credits TSH"));
         model->setHeaderData(7, Qt::Horizontal, tr("Credits SP"));


         QTableView *view = new QTableView;
         view->setModel(model);
         view->setWindowTitle("Catalogues Cursus");
         view->show();


}

