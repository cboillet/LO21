#include "UTProfiler.h"
#include "manager.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtGui>
#include <QMessageBox>

const int MAXCREDIT=6;

QTextStream& operator<<(QTextStream& f, const UV& uv){
	return f<<uv.getCode()<<", "<<uv.getCategorie()<<", "<<uv.getNbCredits()<<" credits, "<<uv.getTitre();
}

QTextStream& operator>>(QTextStream& f, Categorie& cat){
    QString str;
    f>>str;
    if (str=="CS") cat=Categorie::CS;
    else
    if (str=="TM") cat=Categorie::TM;
    else
    if (str=="SP") cat=Categorie::SP;
    else
    if (str=="TSH") cat=Categorie::TSH;
    else {
        throw UTProfilerException("erreur, lecture categorie");
    }
    return f;
}

Categorie StringToCategorie(const QString& str){
    if (str=="CS") return Categorie::CS;
    else
    if (str=="TM") return Categorie::TM;
    else
    if (str=="SP") return Categorie::SP;
    else
    if (str=="TSH") return Categorie::TSH;
    else {
        throw UTProfilerException(QString("erreur, StringToCategorie, categorie ")+str+" inexistante");
    }
}
QString CategorieToString(Categorie c){
    switch(c){
    case Categorie::CS: return "CS";
    case Categorie::TM: return "TM";
    case Categorie::SP: return "SP";
    case Categorie::TSH: return "TSH";
    default: throw UTProfilerException("erreur, categorie non traitee");
    }
}

Equival StringToEquival(const QString& e){
    if (e=="FormationPrecedente") return Equival::FormationPrecedente;
    else
    if (e=="SejourEtranger") return Equival::SejourEtranger;
    else
    if (e=="Stage") return Equival::Stage;
    else {
        throw UTProfilerException(QString("erreur, EquivalToCategorie, equival ")+e+" inexistante");
    }
}
QString EquivalToString(Equival e){
    switch(e){
    case Equival::FormationPrecedente: return "FormationPrecedente";
    case Equival::SejourEtranger: return "SejourEtranger";
    case Equival::Stage: return "Stage";
    default: throw UTProfilerException("erreur, type d'�quivalence non traitee");
    }
}

Note StringToNote(const QString& e){
    if (e=="A") return Note::A;
    else
    if (e=="B") return Note::B;
    else
    if (e=="C") return Note::C;
    else
    if (e=="D") return Note::D;
    else
    if (e=="E") return Note::E;
    else
    if (e=="F") return Note::F;
    else
    if (e=="FX") return Note::FX;
    else
    if (e=="RES") return Note::RES;
    else
    if (e=="EC") return Note::EC;
    else {
        throw UTProfilerException(QString("erreur, NoteToCategorie, note ")+e+" inexistante");
    }
}
QString NoteToString(Note e){
    switch(e){
    case Note::A: return "A";
    case Note::B: return "B";
    case Note::C: return "C";
    case Note::D: return "D";
    case Note::E: return "E";
    case Note::F: return "F";
    case Note::FX: return "FX";
    case Note::RES: return "RES";
    case Note::EC: return "EC";
    default: throw UTProfilerException("erreur, type de Note non traitee");
    }
}

QTextStream& operator<<(QTextStream& f, const Categorie& cat){
    switch(cat){
    case Categorie::CS: f<<"CS"; break;
    case Categorie::TM: f<<"TM"; break;
    case Categorie::SP: f<<"SP"; break;
    case Categorie::TSH: f<<"TSH"; break;
    default: throw UTProfilerException("erreur, categorie non traitee");
    }
    return f;
}
Saison StringToSaison(const QString& str){
    if (str=="Automne") return Saison::Automne;
    else
    if (str=="Printemps") return Saison::Printemps;
    else {
        throw UTProfilerException(QString("erreur, StringToSaison, saison")+str+" inexistante");
    }
}
QString SaisonToString(Saison sais){
    switch(sais){
    case Saison::Automne: return "Automne";
    case Saison::Printemps: return "Printemps";
    default: throw UTProfilerException("erreur, saison non traitee");
    }
}
QTextStream& operator>>(QTextStream& f, Saison& sais){
    QString str;
    f>>str;
    if (str=="Automne") sais=Saison::Automne;
    else
    if (str=="Printemps") sais=Saison::Printemps;
    else {
        throw UTProfilerException(QString("erreur, StringToSaison, saison")+str+" inexistante");
    }
    return f;
}

UV* UVManager::trouver(const QString& c)const{
    for(unsigned int i=0; i<nb; i++)
        if (c==t[i]->getCode()) return t[i];
    return 0;
}

const UV& UVManager::getUV(const QString& code)const{
    return const_cast<UVManager*>(this)->getUV(code);
}

UV& UVManager::getUV(const QString& code){
    UV* uv=trouver(code);
    if (!uv) throw UTProfilerException("erreur, UVManager, UV inexistante");
    return *uv;
}

UVManager::~UVManager(){
    nb=nbMax=0;
    delete [] t;
}






/******Base de donn�e*******/

