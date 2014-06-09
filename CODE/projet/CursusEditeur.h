#ifndef CURSUSEDITEUR_H
#define CURSUSEDITEUR_H
#include <QWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include <QSqlTableModel>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "UTProfiler.h"


class CursusEditeurNew: public QWidget {
    QLineEdit* code;
    QPushButton* sauver;
    QPushButton* annuler;
  //QPushButton *modifier;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    public:
    explicit CursusEditeurNew(QWidget *parent = 0);
    ~CursusEditeurNew(){}
    signals:

    public slots:
    void sauverCursus() {}
    void annulerCursus() {}
    //void modifierUV();
    private :
       // QPushButton *sauver;
       // QPushButton *annuler;
       //  QPushButton *modifier;
        QPushButton *quit;
        QDialogButtonBox * buttonBox;
        QSqlTableModel *model;
};
#endif // CURSUSEDITEUR_H
