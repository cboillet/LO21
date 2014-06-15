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
    CS->setRange(1,20);
    TM=new QSpinBox;
    TM->setRange(1,20);
    TSH=new QSpinBox;
    TSH->setRange(1,20);
    SP=new QSpinBox;
    SP->setRange(1,20);
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
    int rowAsso = modelDossierInsc->rowCount();
    QSqlRecord recordDossierInsc = modelDossierInsc->record(rowAsso);

    /******AJOUT DU DOSSIER*****/
    int rowCount = modelDossier->rowCount();
    QSqlRecord recordDossier = modelDossier->record(rowCount);
    recordDossier.setValue("etudiantNom", etudiant.geNom());
    recordDossier.setValue("numero", 1);
    recordDossier.setValue("past", 1);
    recordDossier.setValue("valide", 0);
    modelDossier->insertRecord(rowCount, recordDossier);
    modelDossier->submitAll();
    EtudiantManager& etuman=EtudiantManager::getInstance();
    Etudiant& etudiantToEdit=etuman.getEtudiant(etudiant.getNom());
    etudiantToEdit.addDossierPasse(1,db);

    // Dossier& dossierToEdit=etudiantToEdit.dossiers[(1)];

    /**********AJOUT DE L'EQUIVALENCE************/
    QString nomEqui=nomE->text();
    Equival typeEqui=Equival(typeE->currentIndex());
    unsigned int nCS=CS->value();
    unsigned int nTM=TM->value();
    unsigned int nTSH=TSH->value();
    unsigned int nSP=SP->value();
    int rowEqui = modelEquival->rowCount();
    QSqlRecord recordEquival = modelEquival->record(rowEqui);
    recordEquival.setValue("titre", nomEqui);
    recordEquival.setValue("type", EquivalToString(typeEqui));
    recordEquival.setValue("nCS", nCS);
    recordEquival.setValue("nTM", nTM);
    recordEquival.setValue("nTSH", nTSH);
    recordEquival.setValue("nSP", nSP);
    modelEquival->insertRecord(rowEqui, recordEquival);
    modelEquival->submitAll();

    /*************AJOUT DES INSCRIPTIONS*************/
    //etudiant.addDossierPasse(1,db); ajouter le l'equivalence au dossier

    /*************INSCRIPTION***************/
}
