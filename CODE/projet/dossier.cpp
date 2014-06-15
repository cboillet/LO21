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

void EtudiantManager::load(QSqlDatabase& db){
    EtudiantManager& etuMan=EtudiantManager::getInstance();
    UVManager& uvMan=UVManager::getInstance();
    QString nomEtu;
    QString prenomEtu;
    QString cursusString;
    QWidget* parent=new QWidget;

    /**********EQUIVAL****************/
    QSqlTableModel* modelEqui=new QSqlTableModel(parent,db);
    modelEqui->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelEqui->setTable("Equivalence");
    modelEqui->select();
    /*int rowEqui = modelEqui->rowCount();
    for(int i = 0; i < rowEqui; ++i)
        {
            QSqlRecord record = modelEqui->record(i);
            QString titreE = record.value("titre").toString();
            QString type = record.value("type").toString();
            unsigned int CS = record.value("nCS").toInt();
            unsigned int TM = record.value("nTM").toInt();
            unsigned int TSH = record.value("nCS").toInt();
            unsigned int SP = record.value("nTSH").toInt();
            Equival typeEqui=StringToEquival(type);
            //etudiantToEdit.dossiers[(numeroDossier-1)];
        }
    */
    /**********INSC***********/
    QSqlTableModel* modelInsc=new QSqlTableModel(parent,db);
    modelInsc->setEditStrategy(QSqlTableModel::OnManualSubmit);
    modelInsc->setTable("Inscription");
    modelInsc->select();
    /*int rowInsc = modelInsc->rowCount();
    for(int i = 0; i < rowInsc; ++i)
        {
            QSqlRecord record = modelInsc->record(i);
            QString codeUV = record.value("codeUV").toString();
            QString saison = record.value("saison").toString();
            unsigned int annee = record.value("annee").toInt();
            QString resultat = record.value("resultat").toString();
            UV& uvToAdd=uvMan.getUV(codeUV);
            Saison sais=StringToSaison(saison);
            Semestre* semestreToAdd=new Semestre(sais,annee);
            Note res=StringToNote(resultat);
            //etudiantToEdit.dossiers[(numeroDossier-1)];
            //Dossier::addInscription(const UV& u, Semestre& s, Note res=Note::EC)
        }
        */
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
                        if(codeEqui!=0)
                        {
                            modelEqui->setFilter("codeEqui=%codeEqui");
                            QSqlRecord recordEqui = modelEqui->record(1);
                            QString titreE = record.value("titre").toString();
                            QString type = recordEqui.value("type").toString();
                            unsigned int CS = recordEqui.value("nCS").toInt();
                            unsigned int TM = recordEqui.value("nTM").toInt();
                            unsigned int TSH = recordEqui.value("nCS").toInt();
                            unsigned int SP = recordEqui.value("nTSH").toInt();
                            Equival typeEqui=StringToEquival(type);
                            Dossier& DossierToEdit=etudiantToEdit.dossiers[(numeroDossier-1)];
                            DossierToEdit.addEquivalence(titreE,typeEqui,CS,TM,TSH,SP);

                        }
                        if(codeInscription!=0)
                        {
                            modelInsc->setFilter("codeInscription=%codeInscription");
                            QSqlRecord recordInsc = modelInsc->record(1);
                            QString codeUV = recordInsc.value("codeUV").toString();
                            QString saison = recordInsc.value("saison").toString();
                            unsigned int annee = recordInsc.value("annee").toInt();
                            QString resultat = recordInsc.value("resultat").toString();
                            UV& uvToAdd=uvMan.getUV(codeUV);
                            Saison sais=StringToSaison(saison);
                            Semestre* semestreToAdd=new Semestre(sais,annee);
                            Note res=StringToNote(resultat);
                            Dossier& DossierToEdit=etudiantToEdit.dossiers[(numeroDossier-1)];
                            DossierToEdit.addInscription(uvToAdd,*semestreToAdd,res);
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


void Dossier::addEquivalence(const QString& titreE, const Equival& typeE, unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP){
    Equivalence* equiToAdd=new Equivalence(titreE,typeE,CS,TM,TSH,SP);
    equivalences.push_back(*equiToAdd);
}

void Dossier::addInscription(const UV& u, Semestre& s, Note res){
    Inscription* inscToAdd=new Inscription(u,s,res);
    inscriptions.push_back(*inscToAdd);
}

/*******INSCRIPTION********/

/*******EQUIVALENCE*******/
void Equivalence::Equivalence(const QString& nom,const Equival& equi,unsigned int CS, unsigned int TM, unsigned int TSH, unsigned int SP, Semestre& s, QSqlDatabase& db);:nomEquivalence(nom), equivalence(equi,semestre(s){
    Saison sais=SaisonToString(s.getSaison());                                                                                                                                                                                             QString TSH="tsh";
    QString CS="cs";
    QString TM="tm";
    QString SP="sp";

    if (CS!=0)
    {
    UVManager& man=UVManager::getInstance();
    man.addUV(c,t,nbc,cat,sais,db);
    }
    if (TM!=0)
    {



    }

}
