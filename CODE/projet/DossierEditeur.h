#ifndef DOSSIEREDITEUR_H
#define DOSSIEREDITEUR_H
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
#include <QTableView>
#include "dossier.h"

class DossierEditeur: public QWidget {
    Q_OBJECT
    QLineEdit* code;
    QLabel* codeLabel;
    QTextEdit* titre;
    QLabel* titreLabel;
    QSpinBox* credits;
    QLabel* creditsLabel;
    QComboBox* categorie;
    QLabel* categorieLabel;
    QPushButton* sauver;
    QPushButton* annuler;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    Etudiant& etudiant;
    QSqlDatabase& mydb;
    /*
    QString c;
    QString t;
    unsigned int nbc;
    Categorie cat;
    bool aut;
    bool print;
    */
    public:
    explicit DossierEditeur(Etudiant& etu,QSqlDatabase &db,QWidget *parent = 0):etudiant(etu),mydb(db){}
    ~DossierEditeur(){}
    signals:

    public slots:
    void sauverUV(QSqlDatabase& db){}
    void close() {}
    void annulerUV() {}
    //void modifierUV();
    private :
       // QPushButton *sauver;
       // QPushButton *annuler;
       //  QPushButton *modifier;
        QPushButton *quit;
        QDialogButtonBox * buttonBox;
        QSqlTableModel *model;
        QSqlTableModel* modelDossier;
};

#endif // DOSSIEREDITEUR_H
