#ifndef DIALOGUPDATEDELETEUV_H
#define DIALOGUPDATEDELETEUV_H

#include <QDialog>
#include <QFileInfo>
#include <QSql>

namespace Ui {
class DialogUpdateDeleteUV;
}

class DialogUpdateDeleteUV : public QDialog
{
    Q_OBJECT

public:
    bool setUVcode();
    explicit DialogUpdateDeleteUV(QWidget *parent = 0);
    ~DialogUpdateDeleteUV();
    Ui::DialogUpdateDeleteUV* getUiUVdEleteUpdate(){
        return ui;

    }

private:
    Ui::DialogUpdateDeleteUV *ui;
};

#endif // DIALOGUPDATEDELETEUV_H
