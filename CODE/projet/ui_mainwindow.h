/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionUV;
    QAction *actionCursus;
    QAction *actionCatalogue_des_UVs;
    QAction *actionCatalogue_des_cursus;
    QAction *actionG_nerer_une_solution;
    QAction *actionConsulter_des_solutions;
    QAction *actionQuitter;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFichiers;
    QMenu *menuOuvrir;
    QMenu *menuSolutions;
    QMenu *menuEdition;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1559, 694);
        actionUV = new QAction(MainWindow);
        actionUV->setObjectName(QStringLiteral("actionUV"));
        actionCursus = new QAction(MainWindow);
        actionCursus->setObjectName(QStringLiteral("actionCursus"));
        actionCatalogue_des_UVs = new QAction(MainWindow);
        actionCatalogue_des_UVs->setObjectName(QStringLiteral("actionCatalogue_des_UVs"));
        actionCatalogue_des_cursus = new QAction(MainWindow);
        actionCatalogue_des_cursus->setObjectName(QStringLiteral("actionCatalogue_des_cursus"));
        actionG_nerer_une_solution = new QAction(MainWindow);
        actionG_nerer_une_solution->setObjectName(QStringLiteral("actionG_nerer_une_solution"));
        actionConsulter_des_solutions = new QAction(MainWindow);
        actionConsulter_des_solutions->setObjectName(QStringLiteral("actionConsulter_des_solutions"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1559, 26));
        menuFichiers = new QMenu(menuBar);
        menuFichiers->setObjectName(QStringLiteral("menuFichiers"));
        menuOuvrir = new QMenu(menuFichiers);
        menuOuvrir->setObjectName(QStringLiteral("menuOuvrir"));
        menuSolutions = new QMenu(menuFichiers);
        menuSolutions->setObjectName(QStringLiteral("menuSolutions"));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QStringLiteral("menuEdition"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFichiers->menuAction());
        menuBar->addAction(menuEdition->menuAction());
        menuFichiers->addAction(menuOuvrir->menuAction());
        menuFichiers->addAction(menuSolutions->menuAction());
        menuFichiers->addSeparator();
        menuFichiers->addAction(actionQuitter);
        menuOuvrir->addAction(actionCatalogue_des_UVs);
        menuOuvrir->addAction(actionCatalogue_des_cursus);
        menuSolutions->addAction(actionG_nerer_une_solution);
        menuSolutions->addAction(actionConsulter_des_solutions);
        menuEdition->addAction(actionUV);
        menuEdition->addAction(actionCursus);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionUV->setText(QApplication::translate("MainWindow", "UV", 0));
        actionCursus->setText(QApplication::translate("MainWindow", "Cursus", 0));
        actionCatalogue_des_UVs->setText(QApplication::translate("MainWindow", "Catalogue des UVs", 0));
        actionCatalogue_des_cursus->setText(QApplication::translate("MainWindow", "Catalogue des cursus", 0));
        actionG_nerer_une_solution->setText(QApplication::translate("MainWindow", "G\303\251nerer une solution", 0));
        actionConsulter_des_solutions->setText(QApplication::translate("MainWindow", "Consulter des solutions", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "Quitter", 0));
        menuFichiers->setTitle(QApplication::translate("MainWindow", "Fichiers", 0));
        menuOuvrir->setTitle(QApplication::translate("MainWindow", "Ouvrir", 0));
        menuSolutions->setTitle(QApplication::translate("MainWindow", "Solutions", 0));
        menuEdition->setTitle(QApplication::translate("MainWindow", "Edition", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
