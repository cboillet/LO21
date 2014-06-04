#include <QApplication>
#include <QtTest>
#include"./TEST/testUV.h"
#include"./TEST/testManager.h"
#include "UTProfiler.h"
#include "UVEditeur.h"
#include "manager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   /*

    UVManager& m=UVManager::getInstance();
    QString chemin = QFileDialog::getOpenFileName();
    m.load(chemin);
    UV& uv=m.getUV("LO21");
    UVEditeur fenetre(uv);

    fenetre.show();
    */


    int status=0;
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) { //body of lambda
         status |= QTest::qExec(obj, argc, argv);
         delete obj;
       };

     ASSERT_TEST(new TestUV()); //permet de faire plusieurs tests

    return status;
}
