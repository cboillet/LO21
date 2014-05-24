#ifndef CURSUSPROFILER_H
#define CURSUSPROFILER_H

#include "manager.h"
#include <QString>
#include <QTextStream>
#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QCombobox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <type_traits>
#include <QFileDialog>

namespace Ui {
    class CatalogueCursus;
}

class CatalogueCursus : public QWidget
{
    Q_OBJECT

public:
    explicit CatalogueCursus(QWidget *parent = 0);
     CatalogueCursus();

private:
    Ui::CatalogueCursus *ui;
};


#endif // CURSUSPROFILER_H
