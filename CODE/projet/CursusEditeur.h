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
#include <QTableView>
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
    //void modifierUV();
    private :
       // QPushButton *sauver;
       // QPushButton *annuler;
       //  QPushButton *modifier;
        QPushButton *quit;
        QDialogButtonBox * buttonBox;
        QSqlTableModel *model;
};

class CursusEditeurAddUV: public QWidget {
    Q_OBJECT
    QSqlDatabase& mydb;
    QComboBox* cursus;
    QComboBox* uv;
    public:
    explicit CursusEditeurAddUV(QSqlDatabase &db,QWidget *parent = 0);
    ~CursusEditeurAddUV(){}
signals:
public slots:
    void sauverCursus(QSqlDatabase& db);
    void close() {}
    void annulerCursus() {}
private :
    QPushButton *quit;
    QDialogButtonBox * buttonBox;
    QSqlTableModel *model;
    QSqlTableModel *model2;
};
#endif // CURSUSEDITEUR_H
