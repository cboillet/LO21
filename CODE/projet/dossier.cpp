#include "dossier.h"


/*******ETUDIANT******/
void Etudiant::setCursus(const QString& cur){
    CursusManager& c=CursusManager::getInstance();
    cursus=&(c.getCursus(cur));
}
void Etudiant::addDossierPasse(unsigned int n,QSqlDatabase& db){
    Dossier* dossierToadd=new Dossier(1);
    dossiers.push_back(*dossierToadd);
    dossierToadd->setPasse();
}

/******ETUDIANT_MANAGER******/
//EtudiantManager::EtudiantManager(QSqslDatabase& db):mydb(db){
//}

Etudiant* EtudiantManager::trouver(QString n)const{
    for(unsigned int i=0; i<nb; i++)
        if (n==t[i]->getNom()) return t[i];
    return 0;
}

Etudiant& EtudiantManager::getEtudiant(QString n){
    Etudiant* etudiant=trouver(n);
    if (!etudiant) throw UTProfilerException("erreur, DossierManager, dossier inexistante");
    return *etudiant;
}

const Etudiant& EtudiantManager::getEtudiant(QString n)const{
    return const_cast<EtudiantManager*>(this)->getEtudiant(n);
}
void EtudiantManager::loadEquiToClass(const QString& nomEtu,unsigned int numeroDossier,unsigned int codeInsc,QSqlDatabase& db){
    EtudiantManager& etuMan=EtudiantManager::getInstance();
    UVManager& uvMan=UVManager::getInstance();
    QWidget* parent=new QWidget;
    modelEqui->setFilter("codeEqui=%codeInsc"); //code de l'inscription
    QSqlRecord recordEqui = modelEqui->record(1);
    QString titreE = recordEqui.value("titre").toString();
    QString type = recordEqui.value("type").toString();
    unsigned int CS = recordEqui.value("nCS").toInt(); //code inscription de l'equivalence de categorie CS
    if (CS!=0)
        loadInscToClass(nomEtu,numeroDossier,codeInsc,db);

    unsigned int TM = recordEqui.value("nTM").toInt();
    if (TM!=0)
        loadInscToClass(nomEtu,numeroDossier,codeInsc,db);

    unsigned int TSH = recordEqui.value("nCS").toInt();
    if (TSH!=0)
        loadInscToClass(nomEtu,numeroDossier,codeInsc,db);

    unsigned int SP = recordEqui.value("nTSH").toInt();
        loadInscToClass(nomEtu,numeroDossier,codeInsc,db);
    Etudiant& etudiantToEdit=etuMan.getEtudiant(nomEtu);
    Equival typeEqui=StringToEquival(type);
    Dossier& DossierToEdit=etudiantToEdit.dossiers[(numeroDossier-1)];
    modelInsc->setFilter("codeInscription=%codeInsc"); //recuperation du semestre et de l'année de l'équivalence
    QSqlRecord recordInsc = modelInsc->record(1);
    QString saison = recordInsc.value("saison").toString();
    unsigned int annee = recordInsc.value("annee").toInt();
    DossierToEdit.addEquivalence(titreE,typeEqui,CS,TM,TSH,SP,saison,annee,db);
}

void EtudiantManager::loadInscToClass(const QString& nomEtu,unsigned int numeroDossier,unsigned int codeInsc,QSqlDatabase& db){
    EtudiantManager& etuMan=EtudiantManager::getInstance();
    UVManager& uvMan=UVManager::getInstance();
    modelInsc->setFilter("codeInscription=%codeInsc");
    QSqlRecord recordInsc = modelInsc->record(1);
    QString codeUV = recordInsc.value("codeUV").toString();
    QString saison = recordInsc.value("saison").toString();
    unsigned int annee = recordInsc.value("annee").toInt();
    QString resultat = recordInsc.value("resultat").toString();
    UV& uvToAdd=uvMan.getUV(codeUV);
    Saison sais=StringToSaison(saison);
    Semestre* semestreToAdd=new Semestre(sais,annee);
    Note res=StringToNote(resultat);
    Etudiant& etudiantToEdit=etuMan.getEtudiant(nomEtu);
    Dossier& DossierToEdit=etudiantToEdit.dossiers[(numeroDossier-1)];
    DossierToEdit.addInscription(uvToAdd,semestreToAdd,res);

}

