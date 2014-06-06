#include "Profiler.h"
#include "UVEditeur.h"
#include "UTProfiler.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
Profiler::Profiler(QWidget *parent):QMainWindow(parent){
    setWindowTitle("UT-Profiler");
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
    // connections
    connect(actionChargerUV, SIGNAL(triggered()),this,SLOT(openChargerUV()));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(actionUV, SIGNAL(triggered()),this,SLOT(openUV()));
}

/*void Profiler::openChargerUV(){
    QString chemin = QFileDialog::getOpenFileName();
    try {
    if (chemin!="")UVManager::getInstance().load(chemin);
    QMessageBox::information(this, "Chargement Catalogue", "Le catalogue d’UVs
    a été chargé.");
    }catch(UTProfilerException& e){
    QMessageBox::warning(this, "Chargement Catalogue", "Erreur lors du
    chargement du fichier (non valide ?)");
    }

}*/
