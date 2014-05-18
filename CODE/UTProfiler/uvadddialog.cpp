#include "uvadddialog.h"
#include "ui_uvadddialog.h"
#include "mainutprofiler.h"


const int MAXCREDIT=6;

UVAddDialog::UVAddDialog(QWidget *parent) :QDialog(parent),ui(new Ui::UVAddDialog)
{
    ui->setupUi(this);

    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){
        ui->test->setText("Still Connected ...");

        QSqlQueryModel *modelCategorie= new QSqlQueryModel();
        QSqlQueryModel *modelSaison= new QSqlQueryModel();

        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

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
        ui->test->setText("Failed ... ");

    mainUTProfiler.deconnect();


}

UVAddDialog::~UVAddDialog()
{
    delete ui;
}

void UVAddDialog::on_insertUV_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    QString code,titre,categorie,saison;
    int  nbCredit=-1;

    code=  ui->codeLine->text();
    titre= ui->titreLine->text();
    categorie= ui->categorieComb->currentText();
    saison= ui->saisonComb->currentText();
    nbCredit = ui->nbCreditspinBox->value();

    mainUTProfiler.deconnect();
    if(!mainUTProfiler.connectDb() || code.isEmpty() || categorie.isEmpty() || saison.isEmpty()  ||(nbCredit<=-1 || nbCredit>MAXCREDIT )){

            qDebug()<<"Insertion Failed";
            return;
    }
    QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

    query->prepare("INSERT INTO UV (code,titre,uvCategorie,nbCredits,saison)"
                   "VALUES (:code,:titre,:uvCategorie,:nbCredits,:saison)");

    query->bindValue(0,code);
    query->bindValue(1,titre);
    query->bindValue(2,categorie);
    query->bindValue(3,nbCredit);
    query->bindValue(4,saison);


     if(query->exec()){
        ui->test->setText(code +" " + " added !");
    }
     else
     {
         ui->test->setText("Failed...");

     }

    mainUTProfiler.disconnect();
}
