#ifndef CURSUSPROFILER_H
#define CURSUSPROFILER_H

#include <QWidget>

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
