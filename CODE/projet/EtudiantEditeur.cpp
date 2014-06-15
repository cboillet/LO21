#include "EtudiantEditeur.h"
#include <QMessageBox>


EtudiantEditeur::EtudiantEditeur(QSqlDatabase &db,QMainWindow *parent):mydb(db),fenetre(parent){
    this->setWindowTitle(QString("Ajout d'un Etudiant"));

    nomLabel = new QLabel("Nom de l'étudiant",this);
    prenomLabel = new QLabel("Prénom de l'étudiant",this);
    cursusLabel = new QLabel("chiox du cursus que suit l'étudiant",this);
    semestreLabel= new QLabel("Numéro de votre semestre actuel",this);
    // creation des labels
    nom = new QLineEdit;
    prenom = new QLineEdit;
    cursus=new QComboBox(this);
    semestre= new QSpinBox(this);
    semestre->setRange(1,8);
    modelCursus=new QSqlTableModel(parent,mydb);
    modelCursus->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelCursus->setTable("Cursus");
    modelCursus->select();
    modelCursus->setSort(modelCursus->fieldIndex("code"),Qt::AscendingOrder);
    modelEtu=new QSqlTableModel(this,mydb);
    modelEtu->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelEtu->setTable("Etudiant");
    modelEtu->select();

    cursus->setModel(modelCursus);
    cursus->setModelColumn(modelCursus->fieldIndex("code"));
    cursus->setCurrentIndex(0);
    sauver= new QPushButton("Sauver", this);
    annuler= new QPushButton("Annuler", this);
    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(nomLabel);
    coucheH1->addWidget(nom);
    coucheH1->addWidget(prenomLabel);
    coucheH1->addWidget(prenom);
    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(cursusLabel);
    coucheH2->addWidget(cursus);
    coucheH2->addWidget(semestre);
    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(annuler);
    coucheH3->addWidget(sauver);
    couche = new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    setLayout(couche);

    //Connection du slot au signal QUIT
   connect(sauver,  &QPushButton::clicked,[this]{sauverEtudiant(mydb);});
  // connect(UVObligatoire,  &QPushButton::clicked,[this]{setUVObligatoire(mydb);});
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}

void EtudiantEditeur::sauverEtudiant(QSqlDatabase& db){
    QString nomEtu=nom->text();
    QString prenomEtu=prenom->text();
    unsigned int s=semestre->value();
    int codeCursus=cursus->currentIndex(); //ligne du code du Cursus
    int rowCount = modelEtu->rowCount(); //ligne ou inserer l'étudiant
    QSqlRecord recordCursus = modelCursus->record(codeCursus);
    QSqlRecord recordEtudiant = modelEtu->record(rowCount);
    QString cursusCode= recordCursus.value("code").toString();
    recordEtudiant.setValue("nom", nomEtu);
    recordEtudiant.setValue("prenom", prenomEtu);
    recordEtudiant.setValue("cursusCode", cursusCode);
    recordEtudiant.setValue("semestre", s);
    modelEtu->insertRecord(rowCount, recordEtudiant);
    modelEtu->submitAll();
    EtudiantManager& etuman=EtudiantManager::getInstance();
    etuman.addEtudiant(nomEtu,prenomEtu,cursusCode,s);
    Etudiant& etu=etuman.getEtudiant(nomEtu);
    QMessageBox::information(this, "Sauvegarde", "Etudiant sauvegardée...");
    EtudiantEditeurFormationPasse* fenetre2=new EtudiantEditeurFormationPasse(etu,mydb,this);
    fenetre->setCentralWidget(fenetre2);
}

