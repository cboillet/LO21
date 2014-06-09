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
    delete [] stratCredits;};


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
    mydb.setDatabaseName("C:/SQLite/UTProfiler.s3db");
    mydb.setHostName("localhost");
    mydb.setUserName("root");
    mydb.setPassword("");
    if(!mydb.open()){

       qDebug()<<"failed";
       return false;
     }
     else
     {
        qDebug()<<"succes";
        return true;
     }

   mydb = QSqlDatabase::addDatabase("QSQLITE");
   //QString dbPath = QCoreApplication::applicationDirPath()+"C:/SQlite/sqliteadmin/UTProfiler.s3db";
  // mydb.setDatabaseName(dbPath);
   mydb.setDatabaseName("C:/SQlite/sqliteadmin/UTProfiler.s3db");
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

void StrategieUvSQL::ajouterUV(Manager<UV,UVManager>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){
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

void StrategieUvSQL::deleteUV(){

   if(!connect())
   {
           qDebug()<<" Connexion Failed";
           return;
   }

  {
   QSqlDatabase::database().transaction();
   QSqlQuery *query = new QSqlQuery(mydb);

   query->prepare("DELETE FROM UV where code='code'");
           if(query->exec()){
              qDebug("Deleted");
          }
           else
           {
              qDebug()<<query->lastError();
           }

   QSqlDatabase::database().commit();
   }
   disconnect();

}

void StrategieCreditsSQL::ajouterCredits(Manager<Credits,CreditsManager>& man,const Categorie& cat, unsigned int nbcredits){
   QString categorie= CategorieToString(cat);
   int nbCredits=nbcredits;

   if(!connect()||  (nbCredits<=-1 || nbCredits>MAXCREDIT ))
   {
           qDebug()<<" Insertion Failed";
           return;
   }

  {
   QSqlQuery *query = new QSqlQuery(mydb);

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


   disconnect();
   }
}

void StrategieCreditsSQL::deleteCredits(){

   if(!connect())
   {
           qDebug()<<" Insertion Failed";
           return;
   }

  {
   QSqlDatabase::database().transaction();
   QSqlQuery *query = new QSqlQuery(mydb);

   query->prepare("DELETE FROM Credits where categorie='cat'");
           if(query->exec()){
              qDebug("Deleted");
          }
           else
           {
              qDebug()<<query->lastError();
           }

   QSqlDatabase::database().commit();
   }
   disconnect();
}

void StrategieAddUvToCursusSQL::ajouterUvToCursus(Manager<UV,UVManager>& man, const QString& c){
   QString code=c, titre,  uvObligatoire, categorie;
   int creditsObligatoire, duree;


   if(!connect()||  code.isEmpty() )
   {
           qDebug()<<"Insertion Failed";
           return;
   }


{
   QSqlDatabase::database().transaction();
   QSqlQuery *query = new QSqlQuery(mydb);
   query->exec("SELECT code FROM UVObligatoire WHERE code ='code'");
                if (query->next()) {
                    QString  code = query->value(0).toString();
                    query->exec("INSERT INTO Cursus (code, titre, duree, uvObligatoire, categorie, creditsObligatoire) "
                               "VALUES (" + code +":titre,:duree,:uvObligatoire,:categorie,:creditsObligatoire)");
                    query->bindValue(0,code);
                    query->bindValue(1,titre);
                    query->bindValue(2,duree);
                    query->bindValue(3,uvObligatoire);
                    query->bindValue(4,categorie);
                    query->bindValue(5,creditsObligatoire);

                    //query->exec();
                            if(query->exec()){
                               qDebug("Inserted");
                           }
                            else
                            {
                               qDebug()<<query->lastError();
                            }

                }
   QSqlDatabase::database().commit();
 }
   disconnect();

}


void StrategieAddUvToCursusSQL::deleteUvToCursus(){
    QString code=code;
    if(!connect())
    {
            qDebug()<<" Insertion Failed";
            return;
    }

   {
    QSqlDatabase::database().transaction();
    QSqlQuery *query = new QSqlQuery(mydb);

    query->prepare("DELETE FROM Cursus where codeUV='code'");
            if(query->exec()){
               qDebug("Deleted");
           }
            else
            {
               qDebug()<<query->lastError();
            }

    QSqlDatabase::database().commit();
    }
    disconnect();
}


void StrategieAddCreditsToCursusSQL::deleteCreditsToCursus(){
    if(!connect())
    {
            qDebug()<<" Insertion Failed";
            return;
    }

   {
    QSqlDatabase::database().transaction();
    QSqlQuery *query = new QSqlQuery(mydb);

    query->prepare("DELETE FROM Cursus where code='code'");
            if(query->exec()){
               qDebug("Deleted");
           }
            else
            {
               qDebug()<<query->lastError();
            }

    QSqlDatabase::database().commit();
    }
    disconnect();

}



  /* void ajouterCreditsToCursus(Manager<Credits>& man, const Cursus& cu, Categorie& cat){
   QString cursus=c, categorie= CategorieToString(cat);
   int nbCredits;
 {
   QSqlDatabase::database().transaction();
   QSqlQuery *query = new QSqlQuery(mydb);

   query->exec("SELECT nbCredits FROM Credits WHERE cursus= 'cursus' AND categorie ='categorie'");
                if (query->next()) {
                    QString cat = query->value(0).toString();
                    query->exec("INSERT INTO Cursus (code, titre, duree, uvObligatoire, categorie, creditsObligatoire) "
                                "VALUES (:code,:titre,:duree,:uvObligatoire,:categorie,"
                               + nbCredits + ')');
                    query->bindValue(0,code);
                    query->bindValue(1,nbCredits);
                    query->exec();

   QSqlDatabase::database().commit();
   }
   disconnect();
}

}*/

void StrategieCursusSQL::addCursus(Manager<Cursus,CursusManager>& man,const QString& c, const QString& t, unsigned int d)
{


}

void StrategieCursusSQL::deleteCursus(){
   //QString code=code;
   if(!connect())
   {
           qDebug()<<" Connexion Failed";
           return;
   }

  {
   QSqlDatabase::database().transaction();
   QSqlQuery *query = new QSqlQuery(mydb);

   query->prepare("DELETE FROM Cursus where code='code'");
           if(query->exec()){
              qDebug("Deleted");
          }
           else
           {
              qDebug()<<query->lastError();
           }

   QSqlDatabase::database().commit();
   }
   disconnect();

}

Cursus* CursusManager::trouver(const QString& code)const{
    for(unsigned int i=0; i<nb; i++)
        if (code==t[i]->getCode()) return t[i];
    return 0;
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
    delete [] stratCursus;
    delete [] t;
}
