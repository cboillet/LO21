/********************************************************************************
** Form generated from reading UI file 'uvadddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UVADDDIALOG_H
#define UI_UVADDDIALOG_H

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

class Ui_UVAddDialog
{
public:
    QPushButton *insertUV;
    QLabel *test;
    QWidget *widget;
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

    void setupUi(QDialog *UVAddDialog)
    {
        if (UVAddDialog->objectName().isEmpty())
            UVAddDialog->setObjectName(QStringLiteral("UVAddDialog"));
        UVAddDialog->resize(871, 300);
        insertUV = new QPushButton(UVAddDialog);
        insertUV->setObjectName(QStringLiteral("insertUV"));
        insertUV->setGeometry(QRect(230, 250, 75, 23));
        test = new QLabel(UVAddDialog);
        test->setObjectName(QStringLiteral("test"));
        test->setGeometry(QRect(10, 270, 841, 20));
        QFont font;
        font.setPointSize(12);
        test->setFont(font);
        widget = new QWidget(UVAddDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(30, 20, 271, 201));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
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


        retranslateUi(UVAddDialog);

        QMetaObject::connectSlotsByName(UVAddDialog);
    } // setupUi

    void retranslateUi(QDialog *UVAddDialog)
    {
        UVAddDialog->setWindowTitle(QApplication::translate("UVAddDialog", "Dialog", 0));
        insertUV->setText(QApplication::translate("UVAddDialog", "Ajouter", 0));
        test->setText(QApplication::translate("UVAddDialog", "TextLabel", 0));
        code->setText(QApplication::translate("UVAddDialog", "Code", 0));
        titre->setText(QApplication::translate("UVAddDialog", "Titre", 0));
        label_3->setText(QApplication::translate("UVAddDialog", "Nombre de cr\303\251dits", 0));
        saison->setText(QApplication::translate("UVAddDialog", "Saison", 0));
        categorie->setText(QApplication::translate("UVAddDialog", "Cat\303\251gorie", 0));
    } // retranslateUi

};

namespace Ui {
    class UVAddDialog: public Ui_UVAddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UVADDDIALOG_H