void EtudiantManager::load(QSqlDatabase& db){
    QWidget* parent=new QWidget;
    /**********EQUIVAL****************/
    QSqlTableModel* modelEqui=new QSqlTableModel(parent,db);
    modelEqui->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelEqui->setTable("Equivalence");
    modelEqui->select();
    /**********INSC***********/
    QSqlTableModel* modelInsc=new QSqlTableModel(parent,db);
    modelInsc->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelInsc->setTable("Inscription");
    modelInsc->select();
    /****DOSSIERS DES ETU******/
    QSqlTableModel* modelDossier=new QSqlTableModel(parent,db);
    modelDossier->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelDossier->setTable("Dossier");
    modelDossier->select();
    /**********DOSSIER INSC***********/
    QSqlTableModel* modelDoInsc=new QSqlTableModel(parent,db);
    modelDoInsc->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelDoInsc->setTable("associationDossierInscription");
    modelDoInsc->select();

    /*********ETUDIANTS**********/
    QSqlTableModel* modelEtu=new QSqlTableModel(parent,db);
    modelEtu->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelEtu->setTable("Etudiant");
    modelEtu->select();
    /************UV************/
    QSqlTableModel* modelUV=new QSqlTableModel(parent,db);
    modelUV->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelUV->setTable("UV");
    modelUV->select();
    EtudiantManager& etuMan=EtudiantManager::getInstance();
    UVManager& uvMan=UVManager::getInstance();
    QString nomEtu;
    QString prenomEtu;
    QString cursusString;
    int rCount = modelEtu->rowCount();
    for(int i = 0; i < rCount; ++i)
        {
            QSqlRecord record = modelEtu->record(i);
            nomEtu = record.value("nom").toString();
            prenomEtu = record.value("prenom").toString();
            cursusString = record.value("cursusCode").toString();
            Etudiant* etudiantToadd=new Etudiant(nomEtu,prenomEtu);
            addItem(etudiantToadd);
            etudiantToadd->setCursus(cursusString);
            modelDossier->setFilter("etudiantNom=%"+nomEtu+"%");

            /*********Parcours des dossiers de l'etu*******/
            int rowCount = modelDossier->rowCount();
            for(int i = 0; i < rowCount; ++i)
                {
                    QSqlRecord recordDossier = modelDossier->record(i);
                    nomEtu = recordDossier.value("etudiantNom").toString();
                    unsigned int codeDossier = record.value("codeDossier").toInt();
                    unsigned int numeroDossier = record.value("numero").toInt();
                    bool valide=recordDossier.value("valide").toBool();
                    bool past=recordDossier.value("past").toBool();
                    Etudiant& etudiantToEdit=etuMan.getEtudiant(nomEtu);
                    if (past)
                        etudiantToEdit.addDossierPasse(1,db);
                    else
                    {
                        //modelDossier->setFilter("etudiantNom=nomEtu");
                        //int lastDossier = modelDossier->rowCount(); //numéro du dernier dossier de l'étudiant
                        // recuperer le dernier numéro de dossier de nomEtu
                        etudiantToEdit.addDossier(numeroDossier,db);
                        if (valide)
                            {
                            Dossier& dossierAdded= etudiantToEdit.dossiers[(numeroDossier-1)];
                            dossierAdded.setValidation();//setValide le dossier
                            }
                     }
                    /********Parcours AssociationDossierInscription*********/
                    modelDoInsc->setFilter("codeDossier= %codeDossier");
                    int rowDoInsc = modelDoInsc->rowCount();
                    for(int i = 0; i < rowCount; ++i)
                    {
                        QSqlRecord recordDoInsc = modelDoInsc->record(i);
                        unsigned int codeInscription = recordDoInsc.value("codeInscription").toInt();
                        unsigned int codeEqui = recordDoInsc.value("codeEqui").toInt();
                         /*********AJOUT de L'EQUIVALENCE***********/
                        if(codeEqui!=0)
                        {
                            loadEquiToClass(nomEtu,numeroDossier,codeInscription,db);

                        }
                        /*********AJOUT de L'INSCRIPTION***********/
                        if(codeInscription!=0)
                        {
                            loadInscToClass(nomEtu,numeroDossier,codeInscription,db);
                        }

                    }

                }

    }


  }


void EtudiantManager::addEtudiant(const QString& nom, const QString& pre,const QString& cur, unsigned int s){
    Etudiant* etudiantToadd=new Etudiant(nom,pre);
    addItem(etudiantToadd);
    etudiantToadd->setCursus(cur);
    etudiantToadd->setSemestre(s);
}

