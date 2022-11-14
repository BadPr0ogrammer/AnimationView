#include "mymainwindow.h"

#include "ui_myMainWindow.h"

#include <pqApplicationCore.h>
#include <pqCategoryToolbarsBehavior.h>
#include <pqColorToolbar.h>
#include <pqDeleteReaction.h>
//#include <pqHelpReaction.h>
#include <pqLoadDataReaction.h>
#include <pqParaViewBehaviors.h>
#include <pqParaViewMenuBuilders.h>
#include <pqRepresentationToolbar.h>

#include "myloaddatareaction.h"

class myMainWindow::pqInternals : public Ui::myMainWindow
{
};

myMainWindow::myMainWindow()
  : Internals(new pqInternals())
{
  // Setup default GUI layout.
  this->Internals->setupUi(this);

  // Setup the dock window corners to give the vertical docks more room.
  this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

  // Setup color editor
  // Provide access to the color-editor panel for the application and hide it
  // b pqApplicationCore::instance()->registerManager("COLOR_EDITOR_PANEL", this->Internals->colorMapEditorDock);
  // b this->Internals->colorMapEditorDock->hide();

  // Create a custom file menu with only Open and close
  QList<QAction*> actionList = this->Internals->menu_File->actions();
  QAction* action = actionList.at(0);
  new myLoadDataReaction(action);
  QObject::connect(actionList.at(1), SIGNAL(triggered()), QApplication::instance(), SLOT(closeAllWindows()));

  // Build the filters menu
  pqParaViewMenuBuilders::buildFiltersMenu(*this->Internals->menuFilters, this);

  // Setup the context menu for the pipeline browser.
  // b pqParaViewMenuBuilders::buildPipelineBrowserContextMenu(*this->Internals->pipelineBrowser->contextMenu());

  // Add the ColorToolbar
  // b QToolBar* colorToolbar = new pqColorToolbar(this);
  // b colorToolbar->layout()->setSpacing(0);
  // b this->addToolBar(colorToolbar);

  // Add the Representation Toolbar
  // b QToolBar* reprToolbar = new pqRepresentationToolbar(this);
  // b reprToolbar->setObjectName("Representation");
  // b reprToolbar->layout()->setSpacing(0);
  // b this->addToolBar(reprToolbar);

  // Enable help from the properties panel.
  // This is not really working as the documentation is not built in this app
  //QObject::connect(this->Internals->proxyTabWidget, &pqPropertiesPanel::helpRequested,
    //&pqHelpReaction::showProxyHelp);

  // hook delete to pqDeleteReaction.
  // b QAction* tempDeleteAction = new QAction(this);
  // b pqDeleteReaction* handler = new pqDeleteReaction(tempDeleteAction);
  // b handler->connect(this->Internals->proxyTabWidget, SIGNAL(deleteRequested(pqProxy*)), SLOT(deleteSource(pqProxy*)));

  // Final step, define application behaviors. Since we want all ParaView
  // behaviors, we use this convenience method.
  new pqParaViewBehaviors(this, this);
}

myMainWindow::~myMainWindow() = default;
