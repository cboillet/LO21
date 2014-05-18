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
    if (str=="CS") cat=CS;
	else
    if (str=="TM") cat=TM;
	else
    if (str=="SP") cat=SP;
	else
    if (str=="TSH") cat=TSH;
	else {
        throw UTProfilerException("erreur, lecture categorie");
	}
	return f;
}

Categorie StringToCategorie(const QString& str){
    if (str=="CS") return CS;
    else
    if (str=="TM") return TM;
    else
    if (str=="SP") return SP;
    else
    if (str=="TSH") return TSH;
    else {
        throw UTProfilerException(QString("erreur, StringToCategorie, categorie ")+str+" inexistante");
    }
}

QString CategorieToString(Categorie c){
    switch(c){
    case CS: return "CS";
    case TM: return "TM";
    case SP: return "SP";
    case TSH: return "TSH";
    default: throw UTProfilerException("erreur, categorie non traitee");
    }
}

QTextStream& operator<<(QTextStream& f, const Categorie& cat){
	switch(cat){
    case CS: f<<"CS"; break;
    case TM: f<<"TM"; break;
    case SP: f<<"SP"; break;
    case TSH: f<<"TSH"; break;
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

/******Base de donnée*******/

bool StrategieUvSQL::connect(){
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/SQlite/DataBase/UTProfiler.db");
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
}

void StrategieUvSQL::disconnect(){
    QString connection;
    connection=mydb.connectionName();
    QSqlDatabase::removeDatabase(connection);
}

void StrategieUvSQL::ajouterUV(Manager<UV>& man, const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p){
    QString code, titre, categorie, saison;
    int nbCredit;
    code=  c;
    titre= t;
    categorie= cat;
    saison= a; //saison à 1 si automne et 0 si printemps
    nbCredit = nbc;
    if(!connect() || code.isEmpty() || categorie.isEmpty() || saison.isEmpty()  ||(nbCredit<=-1 || nbCredit>MAXCREDIT ))
    {
            qDebug()<<"Insertion Failed";
            return;
    }
    QSqlQuery *query = new QSqlQuery(mydb);

    query->prepare("INSERT INTO UV (code,titre,uvCategorie,nbCredits,saison)"
                   "VALUES (:code,:titre,:uvCategorie,:nbCredits,:saison)");

    query->bindValue(0,code);
    query->bindValue(1,titre);
    query->bindValue(2,categorie);
    query->bindValue(3,nbCredit);
    query->bindValue(4,saison);
    query->exec();
    disconnect();
}




