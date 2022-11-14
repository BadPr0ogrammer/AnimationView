#include "ui_myMainWindow.h"
#include "mymainwindow.h"

#include <pqApplicationCore.h>
#include <pqCategoryToolbarsBehavior.h>
#include <pqColorToolbar.h>
#include <pqDeleteReaction.h>
//#include <pqHelpReaction.h>
#include <pqLoadDataReaction.h>
#include <pqParaViewBehaviors.h>
#include <pqParaViewMenuBuilders.h>
#include <pqRepresentationToolbar.h>

//#include "pqActiveObjects.h"
//#include "pqCoreUtilities.h"
#include "pqMainWindowEventManager.h"
//#include "pqParaViewBehaviors.h"
//#include "pqParaViewMenuBuilders.h"
//#include "pqSaveStateReaction.h"
//#include "pqSettings.h"
//#include "pqTimer.h"
//#include "pqWelcomeDialog.h"
//#include "vtkCommand.h"
//#include "vtkPVGeneralSettings.h"
//#include "vtkProcessModule.h"
//#include "vtkRemotingCoreConfiguration.h"
//#include "vtkSMSettings.h"

#include "pqParaViewBehaviors.h"
#include "pqAlwaysConnectedBehavior.h"
#include "pqApplicationCore.h"
#include "pqApplyBehavior.h"
#include "pqAutoLoadPluginXMLBehavior.h"
#include "pqBlockContextMenu.h"
#include "pqCollaborationBehavior.h"
#include "pqCommandLineOptionsBehavior.h"
#include "pqCoreTestUtility.h"
#include "pqCrashRecoveryBehavior.h"
#include "pqCustomShortcutBehavior.h"
#include "pqDataTimeStepBehavior.h"
#include "pqDefaultViewBehavior.h"
#include "pqFileDialogFavoriteModel.h"
#include "pqInterfaceTracker.h"
#include "pqLiveSourceBehavior.h"
#include "pqLockPanelsBehavior.h"
#include "pqMainWindowEventBehavior.h"
#include "pqObjectPickingBehavior.h"
#include "pqPersistentMainWindowStateBehavior.h"
#include "pqPipelineContextMenuBehavior.h"
#include "pqPluginActionGroupBehavior.h"
#include "pqPluginDockWidgetsBehavior.h"
#include "pqPluginSettingsBehavior.h"
#include "pqPluginToolBarBehavior.h"
#include "pqPropertiesPanel.h"
#include "pqServerManagerModel.h"
#include "pqSpreadSheetVisibilityBehavior.h"
#include "pqStandardPropertyWidgetInterface.h"
#include "pqStandardRecentlyUsedResourceLoaderImplementation.h"
#include "pqStandardViewFrameActionsImplementation.h"
#include "pqStreamingTestingEventPlayer.h"
#include "pqUndoRedoBehavior.h"
#include "pqUndoStack.h"
#include "pqUsageLoggingBehavior.h"
#include "pqVerifyRequiredPluginBehavior.h"
#include "pqViewStreamingBehavior.h"

#include "vtkPVPluginLoader.h"

#include "myloaddatareaction.h"

class myMainWindow::pqInternals : public Ui::pqClientMainWindow
{
};

//-----------------------------------------------------------------------------
myMainWindow::myMainWindow()
  : Internals(new pqInternals())
{
  // Setup default GUI layout.
  this->Internals = new pqInternals();
  this->Internals->setupUi(this);

  // Setup the dock window corners to give the vertical docks more room.
  this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

  // Setup color editor
  // Provide access to the color-editor panel for the application and hide it
  pqApplicationCore::instance()->registerManager("COLOR_EDITOR_PANEL", this->Internals->colorMapEditorDock);
  this->Internals->colorMapEditorDock->hide();

  // Create a custom file menu with only Open and close
  QList<QAction*> actionList = this->Internals->menu_File->actions();
  QAction* action = actionList.at(0);
  new myLoadDataReaction(action);
  QObject::connect(actionList.at(1), SIGNAL(triggered()), QApplication::instance(), SLOT(closeAllWindows()));

  // Build the filters menu
  pqParaViewMenuBuilders::buildFiltersMenu(*this->Internals->menuFilters, this);

  // Setup the context menu for the pipeline browser.
  pqParaViewMenuBuilders::buildPipelineBrowserContextMenu(*this->Internals->pipelineBrowser->contextMenu());

  // Add the ColorToolbar
  QToolBar* colorToolbar = new pqColorToolbar(this);
  colorToolbar->layout()->setSpacing(0);
  this->addToolBar(colorToolbar);

  // Add the Representation Toolbar
  QToolBar* reprToolbar = new pqRepresentationToolbar(this);
  reprToolbar->setObjectName("Representation");
  reprToolbar->layout()->setSpacing(0);
  this->addToolBar(reprToolbar);

  // Enable help from the properties panel.
  // This is not really working as the documentation is not built in this app
  //QObject::connect(this->Internals->proxyTabWidget, &pqPropertiesPanel::helpRequested, &pqHelpReaction::showProxyHelp);

  // hook delete to pqDeleteReaction.
  QAction* tempDeleteAction = new QAction(this);
  pqDeleteReaction* handler = new pqDeleteReaction(tempDeleteAction);
  handler->connect(this->Internals->proxyTabWidget, SIGNAL(deleteRequested(pqProxy*)), SLOT(deleteSource(pqProxy*)));

  // Final step, define application behaviors. Since we want all ParaView
  // behaviors, we use this convenience method.
  new pqParaViewBehaviors(this, this);

  vtkNew<vtkPVPluginLoader> loader;
  if (!loader->LoadPluginByName("GeomOptFilter")) {

  }
}

