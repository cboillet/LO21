#include <QApplication>
#include <QtTest>
#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"./TEST/testUV.h"
#include"./TEST/testManager.h"
#include "UTProfiler.h"
#include "dossier.h"
#include "UVEditeur.h"
#include "istream"
#include "ostream"
#include "manager.h"
#include "profiler.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    //Semestre* s=new Semestre(sais,annee);
   Profiler profiler;
   profiler.showMaximized();
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
