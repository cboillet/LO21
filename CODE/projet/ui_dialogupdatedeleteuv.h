/********************************************************************************
** Form generated from reading UI file 'dialogupdatedeleteuv.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGUPDATEDELETEUV_H
#define UI_DIALOGUPDATEDELETEUV_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogUpdateDeleteUV
{
public:
    QComboBox *uvsModelCombo;
    QPushButton *deleteUV;
    QPushButton *updateUV;
    QWidget *widget;
    QVBoxLayout *updateUVverticalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *code;
    QLineEdit *codeLine;
    QHBoxLayout *horizontalLayout_4;
    QLabel *titre;
    QLineEdit *titreLine;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *nbCreditspinBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *saison;
    QComboBox *saisonComb;
    QHBoxLayout *horizontalLayout;
    QLabel *categorie;
    QComboBox *categorieComb;
    QPushButton *confirmUpdate;

    void setupUi(QDialog *DialogUpdateDeleteUV)
    {
        if (DialogUpdateDeleteUV->objectName().isEmpty())
            DialogUpdateDeleteUV->setObjectName(QStringLiteral("DialogUpdateDeleteUV"));
        DialogUpdateDeleteUV->resize(480, 365);
        uvsModelCombo = new QComboBox(DialogUpdateDeleteUV);
        uvsModelCombo->setObjectName(QStringLiteral("uvsModelCombo"));
        uvsModelCombo->setGeometry(QRect(20, 40, 81, 22));
        deleteUV = new QPushButton(DialogUpdateDeleteUV);
        deleteUV->setObjectName(QStringLiteral("deleteUV"));
        deleteUV->setGeometry(QRect(10, 280, 75, 23));
        updateUV = new QPushButton(DialogUpdateDeleteUV);
        updateUV->setObjectName(QStringLiteral("updateUV"));
        updateUV->setGeometry(QRect(110, 280, 75, 23));
        widget = new QWidget(DialogUpdateDeleteUV);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(220, 40, 221, 231));
        updateUVverticalLayout = new QVBoxLayout(widget);
        updateUVverticalLayout->setObjectName(QStringLiteral("updateUVverticalLayout"));
        updateUVverticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        code = new QLabel(widget);
        code->setObjectName(QStringLiteral("code"));

        horizontalLayout_5->addWidget(code);

        codeLine = new QLineEdit(widget);
        codeLine->setObjectName(QStringLiteral("codeLine"));

        horizontalLayout_5->addWidget(codeLine);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        titre = new QLabel(widget);
        titre->setObjectName(QStringLiteral("titre"));

        horizontalLayout_4->addWidget(titre);

        titreLine = new QLineEdit(widget);
        titreLine->setObjectName(QStringLiteral("titreLine"));

        horizontalLayout_4->addWidget(titreLine);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        nbCreditspinBox = new QSpinBox(widget);
        nbCreditspinBox->setObjectName(QStringLiteral("nbCreditspinBox"));
        nbCreditspinBox->setMinimum(0);
        nbCreditspinBox->setMaximum(6);

        horizontalLayout_3->addWidget(nbCreditspinBox);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        saison = new QLabel(widget);
        saison->setObjectName(QStringLiteral("saison"));

        horizontalLayout_2->addWidget(saison);

        saisonComb = new QComboBox(widget);
        saisonComb->setObjectName(QStringLiteral("saisonComb"));

        horizontalLayout_2->addWidget(saisonComb);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        categorie = new QLabel(widget);
        categorie->setObjectName(QStringLiteral("categorie"));

        horizontalLayout->addWidget(categorie);

        categorieComb = new QComboBox(widget);
        categorieComb->setObjectName(QStringLiteral("categorieComb"));

        horizontalLayout->addWidget(categorieComb);


        verticalLayout->addLayout(horizontalLayout);


        updateUVverticalLayout->addLayout(verticalLayout);

        confirmUpdate = new QPushButton(widget);
        confirmUpdate->setObjectName(QStringLiteral("confirmUpdate"));

        updateUVverticalLayout->addWidget(confirmUpdate);


        retranslateUi(DialogUpdateDeleteUV);

        QMetaObject::connectSlotsByName(DialogUpdateDeleteUV);
    } // setupUi

    void retranslateUi(QDialog *DialogUpdateDeleteUV)
    {
        DialogUpdateDeleteUV->setWindowTitle(QApplication::translate("DialogUpdateDeleteUV", "Dialog", 0));
        deleteUV->setText(QApplication::translate("DialogUpdateDeleteUV", "Supprimer", 0));
        updateUV->setText(QApplication::translate("DialogUpdateDeleteUV", "modifier", 0));
        code->setText(QApplication::translate("DialogUpdateDeleteUV", "Code", 0));
        titre->setText(QApplication::translate("DialogUpdateDeleteUV", "Titre", 0));
        label_3->setText(QApplication::translate("DialogUpdateDeleteUV", "Nombre de cr\303\251dits", 0));
        saison->setText(QApplication::translate("DialogUpdateDeleteUV", "Saison", 0));
        categorie->setText(QApplication::translate("DialogUpdateDeleteUV", "Cat\303\251gorie", 0));
        confirmUpdate->setText(QApplication::translate("DialogUpdateDeleteUV", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogUpdateDeleteUV: public Ui_DialogUpdateDeleteUV {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUPDATEDELETEUV_H