myMainWindow::~myMainWindow() = default;
//vtkRemotingApplication.lib;vtkRemotingServerManager.lib;vtkRemotingCore.lib;vtkPVVTKExtensionsCore-pv5.10.lib;
//pqCore-pv5.10.lib;pqComponents-pv5.10.lib;pqWidgets-pv5.10.lib;pqApplicationComponents-pv5.10.lib;
//GeneratedFiles\$(ConfigurationName);GeneratedFiles;.;..\paraview\build\Clients\ParaView;..\paraview\build\VTKExtensions\IOCore;..\paraview\VTKExtensions\IOCore;..\paraview\build\VTK\Rendering\Context2D;..\paraview\VTK\Rendering\Context2D;..\paraview\build\VTK\Charts\Core;..\paraview\VTK\Charts\Core;..\paraview\build\Qt\ApplicationComponents;..\paraview\Qt\ApplicationComponents;..\paraview\build\Qt\Core;..\paraview\Qt\Core;..\paraview\build\Qt\Components;../paraview/build/Qt/Components/pqComponents_autogen/include;..\paraview\Qt\Components;..\paraview\build\Qt\Widgets;..\paraview\Qt\Widgets;../paraview/build/Qt/Core/pqCore_autogen/include;..\paraview\build\Remoting\Core;..\paraview\Remoting\Core;..\paraview\build\Remoting\ClientServerStream;..\paraview\Remoting\ClientServerStream;..\paraview\build\Remoting\ServerManager;..\paraview\Remoting\ServerManager;..\paraview\build\VTKExtensions\Core;..\paraview\VTKExtensions\Core;..\paraview\build\VTK\ThirdParty\cli11;..\paraview\VTK\ThirdParty\cli11;..\paraview\build\ThirdParty\QtTesting\vtkqttesting;..\paraview\ThirdParty\QtTesting\vtkqttesting;..\paraview\build\Remoting\Settings;..\paraview\Remoting\Settings;..\paraview\build\Remoting\Views;..\paraview\Remoting\Views;..\paraview\build\Remoting\Application;..\paraview\Remoting\Application;..\paraview\Remoting\Animation;..\paraview\build\Remoting\Misc;..\paraview\Remoting\Misc;..\paraview\build\Remoting\Animation;..\paraview\build\VTKExtensions\FiltersRendering;..\paraview\VTKExtensions\FiltersRendering;..\paraview\build\VTKExtensions\Extraction;..\paraview\VTKExtensions\Extraction;..\paraview\build\VTKExtensions\Misc;..\paraview\VTKExtensions\Misc;..\paraview\VTK\ThirdParty\doubleconversion;../paraview/build/ThirdParty/VTK/ThirdParty/doubleconversion/vtkdoubleconversion;..\paraview\build\VTK\Rendering\Parallel;..\paraview\VTK\Rendering\Parallel;..\paraview\VTK\Rendering\Volume;..\paraview\build\VTKExtensions\InteractionStyle;..\paraview\VTKExtensions\InteractionStyle;..\paraview\build\VTK\Filters\ParallelDIY2;..\paraview\VTK\Filters\ParallelDIY2;..\paraview\build\CMakeFiles\paraview_client_server;..\paraview\build\CMakeFiles\paraview_server_manager;..\paraview\build\VTK\Rendering\Core;..\paraview\VTK\Rendering\Core;..\paraview\build\VTK\Common\Core;..\paraview\VTK\Common\Core;..\paraview\VTK\ThirdParty\lz4\vtklz4\lib;..\paraview\build\VTK\Filters\Core;..\paraview\VTK\Filters\Core;..\paraview\VTK\Utilities\KWIML;..\paraview\VTK\Common\DataModel;..\paraview\build\VTK\IO\XML;..\paraview\VTK\IO\XML;..\paraview\build\VTK\Rendering\Annotation;..\paraview\VTK\Rendering\Annotation;..\paraview\build\VTK\Common\DataModel;..\paraview\build\VTK\GUISupport\Qt;..\paraview\VTK\GUISupport\Qt;..\paraview\build\VTK\Common\ExecutionModel;..\paraview\VTK\Common\ExecutionModel;..\paraview\build\VTK\Common\Color;..\paraview\VTK\Common\Color;..\paraview\build\VTK\Common\Math;..\paraview\VTK\Common\Math;..\paraview\build\VTK\Interaction\Style;..\paraview\VTK\Interaction\Style;..\paraview\build\VTK\Rendering\Image;..\paraview\VTK\Rendering\Image;..\paraview\build\VTK\Interaction\Widgets;..\paraview\VTK\Interaction\Widgets;..\paraview\build\VTK\Rendering\OpenGL2;..\paraview\VTK\Rendering\OpenGL2;..\paraview\build\VTK\Common\Transforms;..\paraview\VTK\Common\Transforms;..\paraview\build\VTK\Rendering\UI;..\paraview\VTK\Rendering\UI;..\paraview\build\VTK\Imaging\Core;..\paraview\VTK\Imaging\Core;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5\QtWidgets;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5\QtGui;..\VCPKG\INSTALLED\X64-WINDOWS\include\qt5\QtCore;debug;%(AdditionalIncludeDirectories)
/*
pqParaViewBehaviors::setEnableAddExamplesInFavoritesBehavior     (false);
  pqParaViewBehaviors::setEnableAlwaysConnectedBehavior           (true);
  pqParaViewBehaviors::setEnableApplyBehavior                     (true);
  pqParaViewBehaviors::setEnableAutoLoadPluginXMLBehavior         (true);
  pqParaViewBehaviors::setEnableBlockContentMenu                   (false);
  pqParaViewBehaviors::setEnableCollaborationBehavior             (true);
  pqParaViewBehaviors::setEnableCommandLineOptionsBehavior        (true);
  pqParaViewBehaviors::setEnableCrashRecoveryBehavior             (true);
  pqParaViewBehaviors::setEnableCustomShortcutBehavior            (true);
  pqParaViewBehaviors::setEnableDataTimeStepBehavior              (true);
  pqParaViewBehaviors::setEnableDefaultViewBehavior                (false);
  pqParaViewBehaviors::setEnableLiveSourceBehavior                (true);
  pqParaViewBehaviors::setEnableLockPanelsBehavior                (true);
  pqParaViewBehaviors::setEnableMainWindowEventBehavior           (true);
  pqParaViewBehaviors::setEnableObjectPickingBehavior              (false);
  pqParaViewBehaviors::setEnablePersistentMainWindowStateBehavior  (false);
  pqParaViewBehaviors::setEnablePipelineContextMenuBehavior        (false);
  pqParaViewBehaviors::setEnablePluginActionGroupBehavior         (true);
  pqParaViewBehaviors::setEnablePluginDockWidgetsBehavior         (true);
  pqParaViewBehaviors::setEnablePluginSettingsBehavior            (true);
  pqParaViewBehaviors::setEnablePluginToolBarBehavior             (true);
  pqParaViewBehaviors::setEnablePythonShellResetBehavior           (false);
  pqParaViewBehaviors::setEnableQuickLaunchShortcuts              (true);
  pqParaViewBehaviors::setEnableSpreadSheetVisibilityBehavior      (false);
  pqParaViewBehaviors::setEnableStandardPropertyWidgets           (true);
  pqParaViewBehaviors::setEnableStandardRecentlyUsedResourceLoader (false);
  pqParaViewBehaviors::setEnableStandardViewFrameActions          (true);
  pqParaViewBehaviors::setEnableUndoRedoBehavior                   (false);
  pqParaViewBehaviors::setEnableUsageLoggingBehavior              (true);
  pqParaViewBehaviors::setEnableVerifyRequiredPluginBehavior      (true);
  pqParaViewBehaviors::setEnableWheelNeedsFocusBehavior           (true);
*/