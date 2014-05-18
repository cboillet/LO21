#include "mainutprofiler.h"
#include "ui_mainutprofiler.h"
#include "uvadddialog.h"
#include "dialogupdatedeleteuv.h"
#include <QTableWidget>
#include <QPushButton>


MainUTProfiler *MainUTProfiler::utProfiler=0;
MainUTProfiler::MainUTProfiler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUTProfiler)
{
    ui->setupUi(this);
   /* if(!connectDb()){
         ui->db->setText("failed");
     }
     else
     {
         ui->db->setText("connected");
     }*/
}

MainUTProfiler::~MainUTProfiler()
{
    delete ui;
}



/*
This Slot Open the Window To Add a new UV
*/

void MainUTProfiler::on_addUV_clicked()
{
    UVAddDialog addUVD;
    addUVD.setModal(true);
    addUVD.exec();

}

void MainUTProfiler::on_updateDeleteUV_clicked()
{
    DialogUpdateDeleteUV updelUVD;
    updelUVD.setModal(true);
    updelUVD.exec();
}
