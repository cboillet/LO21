#ifndef ETUDIANTEDITEUR_H
#define ETUDIANTEDITEUR_H
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
#include <QListWidget>
#include <QTableView>
#include <QListView>
#include <QMainWindow>
#include "dossier.h"

class EtudiantEditeur: public QWidget {
    Q_OBJECT
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;
    QComboBox* cursus;
    QLabel* cursusLabel;
    QSpinBox* semestre;
    QLabel* semestreLabel;
    QPushButton* sauver;
    QPushButton* annuler;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QSqlDatabase& mydb;
    QMainWindow *fenetre;
    public:
    explicit EtudiantEditeur(QSqlDatabase &db,QMainWindow *parent = 0);
    ~EtudiantEditeur(){}
    signals:

    public slots:
    void sauverEtudiant(QSqlDatabase& db);
    void close() {}
    void annulerEtudiant() {}
    //void modifierUV();
    private :
        QPushButton *quit;
        QDialogButtonBox * buttonBox;
        QSqlTableModel *modelCursus;
        QSqlTableModel *modelEtu;
};

class EtudiantEditeurFormationPasse: public QWidget{
  Q_OBJECT
    Etudiant& etudiant;
    QListView* uvObtenue;
    QLabel* uvObetnueLabel;
    QLabel* equivalenceLabel;
    QLabel* nomELabel;
    QLabel* typeELabel;
    QLabel* CSLabel;
    QLabel* TMLabel;
    QLabel* TSHLabel;
    QLabel* SPLabel;
    QLineEdit* nomE;
    QComboBox* typeE;
    QSpinBox* CS;
    QSpinBox* TM;
    QSpinBox* TSH;
    QSpinBox* SP;
    QPushButton* sauver;
    QPushButton* annuler;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QSqlDatabase& mydb;
    QSqlTableModel *modelUV;
    QSqlTableModel *modelEquival;
    QSqlTableModel *modelEtu;
    QSqlTableModel *modelDossier;
    QSqlTableModel *modelInscription;
    QSqlTableModel *modelDossierInsc;
    public:
    explicit EtudiantEditeurFormationPasse(Etudiant& etu, QSqlDatabase& db, QWidget* parent);
    ~EtudiantEditeurFormationPasse(){}
    signals:

    public slots:
    void sauverEtudiant(QSqlDatabase& db);
    void close() {}
    void annulerEtudiant() {}
    //void modifierUV();
    private :
        QPushButton *quit;
        QDialogButtonBox * buttonBox;
        QSqlTableModel *modelCursus;
};

#endif // ETUDIANTEDITEUR_H
