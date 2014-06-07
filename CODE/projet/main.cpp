#include <QApplication>
#include <QtTest>
#include <QMainWindow>
#include <QTextEdit>
#include"./TEST/testUV.h"
#include"./TEST/testManager.h"
#include "UTProfiler.h"
#include "UVEditeur.h"
#include "manager.h"
#include "profiler.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

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