/*********DOSSIER***********/


void Dossier::addEquivalence(const QString& titreE, const Equival& typeE, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, QString saison, unsigned int annee,QSqlDatabase& db){
    Saison sais=StringToSaison(saison);
    Semestre* s=new Semestre(sais,annee);
    //Semestre(Saison s, unsigned int a =0);
    Equivalence* equiToAdd=new Equivalence(titreE,typeE,CS,TM,TSH,SP,sais,annee);
    //Equivalence(const QString& nom, const Equival& equi, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, const Saison& saison, unsigned int annee)
    equivalences.push_back(*equiToAdd);
    QString sTSH="tsh";
    QString sCS="cs";
    QString sTM="tm";
    QString sSP="sp";
    UVManager& man=UVManager::getInstance();
    if (CS!=0)
    {
    QString temp=titreE+sCS;
    man.ajouterUV(temp,temp,CS,sais,Categorie::CS);
    UV& uvToAdd=man.getUV(temp);
    equiToAdd->setCS(uvToAdd,s);
    //equiToAdd->nCS=new Inscription(uvToAdd,s);
    }
    if (TM!=0)
    {
    QString temp=titreE+sTM;
    man.ajouterUV(temp,temp,TM,sais,Categorie::TM);
    UV& uvToAdd=man.getUV(temp);
    equiToAdd->setTM(uvToAdd,s);
    }
    if (TSH!=0)
    {
    QString temp=titreE+sTSH;
    man.ajouterUV(temp,temp,TSH,sais,Categorie::TSH);
    UV& uvToAdd=man.getUV(temp);
    equiToAdd->setTSH(uvToAdd,s);
    }
    if (SP!=0)
    {
    QString temp=titreE+sSP;
    man.ajouterUV(temp,temp,SP,sais, Categorie::SP);
    UV& uvToAdd=man.getUV(temp);
    equiToAdd->setSP(uvToAdd,s);
    }
}

void Dossier::addInscription(const UV& u, Semestre* s, Note res){
    Inscription* inscToAdd=new Inscription(u,s,res);
    inscriptions.push_back(*inscToAdd);
}

/*******INSCRIPTION********/




/******EQUIVALENCE*****/
Equivalence::Equivalence(const QString& nom, const Equival& equi, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, const Saison& saison, unsigned int annee):nomEquivalence(nom),equivalence(equi){
    semestre=new Semestre(saison,annee);
}

void Equivalence::setCS(const UV& uvToAdd, Semestre* s){nCS=new Inscription(uvToAdd,s);}
void Equivalence::setTM(const UV& uvToAdd, Semestre* s){nTM=new Inscription(uvToAdd,s);}
void Equivalence::setTSH(const UV& uvToAdd, Semestre* s){nTSH=new Inscription(uvToAdd,s);}
void Equivalence::setSP(const UV& uvToAdd, Semestre* s){nSP=new Inscription(uvToAdd,s);}

int EtudiantManager::addDossierdb(const QString& etudiantNom, unsigned int numero, bool valide, bool past, QSqlDatabase& db){
    QWidget* parent=new QWidget;
    QSqlTableModel* modelDossier=new QSqlTableModel(parent,db);
    modelDossier->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelDossier->setTable("Dossier");
    modelDossier->select();
    QSqlRecord recordDossier = modelDossier->record(modelDossier->rowCount());
    recordDossier.setValue("etudiantNom", etudiantNom);
    recordDossier.setValue("numero", numero);
    recordDossier.setValue("valide", valide);
    recordDossier.setValue("past", past);
    modelDossier->insertRecord(modelDossier->rowCount(), recordDossier);
    modelDossier->submitAll();
    return recordDossier.value("codeDossier").toInt();
}

