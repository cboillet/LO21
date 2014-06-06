#include <QApplication>
#include <QtTest>
#include"./TEST/testUV.h"
#include"./TEST/testManager.h"
#include "UTProfiler.h"
#include "UVEditeur.h"
#include "manager.h"
#include "profiler.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    UVManager& m=UVManager::getInstance();
   // QString chemin = QFileDialog::getOpenFileName(); //a tester quand j'aurais la base de données
   /* m.stratUV->connect();
   UV& uv=m.getUV("LO21");
   UV& uv;
   UVEditeur fenetre(uv);
   fenetre.show();
   */

    Profiler profiler;
    profiler.show();
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
