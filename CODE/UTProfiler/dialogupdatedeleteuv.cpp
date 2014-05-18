#include "dialogupdatedeleteuv.h"
#include "ui_dialogupdatedeleteuv.h"
#include "mainutprofiler.h"

DialogUpdateDeleteUV::DialogUpdateDeleteUV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpdateDeleteUV)
{
    ui->setupUi(this);


    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){

        QSqlQueryModel *modelUvs= new QSqlQueryModel();
        QSqlQueryModel *modelCategorie= new QSqlQueryModel();
        QSqlQueryModel *modelSaison= new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

        // SET All the Uvs on the Combobox
        query->prepare("SELECT code FROM UV");
        if(query->exec()){
            modelUvs->setQuery(*query);
            ui->uvsModelCombo->setModel(modelUvs);
        }

        // SET The Possible Categorie Values
        query->prepare("SELECT uvType FROM categorie");
        query->exec();
        modelCategorie->setQuery(*query);
        ui->categorieComb->setModel(modelCategorie);

        // SET The Possible Saison Values

        query->prepare("SELECT SaisonType FROM saison");
        query->exec();
        modelSaison->setQuery(*query);
        ui->saisonComb->setModel(modelSaison);
        // Disconnection

    }
    else
    {
        qDebug()<<"Failed to open connection..";
    }

    mainUTProfiler.deconnect();


}



DialogUpdateDeleteUV::~DialogUpdateDeleteUV()
{
    delete ui;
}
