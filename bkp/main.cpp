#include <QApplication>
#include <QStyleFactory>

#include "QVTKRenderWidget.h"
#include <pqPVApplicationCore.h>

#include "mymainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    pqPVApplicationCore appCore(argc, argv);

    myMainWindow w;
    w.show();

    return app.exec();
}

/*
 *
    setlocale(LC_NUMERIC, "C");
    QSurfaceFormat::setDefaultFormat(QVTKRenderWidget::defaultFormat());


      //QApplication::setStyle("fusion");
#include <QApplication>
#include <QStyleFactory>

#include "QVTKRenderWidget.h"

#include "vtuanimationview.h"

int main(int argc, char *argv[])
{
    setlocale(LC_NUMERIC, "C");
    QSurfaceFormat::setDefaultFormat(QVTKRenderWidget::defaultFormat());

    QApplication a(argc, argv);
    QApplication::setStyle("fusion");

    VtuAnimationView w;
    w.show();

    return a.exec();
}
/*

void pqDefaultViewBehavior::showWarnings()
{
  using RCInfo = vtkPVRenderingCapabilitiesInformation;
  if (RCInfo::Supports(this->ClientCapabilities, RCInfo::OPENGL) &&
    RCInfo::Supports(this->ServerCapabilities, RCInfo::OPENGL))
  {
    // all's well!
    return;
  }

  if (this->Server == nullptr)
  {
    return;
  }

  if (!RCInfo::Supports(this->ClientCapabilities, RCInfo::OPENGL))
  {
    QString msg = tr("Your OpenGL drivers don't support\n"
                     "required OpenGL features for basic rendering.\n"
                     "Application cannot continue. Please exit and use an older version.\n\n"
                     "CONTINUE AT YOUR OWN RISK!\n\n");
    msg += openGLVersionInfo(this->Server->session(), vtkSMSession::CLIENT);
    QMessageBox::warning(
      pqCoreUtilities::mainWidget(), tr("OpenGL support inadequate!"), msg, QMessageBox::Ok);
    return;
  }


//-----------------------------------------------------------------------------
void pqInterfaceTracker::initialize()
{
  vtkPVPluginTracker* tracker = vtkPVPluginTracker::GetInstance();

  // Process any already loaded plugins. These are typically the plugins that
  // got autoloaded when the application started.
  for (unsigned int cc = 0; cc < tracker->GetNumberOfPlugins(); cc++)
  {
    this->onPluginLoaded(nullptr, 0, tracker->GetPlugin(cc));
  }
}

//-----------------------------------------------------------------------------
void pqInterfaceTracker::onPluginLoaded(vtkObject*, unsigned long, void* calldata)
{
  vtkPVPlugin* plugin = reinterpret_cast<vtkPVPlugin*>(calldata);
  vtkPVGUIPluginInterface* guiplugin = dynamic_cast<vtkPVGUIPluginInterface*>(plugin);
  if (guiplugin != nullptr)
  {
    QObjectList ifaces = guiplugin->interfaces();
    Q_FOREACH (QObject* iface, ifaces)
    {
      this->Interfaces.append(iface);
      Q_EMIT this->interfaceRegistered(iface);

      pqAutoStartInterface* asi = qobject_cast<pqAutoStartInterface*>(iface);
      if (asi)
      {
        asi->startup();
      }
    }
  }
}

//-----------------------------------------------------------------------------
void pqInterfaceTracker::addInterface(QObject* iface)
{
  if (!this->Interfaces.contains(iface) && !this->RegisteredInterfaces.contains(iface))
  {
    this->RegisteredInterfaces.push_back(iface);
    Q_EMIT this->interfaceRegistered(iface);

    pqAutoStartInterface* asi = qobject_cast<pqAutoStartInterface*>(iface);
    if (asi)
    {
      asi->startup();
    }
  }
}



class pqPluginManager::pqInternals
{
public:
  QSet<QString> LocalHiddenPlugins;
  QSet<QString> RemoteHiddenPlugins;
  QList<QPointer<pqServer>> Servers;

  QString getXML(vtkPVPluginsInformation* info, bool remote)
  {
    std::ostringstream stream;
    stream << "<?xml version=\"1.0\" ?>\n";
    stream << "<Plugins>\n";
    for (unsigned int cc = 0; cc < info->GetNumberOfPlugins(); cc++)
    {
      if ((remote && this->RemoteHiddenPlugins.contains(info->GetPluginFileName(cc))) ||
        (!remote && this->LocalHiddenPlugins.contains(info->GetPluginFileName(cc))))
      {
        continue;
      }

      stream << "  <Plugin name=\"" << info->GetPluginName(cc) << "\""
             << " filename=\"" << info->GetPluginFileName(cc) << "\""
             << " auto_load=\"" << (info->GetAutoLoad(cc) ? 1 : 0) << "\" />\n";
    }
    stream << "</Plugins>\n";
    // cout << stream.str().c_str() << endl;
    return QString(stream.str().c_str());
  }
};


// self include
#include "pqPropertyManager.h"

// Qt includes
#include <QApplication>
#include <QByteArray>
#include <QMultiMap>

// ParaView includes
#include "pqPropertyLinks.h"

//-----------------------------------------------------------------------------
pqPropertyManager::pqPropertyManager(QObject* p)
  : QObject(p)
{
  this->Links = new pqPropertyLinks();
  this->Links->setUseUncheckedProperties(true);
  this->Links->setAutoUpdateVTKObjects(false);
  QObject::connect(this->Links, SIGNAL(qtWidgetChanged()), this, SLOT(propertyChanged()));
  this->Modified = false;
}


//-----------------------------------------------------------------------------
class pqProxyInternal
{
public:
  pqProxyInternal() { this->Connection = vtkSmartPointer<vtkEventQtSlotConnect>::New(); }
  typedef QMap<QString, QList<vtkSmartPointer<vtkSMProxy>>> ProxyListsType;
  ProxyListsType ProxyLists;
  vtkSmartPointer<vtkSMProxy> Proxy;
  vtkSmartPointer<vtkEventQtSlotConnect> Connection;

  /// Returns true if the ProxyLists (the collection of helper proxies)
  /// contains the given proxy.
  bool containsHelperProxy(vtkSMProxy* aproxy, QString& key) const
  {
    for (ProxyListsType::const_iterator iter = this->ProxyLists.begin();
         iter != this->ProxyLists.end(); ++iter)
    {
      if (iter.value().contains(aproxy))
      {
        key = iter.key();
        return true;
      }
    }
    return false;
  }
};

//-----------------------------------------------------------------------------
pqProxy::pqProxy(const QString& group, const QString& name, vtkSMProxy* proxy, pqServer* server,
  QObject* _parent /*=nullptr)
  : pqServerManagerModelItem(_parent)
  , Server(server)
  , SMName(name)
  , SMGroup(group)
{
  this->Internal = new pqProxyInternal;
  this->Internal->Proxy = proxy;
  this->Modified = pqProxy::UNMODIFIED;
  this->UserModifiedSMName = false;
}



//----------------------------------------------------------------------------
pqQVTKWidget::pqQVTKWidget(QWidget* parentObject, Qt::WindowFlags f, bool isStereo)
  : Superclass(parentObject, f)
  , SizePropertyName("ViewSize")
  , useStereo(isStereo)
{
  auto* layout = new QVBoxLayout();
  layout->setMargin(0);

  if (useStereo)
  {
    auto ptr = new pqQVTKWidgetBase(parentObject, f);
    baseClass.setValue(ptr);
    layout->addWidget(ptr);

    vtkVLogF(PARAVIEW_LOG_APPLICATION_VERBOSITY(), "Using stereo-capable context.");
  }
  else
  {
    auto ptr = new QVTKOpenGLNativeWidget(parentObject, f);
    baseClass.setValue(ptr);
    layout->addWidget(ptr);

    vtkVLogF(PARAVIEW_LOG_APPLICATION_VERBOSITY(), "Using native-capable context.");
  }

  this->setLayout(layout);

  // disable HiDPI if we are running tests
  if (this->useStereo)
  {
    baseClass.value<pqQVTKWidgetBase*>()->setEnableHiDPI(
      vtksys::SystemTools::GetEnv("DASHBOARD_TEST_FROM_CTEST") ? false : true);
  }
  else
  {
    baseClass.value<QVTKOpenGLNativeWidget*>()->setEnableHiDPI(
      vtksys::SystemTools::GetEnv("DASHBOARD_TEST_FROM_CTEST") ? false : true);
  }





pqQVTKWidgetEventPlayer::pqQVTKWidgetEventPlayer(QObject* p)
  : pqWidgetEventPlayer(p)
{
}

bool pqQVTKWidgetEventPlayer::playEvent(
  QObject* Object, const QString& Command, const QString& Arguments, bool& Error)
{
  QVTKOpenGLStereoWidget* qvtkStereoWidget = qobject_cast<QVTKOpenGLStereoWidget*>(Object);
  QVTKOpenGLNativeWidget* qvtkNativeWidget = qobject_cast<QVTKOpenGLNativeWidget*>(Object);
  pqQVTKWidget* qvtkWidget = qobject_cast<pqQVTKWidget*>(Object);
  if (qvtkStereoWidget || qvtkNativeWidget || qvtkWidget)
  {
    if (Command == "mousePress" || Command == "mouseRelease" || Command == "mouseMove" ||
      Command == "mouseDblClick")
    {
      QRegExp mouseRegExp("\\(([^,]*),([^,]*),([^,]),([^,]),([^,]*)\\)");
      if (mouseRegExp.indexIn(Arguments) != -1)
      {
        QWidget* widget = qobject_cast<QWidget*>(Object);
        QVariant v = mouseRegExp.cap(1);
        int x = static_cast<int>(v.toDouble() * widget->size().width());
        v = mouseRegExp.cap(2);
        int y = static_cast<int>(v.toDouble() * widget->size().height());
        v = mouseRegExp.cap(3);
        Qt::MouseButton button = static_cast<Qt::MouseButton>(v.toInt());
        v = mouseRegExp.cap(4);
        Qt::MouseButtons buttons = static_cast<Qt::MouseButton>(v.toInt());
        v = mouseRegExp.cap(5);
        Qt::KeyboardModifiers keym = static_cast<Qt::KeyboardModifier>(v.toInt());

        QEvent::Type type = QEvent::None;
        if (Command == "mousePress")
        {
          type = QEvent::MouseButtonPress;
        }
        else if (Command == "mouseRelease")
        {
          type = QEvent::MouseButtonRelease;
        }
        else if (Command == "mouseMove")
        {
          type = QEvent::MouseMove;
        }
        else if (Command == "mouseDblClick")
        {
          type = QEvent::MouseButtonDblClick;
        }
        QMouseEvent e(type, QPoint(x, y), button, buttons, keym);

        if (qvtkStereoWidget != nullptr)
        {
          // Due to QTBUG-61836 (see QVTKOpenGLStereoWidget::testingEvent()), events should
          // be propagated back to the internal QVTKOpenGLWindow when being fired
          // explicitly on the widget instance. We have to use a custom event
          // callback in this case to ensure that events are passed to the window.
          qApp->notify(qvtkStereoWidget->embeddedOpenGLWindow(), &e);
        }

        if (qvtkNativeWidget != nullptr)
        {
          qApp->notify(qvtkNativeWidget, &e);
        }

        if (qvtkWidget != nullptr)
        {
          qvtkWidget->notifyQApplication(&e);
        }
      }
      return true;
    }
  }
  return this->Superclass::playEvent(Object, Command, Arguments, Error);
}


bool pqQVTKWidgetEventTranslator::translateEvent(
  QObject* Object, QEvent* Event, int eventType, bool& error)
{
  // Only translate events for QWidget subclasses that internally use a render
  // window
  QWidget* const widget = qobject_cast<QWidget*>(Object);
  if (!widget)
  {
    return false;
  }

  // Look for a render window in the possible widget types.
  vtkRenderWindow* rw = nullptr;

  if (QVTKOpenGLStereoWidget* const qvtkWidget = qobject_cast<QVTKOpenGLStereoWidget*>(Object))
  {
    rw = qvtkWidget->embeddedOpenGLWindow() ? qvtkWidget->renderWindow() : nullptr;
  }

  if (QVTKOpenGLNativeWidget* const qvtkNativeWidget =
        qobject_cast<QVTKOpenGLNativeWidget*>(Object))
  {
    rw = qvtkNativeWidget->renderWindow();
  }

  if (pqQVTKWidget* const qvtkWidget = qobject_cast<pqQVTKWidget*>(Object))
  {
    rw = qvtkWidget->renderWindow();
  }

  // Could not find a render window, don't translate the event
  if (rw == nullptr)
  {
    return false;
  }

  if (eventType == pqEventTypes::ACTION_EVENT)
  {
    switch (Event->type())
    {
      // ContextMenu are supported via mousePress
      case QEvent::ContextMenu:
      {
        return true;
        break;
      }
      case QEvent::MouseButtonPress:
      {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(Event);
        if (mouseEvent)
        {
          QSize size = widget->size();
          double normalized_x = mouseEvent->x() / static_cast<double>(size.width());
          double normalized_y = mouseEvent->y() / static_cast<double>(size.height());
          Q_EMIT recordEvent(widget, "mousePress",
            QString("(%1,%2,%3,%4,%5)")
              .arg(normalized_x)
              .arg(normalized_y)
              .arg(mouseEvent->button())
              .arg(mouseEvent->buttons())
              .arg(mouseEvent->modifiers()));
        }
        return true;
        break;
      }


class pqScalarsToColorsInternal
{
public:
  vtkEventQtSlotConnect* VTKConnect;

  pqScalarsToColorsInternal() { this->VTKConnect = vtkEventQtSlotConnect::New(); }
  ~pqScalarsToColorsInternal() { this->VTKConnect->Delete(); }
};

//-----------------------------------------------------------------------------
pqScalarsToColors::pqScalarsToColors(const QString& group, const QString& name, vtkSMProxy* proxy,
  pqServer* server, QObject* _parent /*=nullptr)
  : pqProxy(group, name, proxy, server, _parent)
{
  this->Internal = new pqScalarsToColorsInternal;

  this->Internal->VTKConnect->Connect(
    proxy->GetProperty("RGBPoints"), vtkCommand::ModifiedEvent, this, SLOT(checkRange()));
  this->Internal->VTKConnect->Connect(
    proxy->GetProperty("UseLogScale"), vtkCommand::ModifiedEvent, this, SLOT(checkRange()));
  if (vtkSMProperty* prop = proxy->GetProperty("VectorComponent"))
  {
    this->Internal->VTKConnect->Connect(
      prop, vtkCommand::ModifiedEvent, this, SIGNAL(componentOrModeChanged()));
  }
  if (vtkSMProperty* prop = proxy->GetProperty("VectorMode"))
  {
    this->Internal->VTKConnect->Connect(
      prop, vtkCommand::ModifiedEvent, this, SIGNAL(componentOrModeChanged()));
  }
}

//-----------------------------------------------------------------------------
pqScalarsToColors::~pqScalarsToColors()
{
  delete this->Internal;
}

//-----------------------------------------------------------------------------
pqScalarBarRepresentation* pqScalarsToColors::getScalarBar(pqRenderViewBase* ren) const
{
  vtkSMProxy* proxy =
    vtkSMTransferFunctionProxy::FindScalarBarRepresentation(this->getProxy(), ren->getProxy());
  pqServerManagerModel* smmodel = pqApplicationCore::instance()->getServerManagerModel();
  return proxy ? smmodel->findItem<pqScalarBarRepresentation*>(proxy) : nullptr;
}




pqSMAdaptor::PropertyType pqSMAdaptor::getPropertyType(vtkSMProperty* Property)



class pqTimeKeeper::pqInternals
{
public:
  vtkNew<vtkEventQtSlotConnect> VTKConnect;
};

//-----------------------------------------------------------------------------
pqTimeKeeper::pqTimeKeeper(const QString& group, const QString& name, vtkSMProxy* timekeeper,
  pqServer* server, QObject* _parent /*=0)
  : pqProxy(group, name, timekeeper, server, _parent)
{
  this->Internals = new pqInternals();
  this->Internals->VTKConnect->Connect(
    timekeeper->GetProperty("Time"), vtkCommand::ModifiedEvent, this, SIGNAL(timeChanged()));
  this->Internals->VTKConnect->Connect(timekeeper->GetProperty("TimestepValues"),
    vtkCommand::ModifiedEvent, this, SIGNAL(timeStepsChanged()));
  this->Internals->VTKConnect->Connect(timekeeper->GetProperty("TimestepValues"),
    vtkCommand::ModifiedEvent, this, SIGNAL(timeRangeChanged()));
  this->Internals->VTKConnect->Connect(timekeeper->GetProperty("TimeRange"),
    vtkCommand::ModifiedEvent, this, SIGNAL(timeRangeChanged()));
}



vtkPVGUIPluginInterface::~vtkPVGUIPluginInterface() = default;
 */
