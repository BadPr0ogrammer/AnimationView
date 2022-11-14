/********************************************************************************
** Form generated from reading UI file 'myMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYMAINWINDOW_H
#define UI_MYMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "pqColorMapEditor.h"
#include "pqDataInformationWidget.h"
#include "pqPipelineBrowserWidget.h"
#include "pqPropertiesPanel.h"
#include "pqStatusBar.h"
#include "pqViewManager.h"

QT_BEGIN_NAMESPACE

class Ui_pqClientMainWindow
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    pqViewManager *MultiViewManager;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menuFilters;
    pqStatusBar *statusbar;
    QDockWidget *pipelineBrowserDock;
    pqPipelineBrowserWidget *pipelineBrowser;
    QDockWidget *colorMapEditorDock;
    pqColorMapEditor *colorMapEditorPanel;
    QDockWidget *proxyTabDock;
    pqPropertiesPanel *proxyTabWidget;

    void setupUi(QMainWindow *pqClientMainWindow)
    {
        if (pqClientMainWindow->objectName().isEmpty())
            pqClientMainWindow->setObjectName(QString::fromUtf8("pqClientMainWindow"));
        pqClientMainWindow->resize(970, 700);
        actionOpen = new QAction(pqClientMainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(pqClientMainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(pqClientMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        MultiViewManager = new pqViewManager(centralwidget);
        MultiViewManager->setObjectName(QString::fromUtf8("MultiViewManager"));

        gridLayout->addWidget(MultiViewManager, 0, 0, 1, 1);

        pqClientMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pqClientMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 970, 19));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuFilters = new QMenu(menubar);
        menuFilters->setObjectName(QString::fromUtf8("menuFilters"));
        pqClientMainWindow->setMenuBar(menubar);
        statusbar = new pqStatusBar(pqClientMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        pqClientMainWindow->setStatusBar(statusbar);
        pipelineBrowserDock = new QDockWidget(pqClientMainWindow);
        pipelineBrowserDock->setObjectName(QString::fromUtf8("pipelineBrowserDock"));
        pipelineBrowserDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        pipelineBrowser = new pqPipelineBrowserWidget();
        pipelineBrowser->setObjectName(QString::fromUtf8("pipelineBrowser"));
        pipelineBrowser->setContextMenuPolicy(Qt::DefaultContextMenu);
        pipelineBrowserDock->setWidget(pipelineBrowser);
        pqClientMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pipelineBrowserDock);
        colorMapEditorDock = new QDockWidget(pqClientMainWindow);
        colorMapEditorDock->setObjectName(QString::fromUtf8("colorMapEditorDock"));
        colorMapEditorDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        colorMapEditorPanel = new pqColorMapEditor();
        colorMapEditorPanel->setObjectName(QString::fromUtf8("colorMapEditorPanel"));
        colorMapEditorDock->setWidget(colorMapEditorPanel);
        pqClientMainWindow->addDockWidget(Qt::RightDockWidgetArea, colorMapEditorDock);
        proxyTabDock = new QDockWidget(pqClientMainWindow);
        proxyTabDock->setObjectName(QString::fromUtf8("proxyTabDock"));
        proxyTabDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        proxyTabWidget = new pqPropertiesPanel();
        proxyTabWidget->setObjectName(QString::fromUtf8("proxyTabWidget"));
        proxyTabDock->setWidget(proxyTabWidget);
        pqClientMainWindow->addDockWidget(Qt::LeftDockWidgetArea, proxyTabDock);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menuFilters->menuAction());
        menu_File->addAction(actionOpen);
        menu_File->addAction(actionExit);

        retranslateUi(pqClientMainWindow);

        QMetaObject::connectSlotsByName(pqClientMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *pqClientMainWindow)
    {
        pqClientMainWindow->setWindowTitle(QCoreApplication::translate("pqClientMainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("pqClientMainWindow", "Open", nullptr));
        actionExit->setText(QCoreApplication::translate("pqClientMainWindow", "Quit", nullptr));
        menu_File->setTitle(QCoreApplication::translate("pqClientMainWindow", "&File", nullptr));
        menuFilters->setTitle(QCoreApplication::translate("pqClientMainWindow", "&Filters", nullptr));
        pipelineBrowserDock->setWindowTitle(QCoreApplication::translate("pqClientMainWindow", "Pipeline Browser", nullptr));
        colorMapEditorDock->setWindowTitle(QCoreApplication::translate("pqClientMainWindow", "Color Map Editor", nullptr));
        proxyTabDock->setWindowTitle(QCoreApplication::translate("pqClientMainWindow", "Properties", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pqClientMainWindow: public Ui_pqClientMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYMAINWINDOW_H