void UVManager::load(QSqlDatabase& db){
    QString code;
    QString titre;
    unsigned int nbc;
    Categorie cat;
    Saison sais;
    QWidget* parent=new QWidget;
    QString categorie;
    QString saison;
    QSqlTableModel* model=new QSqlTableModel(parent,db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("UV");
    model->select();
    int rowCount = model->rowCount();
    for(int i = 0; i < rowCount; ++i)
        {
            QSqlRecord record = model->record(i);
            code = record.value("code").toString();
            titre = record.value("titre").toString();
            nbc = record.value("nbCredits").toInt();
            categorie = record.value("uvCategorie").toString();
            cat=StringToCategorie(categorie);
            saison = record.value("saison").toString();
            sais = StringToSaison(saison);
            UV* uvtoadd=new UV(code, titre, nbc,cat,sais);
            addItem(uvtoadd);
    }

  }

void UVManager::addUV(const QString& c, const QString& t, unsigned int nbc, Saison sais, QSqlDatabase& dbCategorie, Categorie cat){
   /******Ajoute a la liste UVs******/
 QString categorie= CategorieToString(cat);
 QString saison= SaisonToString(sais);
   UV* uvtoadd=new UV(c,t,nbc,cat,sais);
   addItem(uvtoadd);
   /***********Ajoute � la BD*************/

   if(c.isEmpty()  || saison.isEmpty()  ||(nbc<=-1 || nbc>MAXCREDIT ))
   {
           qDebug()<<"Insertion Failed";

   }
   QSqlQuery *query = new QSqlQuery(dbCategorie);
   query->prepare("INSERT INTO UV (code,titre,uvCategorie,nbCredits,saison)"
                  "VALUES (:code,:titre,:uvCategorie,:nbCredits,:saison)");

   query->bindValue(0,c);
   query->bindValue(1,t);
   query->bindValue(2,categorie);
   query->bindValue(3,nbc);
   query->bindValue(4,saison);

   try{
   query->exec();
   }
   catch(UTProfilerException& e){
       //QMessageBox::warning("Insertion", QString("Insertion dans la base de donn�es impossible"));
   }
}

void UVManager::ajouterUV(const QString& c, const QString& t, unsigned int nbc, Saison sais, Categorie cat){
    UV* uvAdd=new UV(c,t,nbc,cat,sais);
    addItem(uvAdd);
}

Cursus* CursusManager::trouver(const QString& code)const{
    for(unsigned int i=0; i<nb; i++)
        if (code==t[i]->getCode()) return t[i];
    return 0;
}

void Cursus::addUvToCursus(const QString &c, QSqlDatabase db){
    UVManager& uv=UVManager::getInstance();
    UV& uvToEdit=uv.getUV(c);
    UVObligatoire.push_back(uvToEdit);
}

void CursusManager::load(QSqlDatabase& db){
    QString code;
    QString titre;
    unsigned int duree;
    unsigned int CS;
    unsigned int TM;
    unsigned int TSH;
    unsigned int SP;
    QWidget* parent=new QWidget;
    QSqlTableModel* model=new QSqlTableModel(parent,db);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("Cursus");
    model->select();
    int rowCount = model->rowCount();
    //QString uvCode = model->data(codeCursus,0);
    for(int i = 0; i < rowCount; ++i)
        {
            QSqlRecord record = model->record(i);
            code = record.value("code").toString();
            titre = record.value("titre").toString();
            duree = record.value("duree").toInt();
            CS = record.value("nbCS").toInt();
            TM = record.value("nbTM").toInt();
            TSH = record.value("nbTSH").toInt();
            SP = record.value("nbSP").toInt();
            Cursus* cursustoadd=new Cursus(code, titre, duree,CS,TM,TSH,SP);
            addItem(cursustoadd);
    }
  }

void CursusManager::addCursus(const QString& c,const QString& t, unsigned int duree,unsigned int Ccs,unsigned int Ctm,unsigned int Ctsh,unsigned int Csp,QSqlDatabase& db){
    /******Ajoute a la liste de cursus******/
    Cursus* cursustoadd=new Cursus(c,t,duree,Ccs,Ctm,Ctsh,Csp);
    addItem(cursustoadd);
    /***********Ajoute � la BD*************/
    if(c.isEmpty() || t.isEmpty())
    {
            qDebug()<<"Insertion Failed";

    }
    QSqlQuery *query = new QSqlQuery(db);
    query->prepare("INSERT INTO Cursus (code,titre,duree,nbCS,nbTM,nbTSH,nbSP)"
                   "VALUES (:code,:titre,:duree,:CS,:TM,:TSH,:SP)");

    query->bindValue(0,c);
    query->bindValue(1,t);
    query->bindValue(2,duree);
    query->bindValue(3,Ccs);
    query->bindValue(4,Ctm);
    query->bindValue(5,Ctsh);
    query->bindValue(6,Csp);
    try{
    query->exec();
    }
    catch(UTProfilerException& e){
        //QMessageBox::warning("Insertion", QString("Insertion dans la base de donn�es impossible"));
    }
}

Cursus& CursusManager::getCursus(const QString& c){
    Cursus* cursus=trouver(c);
    if (!cursus) throw UTProfilerException("erreur, CursusManager, Cursus inexistante");
    return *cursus;
}

const Cursus& CursusManager::getCursus(const QString& c)const{
    return const_cast<CursusManager*>(this)->getCursus(c);
}

CursusManager::~CursusManager(){
    nb=nbMax=0;
    delete [] t;
}

/*************Cursus*************/


