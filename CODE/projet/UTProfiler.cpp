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
    delete [] stratUV;
    delete [] t;
}

/**********CreditsManager*********/
CreditsManager::~CreditsManager(){
    nb=nbMax=0;
    delete [] t; //liste de Credits**
    delete [] stratCredits;}


/*************Cursus*************/
Cursus::UVObligatoire::~UVObligatoire(){
    nb=nbMax=0;
    delete [] stratUV;
    delete [] t;
}
/*Cursus::CreditsObligatoire::~CreditsObligatoire(){
    nb=nbMax=0;
    delete [] stratCredits;
    delete [] t;
}*/


/******Base de donnée*******/
void UVManager::addUV( const QString& c, const QString& t, unsigned int nbc, Categorie cat, Saison sais,QSqlDatabase& db){
   QString code, titre, categorie, saison;


   if(code.isEmpty() || categorie.isEmpty() || saison.isEmpty()  ||(nbCredit<=-1 || nbCredit>MAXCREDIT ))
   {
           qDebug()<<"Insertion Failed";

   }
   QSqlQuery *query = new QSqlQuery(db);
   query->prepare("INSERT INTO UV (code,titre,uvCategorie,nbCredits,saison)"
                  "VALUES (:code,:titre,:uvCategorie,:nbCredits,:saison)");

   query->bindValue(0,code);
   query->bindValue(1,titre);
   query->bindValue(2,categorie);
   query->bindValue(3,nbCredit);
   query->bindValue(4,saison);

   try{
   query->exec();
   }
   catch(UTProfilerException& e){
       //QMessageBox::warning("Insertion", QString("Insertion dans la base de données impossible"));
   }
}



void StrategieCreditsSQL::ajouterCredits(Manager<Credits,CreditsManager>& man,const Categorie& cat, unsigned int nbcredits,QSqlDatabase& db){
   QString categorie= CategorieToString(cat);
   int nbCredits=nbcredits;
   // QSqlDatabase db;

   if((nbCredits<=-1 || nbCredits>MAXCREDIT ))
   {
           qDebug()<<" Insertion Failed";
           return;
   }

  {
   QSqlQuery *query = new QSqlQuery(db);

   query->prepare("INSERT INTO Credits ( categorie,nbCredits)"
                  "VALUES (:categorie,:nbCredits)");


   query->bindValue(0,categorie);
   query->bindValue(1,nbCredits);
   query->exec();

   /*query->prepare("INSERT INTO Credits (cursus, categorie,nbCredits)"
                  "VALUES (:cursus,:categorie,:nbCredits)");

   query->bindValue(0,cursus);
   query->bindValue(1,categorie);
   query->bindValue(2,nbCredits);
   query->exec();*/
   }

}



Cursus* CursusManager::trouver(const QString& code)const{
    for(unsigned int i=0; i<nb; i++)
        if (code==t[i]->getCode()) return t[i];
    return 0;
}

void Cursus::UVObligatoire::addUvToCursus(const QString &c, QSqlDatabase db){
    UVManager& uv=UVManager::getInstance();
    UV& uvToEdit=uv.getUV(c);
    //UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p)
    UV* uvToAdd=new UV(c,uvToEdit.geTitre(),uvToEdit.getNbCredits(),uvToEdit.getCategorie(),uvToEdit.ouvertureAutomne(),uvToEdit.ouverturePrintemps());
    addItem(uvToAdd);
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
    /***********Ajoute à la BD*************/
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
        //QMessageBox::warning("Insertion", QString("Insertion dans la base de données impossible"));
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


