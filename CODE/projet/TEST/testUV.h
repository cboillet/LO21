#ifndef TESTUV_H
#define TESTUV_H
#include <QtTest/QtTest>
#include"./../UTProfiler.h"

/*
remarques: un tests unitaires requiert d'instancier une classe pour la tester-> on ne peut pas tester les classes abstraites mais seulement les fonctions qui l'a compose
*/
/*
class UV {
    QString code;
    QString titre;
    unsigned int nbCredits;
    Categorie categorie;
    bool automne;
    bool printemps;
    UV(const UV& u);
    UV& operator=(const UV& u);
    UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p):
      code(c),titre(t),nbCredits(nbc),categorie(cat),automne(a),printemps(p){}
    friend class UVManager;
public:
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
    unsigned int getNbCredits() const { return nbCredits; }
    Categorie getCategorie() const { return categorie; }
    bool ouvertureAutomne() const { return automne; }
    bool ouverturePrintemps() const { return printemps; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setNbCredits(unsigned int n) { nbCredits=n; }
    void setCategorie(Categorie c) { categorie=c; }
    void setOuvertureAutomne(bool b) { automne=b; }
    void setOuverturePrintemps(bool b) { printemps=b; }
};
*/
class TestUV : public QObject{
    Q_OBJECT 
    virtual ~TestUV() {};
    UV* uvtest;
    private slots:
         //void TestOperator=();

   void TestsetNbCredits(){
       uvtest->setNbCredits(6);

         }
 /*
    void TestsetTitre(){
        string content="Programmation orientée objet";
        QString str = QString::fromUtf8(content.c_str());
        uvtest->setTitre(str);

        //QCOMPARE(uvtest->getTitre(), QString("Programmation orientée objet"));
    }

         void TestsetCode(){
             uvtest->setCode("LO21");
             QCOMPARE(uvtest->getCode(), QString("LO21"));
         }
         void TestsetOuvertureAutomne(){
             uvtest->setOuvertureAutomne(1);
             QVERIFY(uvtest->ouvertureAutomne() == 1);
         }
         void TestsetOuverturePrintemps(){
             uvtest->setOuverturePrintemps(1);
             QVERIFY(uvtest->ouverturePrintemps() == 1);
         }
*/
};

#endif // TESTUV_H


