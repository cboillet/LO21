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
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    /*
    QString c;
    QString t;
    unsigned int nbc;
    Categorie cat;
    bool aut;
    bool print;
    */
    public:
    explicit UVEditeurNew(QWidget *parent = 0);
    ~UVEditeurNew(){}
    signals:

    public slots:
    void sauverUV();
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
};


class UVEditeur : public QWidget{
    Q_OBJECT
    UV& uv;
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
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    public:
    explicit UVEditeur(UV& uvToEdit, QWidget *parent = 0);
    signals:
    public slots:
    private slots:
};

#endif // UVEDITEUR_H
