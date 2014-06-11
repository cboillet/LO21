#include "CursusEditeur.h"
#include <QMessageBox>

CursusEditeurNew::CursusEditeurNew(QSqlDatabase &db,QWidget *parent):mydb(db){
    this->setWindowTitle(QString("Ajout d'une UV"));
    codeLabel = new QLabel("code",this);
    titreLabel = new QLabel("titre",this);
    dureeLabel = new QLabel("durée en semestres",this);
    // creation des labels
    code = new QLineEdit;
    titre = new QTextEdit;
    duree=new QSpinBox(this);
    duree->setRange(1,8);
    creditsLabel= new QLabel("nombre de crédits à valider:",this);
    CSLabel= new QLabel("CS:",this);
    CS = new QSpinBox(this);
    TMLabel= new QLabel("TM:",this);
    TM = new QSpinBox(this);
    TSHLabel= new QLabel("TSH:",this);
    TSH = new QSpinBox(this);
    SPLabel= new QLabel("SP:",this);
    SP = new QSpinBox(this);
    CS->setRange(0,60);
    TM->setRange(0,60);
    TSH->setRange(0,60);
    SP->setRange(0,60);
    sauver= new QPushButton("Sauver", this);
    annuler= new QPushButton("Annuler", this);
    UVObligatoire= new QPushButton("Enregistrer les UV obligatoires", this);
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(dureeLabel);
    coucheH1->addWidget(duree);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(creditsLabel);
    coucheH3->addWidget(CSLabel);
    coucheH3->addWidget(CS);
    coucheH3->addWidget(TMLabel);
    coucheH3->addWidget(TM);
    coucheH3->addWidget(TSHLabel);
    coucheH3->addWidget(TSH);
    coucheH3->addWidget(SPLabel);
    coucheH3->addWidget(SP);
    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);
    coucheH4->addWidget(UVObligatoire);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);

    //Connection du slot au signal QUIT
   connect(sauver,  &QPushButton::clicked,[this]{sauverCursus(mydb);});
   connect(UVObligatoire,  &QPushButton::clicked,[this]{setUVObligatoire(mydb);});
   // QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverUV(QSqlDatabase&)));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}

void CursusEditeurNew::sauverCursus(QSqlDatabase& db){
    QString c=code->text();
    QString t=titre->toPlainText();
    unsigned int d=duree->value();
    unsigned int Ccs=CS->value();
    unsigned int Ctm=TM->value();
    unsigned int Ctsh=TSH->value();
    unsigned int Csp=SP->value();
    CursusManager& cursus=CursusManager::getInstance();
    cursus.ajouter(c,t,d,Ccs,Ctm,Ctsh,Csp,db);
    QMessageBox::information(this, "Sauvegarde", "Cursus sauvegardée...");
}
