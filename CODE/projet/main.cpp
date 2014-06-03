#include <QApplication>
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
    return app.exec();
}
