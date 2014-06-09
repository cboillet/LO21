#include "CursusEditeur.h"

CursusEditeurNew::CursusEditeurNew(QWidget* parent){
    this->setWindowTitle(QString("Ajout d'une UV"));
    //Connection du slot au signal QUIT
    //QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverUV()));
    //QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
    // creation des labels
    code = new QLineEdit("code",this);
    sauver= new QPushButton("Sauver", this);
    annuler= new QPushButton("Annuler", this);
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(code);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(annuler);
    coucheH2->addWidget(sauver);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    setLayout(couche);
}
