#include "UTProfiler.h"
#include "manager.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtGui>
#include <QMessageBox>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCoreApplication>
#include <QString>


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
    delete [] t;
    delete [] stratCredits;}


/*************Cursus*************/
Cursus::UVObligatoire::~UVObligatoire(){
    nb=nbMax=0;
    delete [] stratUV;
    delete [] t;
}
Cursus::CreditsObligatoire::~CreditsObligatoire(){
    nb=nbMax=0;
    delete [] stratCredits;
    delete [] t;
}


/******Base de donnée*******/

bool StrategieSQL::connect(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath()+"UTProfiler.db";
    mydb.setDatabaseName(dbPath);
   // mydb.setDatabaseName("C:/SQlite/DataBase/UTProfiler.db");
    mydb.setHostName("localhost");
    mydb.setUserName("root");
    mydb.setPassword("");
    if(!mydb.open()){

        qDebug()<<mydb.lastError();
        qFatal("Failed to connect");
       return false;
     }
     else
     {
        qDebug()<<"connected";
        return true;
     }
}

void StrategieSQL::disconnect(){
    QString connection;
    connection=mydb.connectionName();
    QSqlDatabase::removeDatabase(connection);
}

void StrategieUvSQL::ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){
    QString code, titre, categorie, saison;
    int nbCredit;
    code=  c;
    titre= t;
    categorie= CategorieToString(cat);
    saison= a; //saison à 1 si automne et 0 si printemps
    nbCredit = nbc;

    if(!connect() || code.isEmpty() || categorie.isEmpty() || saison.isEmpty()  ||(nbCredit<=-1 || nbCredit>MAXCREDIT ))
    {
            qDebug()<<"Insertion Failed";

    }

   {
    QSqlQuery *query = new QSqlQuery(mydb);

    query->prepare("INSERT INTO UV (code,titre,uvCategorie,nbCredits,saison)"
                   "VALUES (:code,:titre,:uvCategorie,:nbCredits,:saison)");

    query->bindValue(0,code);
    query->bindValue(1,titre);
    query->bindValue(2,categorie);
    query->bindValue(3,nbCredit);
    query->bindValue(4,saison);
    query->exec();

    }
    disconnect();
}

void StrategieCreditsSQL::ajouterCredits(Manager<Credits>& man, const Categorie& cat, unsigned int nbcredits){
    QString categorie= CategorieToString(cat);
    int nbCredits=nbcredits;

    if(!connect()||  (nbCredits<=-1 || nbCredits>MAXCREDIT ))
    {
            qDebug()<<"Insertion Failed";
            return;
    }

   {
    QSqlQuery *query = new QSqlQuery(mydb);

    query->prepare("INSERT INTO Credits (categorie,nbCredits)"
                   "VALUES (:categorie,:nbCredits)");

    query->bindValue(0,categorie);
    query->bindValue(1,nbCredits);
    query->exec();
    disconnect();
    }
}

void StrategieAddUvToCursusSQL::ajouterUvToCursus(Manager<UV>& man, const QString& c){
    QString code=c, titre, duree;
    Categorie cat;
    int creditsObligatoire;
    int nbCredits;
    if(!connect()||  code.isEmpty() )
    {
            qDebug()<<"Insertion Failed";
            return;
    }


 {
    QSqlDatabase::database().transaction();
    QSqlQuery *query = new QSqlQuery(mydb);
    query->exec("SELECT code FROM UV WHERE code ='c'");
                 if (query->next()) {
                     QString  code = query->value(0).toString();
                     query->exec("INSERT INTO Cursus (titre, duree,creditsObligatoire, uvObligatoire) "
                                "VALUES (:titre,:duree,:creditsObligatoire, "
                                + code + ')');
                     query->bindValue(0,titre);
                     query->bindValue(1,duree);                  
                     query->bindValue(2,creditsObligatoire);
                     query->bindValue(3,code);
                     query->exec();
                 }
    QSqlDatabase::database().commit();
  }
    disconnect();

}

    void ajouterCreditsToCursus(Manager<Credits>& man, const Credits& cursus){

  {
    QSqlDatabase::database().transaction();
    QSqlQuery *query = new QSqlQuery(mydb);

    query->exec("SELECT categorie FROM Credits WHERE categorie ='cat'");
                 if (query->next()) {
                     QString cat = query->value(0).toString();
                     query->exec("INSERT INTO Credits (categorie,nbCredits) "
                                "VALUES (:nbCredits, "
                                + cat + ')');
                     query->bindValue(0,cat);
                     query->bindValue(1,nbCredits);
                     query->exec();

    QSqlDatabase::database().commit();
    }
    disconnect();
}

}
