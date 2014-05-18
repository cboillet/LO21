#include "dialogajouteruv.h"
#include "ui_dialogajouteruv.h"

DialogAjouterUV::DialogAjouterUV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAjouterUV)
{
    ui->setupUi(this);
}

DialogAjouterUV::~DialogAjouterUV()
{
    delete ui;
}
