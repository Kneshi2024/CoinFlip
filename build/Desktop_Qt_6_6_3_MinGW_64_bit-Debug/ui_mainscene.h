/********************************************************************************
** Form generated from reading UI file 'mainscene.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCENE_H
#define UI_MAINSCENE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainScene
{
public:
    QAction *actionquit;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *MainScene)
    {
        if (MainScene->objectName().isEmpty())
            MainScene->setObjectName("MainScene");
        MainScene->resize(592, 418);
        actionquit = new QAction(MainScene);
        actionquit->setObjectName("actionquit");
        centralwidget = new QWidget(MainScene);
        centralwidget->setObjectName("centralwidget");
        MainScene->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainScene);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 592, 26));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainScene->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(actionquit);

        retranslateUi(MainScene);

        QMetaObject::connectSlotsByName(MainScene);
    } // setupUi

    void retranslateUi(QMainWindow *MainScene)
    {
        MainScene->setWindowTitle(QCoreApplication::translate("MainScene", "MainScene", nullptr));
        actionquit->setText(QCoreApplication::translate("MainScene", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainScene", "\345\223\210\345\223\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainScene: public Ui_MainScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCENE_H
