/********************************************************************************
** Form generated from reading UI file 'mainutprofiler.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINUTPROFILER_H
#define UI_MAINUTPROFILER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainUTProfiler
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *UV;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *updateDeleteUV;
    QPushButton *addUV;
    QWidget *Formation;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainUTProfiler)
    {
        if (MainUTProfiler->objectName().isEmpty())
            MainUTProfiler->setObjectName(QStringLiteral("MainUTProfiler"));
        MainUTProfiler->resize(596, 335);
        centralWidget = new QWidget(MainUTProfiler);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 371, 221));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        UV = new QWidget();
        UV->setObjectName(QStringLiteral("UV"));
        layoutWidget = new QWidget(UV);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 165, 65));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        updateDeleteUV = new QPushButton(layoutWidget);
        updateDeleteUV->setObjectName(QStringLiteral("updateDeleteUV"));

        verticalLayout->addWidget(updateDeleteUV);

        addUV = new QPushButton(layoutWidget);
        addUV->setObjectName(QStringLiteral("addUV"));

        verticalLayout->addWidget(addUV);

        tabWidget->addTab(UV, QString());
        Formation = new QWidget();
        Formation->setObjectName(QStringLiteral("Formation"));
        layoutWidget1 = new QWidget(Formation);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 207, 65));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_5 = new QPushButton(layoutWidget1);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout_2->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(layoutWidget1);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout_2->addWidget(pushButton_6);

        tabWidget->addTab(Formation, QString());
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(450, 80, 131, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(460, 120, 111, 23));
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(440, 50, 151, 23));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(480, 160, 75, 23));
        MainUTProfiler->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainUTProfiler);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 596, 26));
        MainUTProfiler->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainUTProfiler);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainUTProfiler->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainUTProfiler);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainUTProfiler->setStatusBar(statusBar);

        retranslateUi(MainUTProfiler);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainUTProfiler);
    } // setupUi

    void retranslateUi(QMainWindow *MainUTProfiler)
    {
        MainUTProfiler->setWindowTitle(QApplication::translate("MainUTProfiler", "MainUTProfiler", 0));
        updateDeleteUV->setText(QApplication::translate("MainUTProfiler", "Visualiser et g\303\251rer Les UVs", 0));
        addUV->setText(QApplication::translate("MainUTProfiler", "Ajouter une UV", 0));
        tabWidget->setTabText(tabWidget->indexOf(UV), QApplication::translate("MainUTProfiler", "UV", 0));
        pushButton_5->setText(QApplication::translate("MainUTProfiler", "Visualiser et g\303\251rer Les Formations", 0));
        pushButton_6->setText(QApplication::translate("MainUTProfiler", "Ajouter une nouvelle formation", 0));
        tabWidget->setTabText(tabWidget->indexOf(Formation), QApplication::translate("MainUTProfiler", "Formation", 0));
        pushButton->setText(QApplication::translate("MainUTProfiler", "Simulez Votre situation", 0));
        pushButton_2->setText(QApplication::translate("MainUTProfiler", "PushButton", 0));
        pushButton_7->setText(QApplication::translate("MainUTProfiler", "D\303\251finir votre jeu de Donn\303\251es", 0));
        pushButton_4->setText(QApplication::translate("MainUTProfiler", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MainUTProfiler: public Ui_MainUTProfiler {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINUTPROFILER_H