EtudiantEditeurFormationPasse::EtudiantEditeurFormationPasse(Etudiant& etu, QSqlDatabase& db, QWidget* parent):etudiant(etu),mydb(db){
    /******Declaration Model******/
    modelEtu=new QSqlTableModel(this,mydb);
    modelEtu->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelEtu->setTable("Etudiant");
    modelEtu->select();
    modelUV=new QSqlTableModel(this,mydb);
    modelUV->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelUV->setTable("UV");
    modelUV->select();
    modelEquival=new QSqlTableModel(this,mydb);
    modelEquival->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelEquival->setTable("Equivalence");
    modelEquival->select();
    modelDossier=new QSqlTableModel(this,mydb);
    modelDossier->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelDossier->setTable("Dossier");
    modelDossier->select();
    modelInscription=new QSqlTableModel(this,mydb);
    modelInscription->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelInscription->setTable("Inscription");
    modelInscription->select();
    modelDossierInsc=new QSqlTableModel(this,mydb);
    modelDossierInsc->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelDossierInsc->setTable("associationDossierInscription");
    modelDossierInsc->select();

    /******Declaration Widget******/
    uvObetnueLabel=new QLabel("Selectionnez les UVs que vous avez déjà obtenues",this);
    equivalenceLabel=new QLabel("Enregistrez si vous avez une équivalence",this);
    nomELabel=new QLabel("Nom de votre equivalence (TN09, Erasmus au Brésil, Césure sur la lune...)",this);
    typeELabel=new QLabel("Type",this);
    CSLabel=new QLabel("Nombre de crédits CS obtenus",this);
    TMLabel=new QLabel("Nombre de crédits TM obtenus",this);
    TSHLabel=new QLabel("Nombre de crédits TSH obtenus",this);
    SPLabel=new QLabel("Nombre de crédits SP obtenus",this);
    uvObtenue=new QListView;

    uvObtenue->setSelectionMode( QAbstractItemView::ExtendedSelection );
    modelUV->setSort(modelUV->fieldIndex("code"),Qt::AscendingOrder);
    uvObtenue->setModel(modelUV);
    uvObtenue->setModelColumn(modelUV->fieldIndex("code"));

    nomE=new QLineEdit;
    typeE=new QComboBox;
    for(Equival equi = Equival::FormationPrecedente; equi!= Equival::END; equi = static_cast<Equival>(static_cast<int>(equi) + 1))
       typeE->addItem(EquivalToString(equi));
    typeE->setCurrentIndex(0);
    CS=new QSpinBox;
    CS->setRange(0,20);
    TM=new QSpinBox;
    TM->setRange(0,20);
    TSH=new QSpinBox;
    TSH->setRange(0,20);
    SP=new QSpinBox;
    SP->setRange(0,20);
    sauver=new QPushButton("sauver",this);
    annuler=new QPushButton("annuler",this);

    /********Declaration Layout*****/
    couche= new QVBoxLayout;
    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(uvObetnueLabel);
    coucheH1->addWidget(uvObtenue);
    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(equivalenceLabel);
    coucheH2->addWidget(nomELabel);
    coucheH2->addWidget(nomE);
    coucheH2->addWidget(typeELabel);
    coucheH2->addWidget(typeE);
    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(CSLabel);
    coucheH3->addWidget(CS);
    coucheH3->addWidget(TMLabel);
    coucheH3->addWidget(TM);
    coucheH3->addWidget(TSHLabel);
    coucheH3->addWidget(TSH);
    coucheH3->addWidget(SPLabel);
    coucheH3->addWidget(SP);
    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    setLayout(couche);

    connect(sauver,  &QPushButton::clicked,[this]{sauverEtudiant(mydb);});
   // connect(UVObligatoire,  &QPushButton::clicked,[this]{setUVObligatoire(mydb);});
     QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}


void EtudiantEditeurFormationPasse::sauverEtudiant(QSqlDatabase& db){
    /**********AJOUT DE L'EQUIVALENCE************/
    EtudiantManager& etuman=EtudiantManager::getInstance();
    QString nomEqui=nomE->text();
    Equival typeEqui=Equival(typeE->currentIndex());
    unsigned int nCS=CS->value();
    unsigned int nTM=TM->value();
    unsigned int nTSH=TSH->value();
    unsigned int nSP=SP->value();
    unsigned int annee=2000;
    QString tem="Automne";
    unsigned int dossier=etuman.addDossierdb(etudiant.getNom(),1,false,true,mydb);
    unsigned int equi=etuman.addInscEqui(etudiant.getNom(),1,db,nomEqui,typeEqui,nCS,nTM,nTSH,nSP,tem,0);
    //(const QString& nomEtu,QSqlDatabase& db,const QString& titreE, const Equival& typeE, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, QString saison, unsigned int annee)
    etudiant.addDossierPasse(1,db); //ajouter le l'equivalence au dossier
    Dossier& DossierToEdit=etudiant.dossiers[0];
    DossierToEdit.addEquivalence(nomEqui,typeEqui,nCS,nTM,nTSH,nSP,tem,annee,mydb);
    /*************INSCRIPTION***************/
}
