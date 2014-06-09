#include "mainutprofiler.h"
#include "UTProfiler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainUTProfiler &w=MainUTProfiler::getUTProfiler();
    w.show();
    return a.exec();
}
