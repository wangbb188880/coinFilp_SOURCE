/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScene
{
public:
    QAction *actionquit;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuquit;

    void setupUi(QMainWindow *MainScene)
    {
        if (MainScene->objectName().isEmpty())
            MainScene->setObjectName(QStringLiteral("MainScene"));
        MainScene->resize(400, 300);
        actionquit = new QAction(MainScene);
        actionquit->setObjectName(QStringLiteral("actionquit"));
        actionquit->setEnabled(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/resource/Coin0001.png"), QSize(), QIcon::Normal, QIcon::On);
        actionquit->setIcon(icon);
        centralWidget = new QWidget(MainScene);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainScene->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainScene);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        menuquit = new QMenu(menuBar);
        menuquit->setObjectName(QStringLiteral("menuquit"));
        MainScene->setMenuBar(menuBar);

        menuBar->addAction(menuquit->menuAction());
        menuquit->addAction(actionquit);

        retranslateUi(MainScene);

        QMetaObject::connectSlotsByName(MainScene);
    } // setupUi

    void retranslateUi(QMainWindow *MainScene)
    {
        MainScene->setWindowTitle(QApplication::translate("MainScene", "MainScene", Q_NULLPTR));
        actionquit->setText(QApplication::translate("MainScene", "\351\200\200\345\207\272", Q_NULLPTR));
        menuquit->setTitle(QApplication::translate("MainScene", "\345\274\200\345\247\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainScene: public Ui_MainScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H
