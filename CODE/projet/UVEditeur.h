#ifndef UVEDITEUR_H
#define UVEDITEUR_H
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


class UVEditeurNew: public QWidget {
    Q_OBJECT
    QLineEdit* code;
    QLabel* codeLabel;
    QTextEdit* titre;
    QLabel* titreLabel;
    QSpinBox* credits;
    QLabel* creditsLabel;
    QComboBox* categorie;
    QLabel* categorieLabel;
    QLabel* ouvertureLabel;
    QCheckBox* automne;
    QCheckBox* printemps;
    QPushButton* sauver;
    QPushButton* annuler;
  //QPushButton *modifier;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    public:
    explicit UVEditeurNew(QWidget *parent = 0);
    signals:
    public slots:
        virtual void sauverUV() = 0;
        virtual void annulerUV() = 0;
        //void modifierUV();
    private :
       // QPushButton *sauver;
       // QPushButton *annuler;
        //  QPushButton *modifier;
        QPushButton *quit;
        QDialogButtonBox * buttonBox;
        QSqlTableModel *model;

};

/*
class UVEditeur : public UVEditeurNew {
    Q_OBJECT
    public:
    explicit UVEditeur(UV& uvToEdit, QWidget *parent = 0);
    signals:
    public slots:
        void sauverUV();
        void annulerUV();
        //void modifierUV();
    private :
       // QPushButton *sauver;
       // QPushButton *annuler;
        //  QPushButton *modifier;
        QPushButton *quit;
        QDialogButtonBox * buttonBox;
        QSqlTableModel *model;
};
*/
#endif // UVEDITEUR_H
