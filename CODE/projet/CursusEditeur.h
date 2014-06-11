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
    Q_OBJECT
    QLineEdit* code;
    QLabel* codeLabel;
    QTextEdit* titre;
    QLabel* titreLabel;
    QSpinBox* duree;
    QLabel* dureeLabel;
    QLabel* creditsLabel;
    QLabel* CSLabel;
    QSpinBox* CS;
    QLabel* TMLabel;
    QSpinBox* TM;
    QLabel* TSHLabel;
    QSpinBox* TSH;
    QLabel* SPLabel;
    QSpinBox* SP;
    QPushButton* sauver;
    QPushButton* annuler;
    QPushButton* UVObligatoire;
    QVBoxLayout* couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QSqlDatabase& mydb;
    public:
    explicit CursusEditeurNew(QSqlDatabase &db,QWidget *parent = 0);
    ~CursusEditeurNew(){}
    signals:

    public slots:
    void sauverCursus(QSqlDatabase& db);
    void close() {}
    void annulerCursus() {}
    void setUVObligatoire(QSqlDatabase& db) {}
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
