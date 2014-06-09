#include <QApplication>
#include <QtTest>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"./TEST/testUV.h"
#include"./TEST/testManager.h"
#include "UTProfiler.h"
#include "UVEditeur.h"
#include "manager.h"
#include "profiler.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    /*
    QWidget fenetre;
    QHBoxLayout* couche=new QHBoxLayout;
    QVBoxLayout* couchecode=new QVBoxLayout;
    QVBoxLayout* couchetitre=new QVBoxLayout;
    QVBoxLayout* couchenbcredits=new QVBoxLayout;
    QVBoxLayout* coucheouverture=new QVBoxLayout;
    QLabel* code= new QLabel("code",&fenetre);
    QLabel* titre= new QLabel("titre",&fenetre);
    QLabel* nbcredits= new QLabel("nombre de crédits", &fenetre);
    QLabel* ouverture= new QLabel("semestre d'ouverture", &fenetre);

    couche->addLayout(couchetitre);
    couche->addLayout(couchecode);
    couche->addLayout(couchenbcredits);
    couche->addLayout(coucheouverture);
   // setLayout(couche);
    fenetre.show();
    */

   Profiler profiler;
   profiler.showMaximized();

    /*QWidget* test;
    UVEditeurNew* fenetre=new UVEditeurNew(test);
    test->show();
    */
    return app.exec();

    /*
    int status=0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) { //body of lambda
         status |= QTest::qExec(obj, argc, argv);
         delete obj;
       };

     ASSERT_TEST(new TestUV()); //permet de faire plusieurs tests

    return status;
    */
}