int EtudiantManager::addInscEqui(const QString& nomEtu, unsigned int numeroDosser,QSqlDatabase& db,const QString& titreE, const Equival& typeE, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, QString saison, unsigned int annee){
    /******EQUIVALENCE********/
    QWidget* parent=new QWidget;
    modelEqui=new QSqlTableModel(parent,db);
    modelEqui->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelEqui->setTable("Equivalence");
    modelEqui->select();
    /**********DOSSIER INSC***********/
     modelDoInsc=new QSqlTableModel(parent,db);
    modelDoInsc->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelDoInsc->setTable("associationDossierInscription");
    modelDoInsc->select();
    /****DOSSIERS DES ETU******/
    modelDossier=new QSqlTableModel(parent,db);
    modelDossier->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelDossier->setTable("Dossier");
    modelDossier->select();
    /*****Ajoute l'équivalence****/
    int rowEqui = modelEqui->rowCount();
    QSqlRecord recordEqui = modelEqui->record(rowEqui);
    recordEqui.setValue("titre", titreE);
    recordEqui.setValue("type", EquivalToString(typeE));
    /***Ajoute les inscription****/
    if (CS!=0)
    {
        QString temp=titreE+"CS";
        //    void addUVdb(const QString& c, const QString& t, unsigned int nbc,const QString& sais, const QString& cat,QSqlDatabase &db);
        addUVdb(temp,temp,CS,saison,CategorieToString(Categorie::CS),db);
        unsigned int nCS = addInsc(temp,saison,annee,NoteToString(Note::A),db);
        recordEqui.setValue("nCS",nCS);
    }
    if (TM!=0)
    {
        QString temp=titreE+"TM";
        addUVdb(temp,temp,TM,saison,CategorieToString(Categorie::TM),db);
        unsigned int nTM = addInsc(temp,saison,annee,NoteToString(Note::A),db);
        recordEqui.setValue("nTM",nTM);
    }
    if (TSH!=0)
    {
        QString temp=titreE+"TSH";
        addUVdb(temp,temp,TSH,saison,CategorieToString(Categorie::TSH),db);
        unsigned int nTSH = addInsc(temp,saison,annee,NoteToString(Note::A),db);
        recordEqui.setValue("nTSH",nTSH);
    }
    if (SP!=0)
    {
        QString temp=titreE+"SP";
        addUVdb(temp,temp,SP,saison,CategorieToString(Categorie::SP),db);
        unsigned int nSP = addInsc(temp,saison,annee,NoteToString(Note::A),db);
        recordEqui.setValue("SP",nSP);
    }
    /*****************************/
    modelEqui->insertRecord(rowEqui, recordEqui);
    modelEqui->submitAll();
    /************Ajoute dans la classe association*************/
    modelDossier->setFilter("etudiantNom=%nomEtu");
    modelDossier->setFilter("numero=%numeroDossier");
    QSqlRecord recordDossier = modelDossier->record(1);
    unsigned int codeDossier=recordDossier.value("codeDossier").toInt(); //recuperation du code dossier
    int rowDoIn = modelDoInsc->rowCount();
    QSqlRecord recordDoInsc = modelDoInsc->record(rowDoIn);
    recordDoInsc.setValue("codeDossier", codeDossier);
    recordDoInsc.setValue("codeEqui", rowEqui);
    modelDoInsc->insertRecord(rowDoIn, recordDoInsc);
    modelDoInsc->submitAll();
    return recordEqui.value("codeEqui").toInt();
    return 0;
}

int EtudiantManager::addInsc(const QString& codeUV,const QString& saison,unsigned int annee,const QString& res,QSqlDatabase& db) {
    /**********DOSSIER INSC***********/
    QWidget* parent=new QWidget;
    modelInsc=new QSqlTableModel(parent,db);
    modelInsc->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelInsc->setTable("Inscription");
    modelInsc->select();
    QSqlRecord recordInsc=modelInsc->record(modelInsc->rowCount());
    recordInsc.setValue("codeUV",codeUV);
    recordInsc.setValue("saison",saison);
    recordInsc.setValue("annee",annee);
    recordInsc.setValue("res",res);
    modelInsc->insertRecord(modelInsc->rowCount(), recordInsc);
    modelInsc->submitAll();
    return recordInsc.value("codeInscription").toInt();

//ajouter l'inscription
}

void EtudiantManager::addUVdb(const QString& c, const QString& t, unsigned int nbc,const QString& sais, const QString& cat,QSqlDatabase &db){
    /************UV************/
    QWidget* parent=new QWidget;
    modelUV=new QSqlTableModel(parent,db);
    modelUV->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelUV->setTable("UV");
    modelUV->select();

    QSqlRecord recordUV=modelUV->record(modelUV->rowCount());
    recordUV.setValue("code",c);
    recordUV.setValue("titre",t);
    recordUV.setValue("nbCredits",nbc);
    recordUV.setValue("uvCategorie",cat);
    recordUV.setValue("saison",sais);
    modelUV->insertRecord(modelUV->rowCount(), recordUV);
    modelUV->submitAll();
}
