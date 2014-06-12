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
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);

    //Connection du slot au signal QUIT
   connect(sauver,  &QPushButton::clicked,[this]{sauverCursus(mydb);});
  // connect(UVObligatoire,  &QPushButton::clicked,[this]{setUVObligatoire(mydb);});
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
    cursus.addCursus(c,t,d,Ccs,Ctm,Ctsh,Csp,db);
    QMessageBox::information(this, "Sauvegarde", "Cursus sauvegardée...");
}

CursusEditeurAddUV::CursusEditeurAddUV(QSqlDatabase &db, QWidget *parent):mydb(db){
    this->setWindowTitle(QString("Lier une UV à un cursus"));
    model=new QSqlTableModel(parent,mydb);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("Cursus");
    model->select();
    model->setSort(model->fieldIndex("code"),Qt::AscendingOrder);

    /*QTableView *view = new QTableView;
    view->setModel(model);
    view->hideColumn(1);view->hideColumn(2);view->hideColumn(3);view->hideColumn(5);view->hideColumn(6);view->hideColumn(7);view->hideColumn(8);
    */

    QLabel* cursusLabel = new QLabel("code:",this);
    cursus=new QComboBox(this);
    cursus->setModel(model);
    cursus->setModelColumn(model->fieldIndex("code"));
    cursus->setCurrentIndex(0);
    QLabel* uvLabel = new QLabel("titre:",this);
    uv=new QComboBox(this);
    model2=new QSqlTableModel(parent,mydb);
    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model2->setTable("UV");
    model2->select();
    model2->setSort(model2->fieldIndex("code"),Qt::AscendingOrder);
    uv->setModel(model2);
    uv->setModelColumn(model2->fieldIndex("code"));
    uv->setCurrentIndex(0);
    modelUvToCursus=new QSqlTableModel(parent,mydb);
    modelUvToCursus->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelUvToCursus->setTable("UVObligatoire");
    modelUvToCursus->select();
    QTableView *view = new QTableView;
        view->setModel(modelUvToCursus);
    QPushButton* sauver=new QPushButton("sauver",this);
    QVBoxLayout* couche = new QVBoxLayout;
    QHBoxLayout* coucheH1 = new QHBoxLayout;
    QHBoxLayout* coucheH2 = new QHBoxLayout;
    QHBoxLayout* coucheH3 = new QHBoxLayout;
    coucheH1->addWidget(cursusLabel);
    coucheH1->addWidget(cursus);
    coucheH1->addWidget(uvLabel);
    coucheH1->addWidget(uv);
    coucheH2->addWidget(sauver);
    coucheH3->addWidget(view);
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    setLayout(couche);
    connect(sauver,  &QPushButton::clicked,[this]{sauverCursus(mydb);});
}

void CursusEditeurAddUV::sauverCursus(QSqlDatabase &db){
    int codeCursus=cursus->currentIndex();
    int codeUV=uv->currentIndex();
    int rowCount = modelUvToCursus->rowCount();
    //QString uvCode = model->data(codeCursus,0);
    QSqlRecord recordCursus = model->record(codeCursus);
    QString cursusCode= recordCursus.value("code").toString();
    QSqlRecord recordUV = model2->record(codeUV);
    QString uvCode = recordUV.value("code").toString();
    QSqlRecord recordUvToCursus = modelUvToCursus->record(rowCount);
    recordUvToCursus.setValue("cursus", cursusCode);
    recordUvToCursus.setValue("uv", uvCode);
     //model->insertRecord(codeCursus, record);
    modelUvToCursus->insertRecord(rowCount, recordUvToCursus);
    modelUvToCursus->submitAll();
    QMessageBox::information(this, "Sauvegarde", "Cursus sauvegardée...");
}
