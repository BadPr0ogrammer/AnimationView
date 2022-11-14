// ***************** DO NOT EDIT ***********************************
// This is a generated file.
// It will be replaced next time you rebuild.
/*=========================================================================

   Program: simple_paraview
   Module:  pqsimple_paraviewInitializer.cxx

   Copyright (c) 2005-2008 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

=========================================================================*/
#include "pqsimple_paraviewInitializer.h"

#include <QApplication>
#include <QBitmap>
#include <QDir>
#include <QSplashScreen>
#include <QtDebug>

#include "myMainWindow.h"

#include "pqPVApplicationCore.h"
#include "pqPluginManager.h"
#include "pqQtDeprecated.h"
#include "pqSettings.h"
#include "vtkSmartPointer.h"
#include "vtkRemotingCoreConfiguration.h"
#include "vtkSMProxyManager.h"
#include "vtkPVLogger.h"
#include "vtkPVPluginLoader.h"
#include "vtkPVPluginTracker.h"
#include "vtksys/SystemTools.hxx"

#define _paraview_client_APPLICATION_XMLS 1
#define _paraview_client_SPLASH_IMAGE 0
#define _paraview_client_TITLE 1
#define _paraview_client_built_shared 1

//-----------------------------------------------------------------------------
pqsimple_paraviewInitializer::pqsimple_paraviewInitializer()
{
  this->PVApp = nullptr;
  this->MainWindow = nullptr;
  this->Splash = nullptr;
}

//-----------------------------------------------------------------------------
pqsimple_paraviewInitializer::~pqsimple_paraviewInitializer()
{
  delete this->Splash;
  this->Splash = nullptr;

  delete this->MainWindow;
  this->MainWindow = nullptr;

  delete this->PVApp;
  this->PVApp = nullptr;
}

//-----------------------------------------------------------------------------
pqsimple_paraviewInitializer::Status pqsimple_paraviewInitializer::Initialize(int argc, char* argv[])
{
  try
  {
    vtkVLogScopeF(PARAVIEW_LOG_APPLICATION_VERBOSITY(), "initialize pqPVApplicationCore");
    this->PVApp = new pqPVApplicationCore (argc, argv);
  }
  catch (const pqApplicationCoreExitCode& exitCode)
  {
    return exitCode.code() == EXIT_SUCCESS ? ExitSuccess : ExitFailure;
  }

  // Attach custom event filter
  QApplication::instance()->installEventFilter(this->PVApp);

#if !_paraview_client_built_shared
  Q_INIT_RESOURCE(simple_paraview_configuration);

#endif

#if _paraview_client_SPLASH_IMAGE
  pqSettings *settings = this->PVApp->settings();
  auto coreConfig = vtkRemotingCoreConfiguration::GetInstance();
  if (!coreConfig->GetDisableRegistry() &&
    settings->value("GeneralSettings.ShowSplashScreen", true).toBool())
  {
    // Create and show the splash screen as the main window is being created.
    QPixmap pixmap("");
    this->Splash = new QSplashScreen(pixmap, Qt::WindowStaysOnTopHint);
    this->Splash->setMask(pixmap.createMaskFromColor(QColor(Qt::transparent)));
    this->Splash->show();
  }
#endif

  // Create main window.
  vtkVLogStartScopeF(PARAVIEW_LOG_APPLICATION_VERBOSITY(), "create-window",
      "creating main window `myMainWindow`");
  this->MainWindow = new myMainWindow();
  vtkLogEndScope("create-window");

  // load distributed plugins configuration.
  vtkVLogStartScopeF(PARAVIEW_LOG_PLUGIN_VERBOSITY(), "app-plugins", "load `simple_paraview` plugin conf");
  vtkPVPluginTracker::GetInstance()->LoadPluginConfigurationXMLs("simple_paraview");
  vtkLogEndScope("app-plugins");

  vtkNew<vtkPVPluginLoader> loader;

  // Load required application plugins.
  vtkVLogStartScopeF(PARAVIEW_LOG_PLUGIN_VERBOSITY(), "req-plugins", "load required plugins: `SimpleParaViewCustomFilters`");
  QString plugin_string = "SimpleParaViewCustomFilters";
  QStringList plugin_list = plugin_string.split(';',PV_QT_SKIP_EMPTY_PARTS);
  Q_FOREACH (const QString plugin_name, plugin_list)
  {
    if (!loader->LoadPluginByName(plugin_name.toUtf8().data()))
    {
      std::cerr << "warning: failed to load required plugin "
        << plugin_name.toUtf8().data() << std::endl;
    }
  }
  vtkLogEndScope("req-plugins");

  // Load optional plugins.
  vtkVLogStartScopeF(PARAVIEW_LOG_PLUGIN_VERBOSITY(), "opt-plugins", "load optional plugins: ``");
  plugin_string = "";
  plugin_list = plugin_string.split(';', PV_QT_SKIP_EMPTY_PARTS);
  Q_FOREACH (const QString plugin_name, plugin_list)
  {
    if (!loader->LoadPluginByName(plugin_name.toUtf8().data()))
    {
      std::cerr << "info: failed to load optional plugin "
        << plugin_name.toUtf8().data() << std::endl;
    }
  }
  vtkLogEndScope("opt-plugins");

  // now load plugins based on user-preferences.
  vtkVLogStartScopeF(PARAVIEW_LOG_PLUGIN_VERBOSITY(), "ini-plugins", "load plugins from settings");
  this->PVApp->getPluginManager()->loadPluginsFromSettings();
  vtkLogEndScope("ini-plugins");

#if _paraview_client_APPLICATION_XMLS
  // Load configuration xmls after all components have been instantiated.
  // This configuration part is something that needs to be cleaned up, I haven't
  // given this too much thought.
  QDir dir2(":/simple_paraview/Configuration");
  QStringList files = dir2.entryList(QDir::Files);
  Q_FOREACH (QString file, files)
  {
    this->PVApp->loadConfiguration(QString(":/simple_paraview/Configuration/") + file);
  }
#else
  // NO XMLS provided, Reader and Writers still needs to be updated
  this->PVApp->updateAvailableReadersAndWriters();
#endif

#if _paraview_client_TITLE
  this->MainWindow->setWindowTitle("Simple ParaView");
#endif

  // the user can specify a different window title by setting the PARAVIEW_WINDOW_TITLE
  // environment variable. This helps when using multiple PV GUIs simultaneously
  // and context switching quickly between them.
  if (const char* newWindowTitle = vtksys::SystemTools::GetEnv("PARAVIEW_WINDOW_TITLE"))
  {
    this->MainWindow->setWindowTitle(newWindowTitle);
  }

  // Fire the signal that the initialization is complete.
  this->PVApp->_paraview_client_environment_complete();

  // We used to call processEvents() here. We removed it, since that results in
  // timers (esp. pqCommandLineOptionsBehavior::playTests(), or
  // pqServer::processServerNotification()) timers could timeout here and that
  // causes test failures. Any case, the UI will update when the main event loop
  // resumes hence these processEvents are fairly useless.
  this->MainWindow->show();
  if (this->Splash)
  {
    this->Splash->finish(this->MainWindow);
  }
  return RunApplication;
}
