#include "CursusProfiler.h"
#include "ui_CatalogueCursus.h"

CatalogueCursus::CatalogueCursus(QWidget *parent) :QWidget(parent),ui(new Ui::CatalogueCursus)
{
    ui->setupUi(this);
}

CatalogueCursus::~CatalogueCursusr()
{
    delete ui;

}
