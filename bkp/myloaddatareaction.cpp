#include "myloaddatareaction.h"

#include <QSet>

#include "pqActiveObjects.h"
#include "pqApplicationCore.h"
#include "pqDataRepresentation.h"
#include "pqObjectBuilder.h"
#include "pqPipelineSource.h"

#include "vtkSMViewProxy.h"
#include "vtkSMSession.h"
#include "vtkSMSessionProxyManager.h"
#include "vtkSMParaViewPipelineController.h"
#include "vtkSMReaderFactory.h"
#include "vtkSMProxyManager.h"
#include "vtkSMPluginManager.h"

myLoadDataReaction::myLoadDataReaction(QAction* parentObject)
  : Superclass(parentObject)
{
}

void myLoadDataReaction::onTriggered()
{
  vtkSMSession* session = vtkSMSession::New();
  vtkSMReaderFactory* readerFactory = vtkSMProxyManager::GetProxyManager()->GetReaderFactory();
  const char* p = readerFactory->GetSupportedFileTypes(session);



  ReaderSet readerSet{ { "sources", "PVDReader" } };//XMLUnstructuredGridReader
  QList<pqPipelineSource*> sources = pqLoadDataReaction::loadData(readerSet);

  Q_FOREACH (pqPipelineSource* source, sources)
  {
    Q_EMIT this->loadedData(source);
  }
}

/*
    vtkNew<vtkSMParaViewPipelineController> controller;

    vtkSMSessionProxyManager* pxm = session->GetSessionProxyManager();
    if (!controller->InitializeSession(session)) {
      cerr << "Failed to initialize ParaView session." << endl;
      return;
    }
    if (controller->FindTimeKeeper(session) == nullptr) {
      cerr << "Failed at line " << __LINE__ << endl;
      return;
    }
    if (controller->FindAnimationScene(session) == nullptr){
      cerr << "Failed at line " << __LINE__ << endl;
      return;
    }
    if (controller->GetTimeAnimationTrack(controller->GetAnimationScene(session)) == nullptr) {
      cerr << "Failed at line " << __LINE__ << endl;
      return;
    }

    vtkSmartPointer<vtkSMProxy> reader;
    reader.loTakeReference(pxm->NewProxy("sources", "XMLUnstructuredGridReader"));
    controller->PreInitializeProxy(reader);

int TestParaViewPipelineController(int argc, char* argv[])
{
  (void)argc;
  vtkInitializationHelper::Initialize(argv[0], vtkProcessModule::PROCESS_CLIENT);

  vtkNew<vtkSMParaViewPipelineController> controller;

  // Create a new session.
  vtkSMSession* session = vtkSMSession::New();
  vtkSMSessionProxyManager* pxm = session->GetSessionProxyManager();
  if (!controller->InitializeSession(session))
  {
    cerr << "Failed to initialize ParaView session." << endl;
    return EXIT_FAILURE;
  }

  if (controller->FindTimeKeeper(session) == nullptr)
  {
    cerr << "Failed at line " << __LINE__ << endl;
    return EXIT_FAILURE;
  }

  if (controller->FindAnimationScene(session) == nullptr)
  {
    cerr << "Failed at line " << __LINE__ << endl;
    return EXIT_FAILURE;
  }

  if (controller->GetTimeAnimationTrack(controller->GetAnimationScene(session)) == nullptr)
  {
    cerr << "Failed at line " << __LINE__ << endl;
    return EXIT_FAILURE;
  }

  {
    // Create reader.
    vtkSmartPointer<vtkSMProxy> exodusReader;
    exodusReader.TakeReference(pxm->NewProxy("sources", "ExodusIIReader"));

    controller->PreInitializeProxy(exodusReader);

    char* fname = vtkTestUtilities::ExpandDataFileName(argc, argv, "Testing/Data/can.ex2");
    vtkSMPropertyHelper(exodusReader, "FileName").Set(fname);
    delete[] fname;

    vtkSMPropertyHelper(exodusReader, "ApplyDisplacements").Set(0);
    exodusReader->UpdateVTKObjects();

    controller->PostInitializeProxy(exodusReader);
    controller->RegisterPipelineProxy(exodusReader);

    // Create view
    vtkSmartPointer<vtkSMProxy> view;
    view.TakeReference(pxm->NewProxy("views", "RenderView"));
    controller->PreInitializeProxy(view);
    controller->PostInitializeProxy(view);
    controller->RegisterViewProxy(view);

    // Create display.
    vtkSmartPointer<vtkSMProxy> repr;
    repr.TakeReference(
      vtkSMViewProxy::SafeDownCast(view)->CreateDefaultRepresentation(exodusReader, 0));
    controller->PreInitializeProxy(repr);
    vtkSMPropertyHelper(repr, "Input").Set(exodusReader);
    controller->PostInitializeProxy(repr);
    controller->RegisterRepresentationProxy(repr);

    vtkSMPropertyHelper(view, "Representations").Add(repr);
    view->UpdateVTKObjects();
  }

  char* tempDir =
    vtkTestUtilities::GetArgOrEnvOrDefault("-T", argc, argv, "VTK_TEMP_DIR", "Testing/Temporary");
  if (!tempDir)
  {
    cerr << "Could not determine temporary directory.\n";
    return EXIT_FAILURE;
  }
  std::string path = tempDir;
  path += "/state.pvsm";
  pxm->SaveXMLState(path.c_str());
  delete[] tempDir;
  session->Delete();
  vtkInitializationHelper::Finalize();
  return EXIT_SUCCESS;
}

 *
 *
 *
  pqServer* server = pqActiveObjects::instance().activeServer();
  pqApplicationCore* core = pqApplicationCore::instance();
  pqObjectBuilder* builder = core->getObjectBuilder();
  pqServerManagerModel* smmodel = core->getServerManagerModel();

  if (!pqSourcesMenuReaction::warnOnCreate(xmlgroup, xmlname))
  {
    return nullptr;
  }

  vtkSMSessionProxyManager* pxm = server->proxyManager();
  vtkSMProxy* prototype = pxm->GetPrototypeProxy(xmlgroup.toUtf8().data(), xmlname.toUtf8().data());
  if (!prototype)
  {
    qCritical() << "Unknown proxy type: " << xmlname;
    return nullptr;
  }

  // Get the list of selected sources.
  QMap<QString, QList<pqOutputPort*>> namedInputs;
  QList<pqOutputPort*> selectedOutputPorts;

  vtkSMProxySelectionModel* selModel = pqActiveObjects::instance().activeSourcesSelectionModel();
  // Determine the list of selected output ports.
  for (unsigned int cc = 0; cc < selModel->GetNumberOfSelectedProxies(); cc++)
  {
    pqServerManagerModelItem* item =
      smmodel->findItem<pqServerManagerModelItem*>(selModel->GetSelectedProxy(cc));

    pqOutputPort* opPort = qobject_cast<pqOutputPort*>(item);
    pqPipelineSource* source = qobject_cast<pqPipelineSource*>(item);
    if (opPort)
    {
      selectedOutputPorts.push_back(opPort);
    }
    else if (source)
    {
      selectedOutputPorts.push_back(source->getOutputPort(0));
    }
  }

  QList<const char*> inputPortNames = pqPipelineFilter::getInputPorts(prototype);
  namedInputs[inputPortNames[0]] = selectedOutputPorts;

  // If the filter has more than 1 input ports, we are simply going to ask the
  // user to make selection for the inputs for each port. We may change that in
  // future to be smarter.
  if (pqPipelineFilter::getRequiredInputPorts(prototype).size() > 1)
  {
    vtkSMProxy* filterProxy = pxm->GetPrototypeProxy("filters", xmlname.toUtf8().data());
    vtkSMPropertyHelper helper(filterProxy, inputPortNames[0]);
    helper.RemoveAllValues();

    Q_FOREACH (pqOutputPort* outputPort, selectedOutputPorts)
    {
      helper.Add(outputPort->getSource()->getProxy(), outputPort->getPortNumber());
    }

    pqChangeInputDialog dialog(filterProxy, pqCoreUtilities::mainWidget());
    dialog.setObjectName("SelectInputDialog");
    if (QDialog::Accepted != dialog.exec())
    {
      helper.RemoveAllValues();
      // User aborted creation.
      return nullptr;
    }
    helper.RemoveAllValues();
    namedInputs = dialog.selectedInputs();
  }

  BEGIN_UNDO_SET(QString("Create '%1'").arg(xmlname));
  pqPipelineSource* filter = builder->createFilter("filters", xmlname, namedInputs, server);
  END_UNDO_SET();
  return filter;

void pqSLACDataLoadManager::setupPipeline()
{
  pqApplicationCore* core = pqApplicationCore::instance();
  pqObjectBuilder* builder = core->getObjectBuilder();
  vtkNew<vtkSMParaViewPipelineControllerWithRendering> controller;

  pqSLACManager* manager = pqSLACManager::instance();

  BEGIN_UNDO_SET("SLAC Data Load");

  // Determine the views.  Do this before deleting existing pipeline objects.
  pqView* meshView = manager->getMeshView();

  // Delete existing pipeline objects.  We will replace them.
  manager->destroyPipelineSourceAndConsumers(manager->getMeshReader());
  manager->destroyPipelineSourceAndConsumers(manager->getParticlesReader());

  QStringList meshFiles = this->ui->meshFile->filenames();
  // This should never really be not empty.
  if (!meshFiles.isEmpty())
  {
    pqSLACManager::instance()->loaderCreatingPipeline();
    pqPipelineSource* meshReader =
      builder->createReader("sources", "SLACReader", meshFiles, this->Server);

    vtkSMSourceProxy* meshReaderProxy = vtkSMSourceProxy::SafeDownCast(meshReader->getProxy());

    // Set up mode (if any).
    QStringList modeFiles = this->ui->modeFile->filenames();
    pqSMAdaptor::setFileListProperty(meshReaderProxy->GetProperty("ModeFileName"), modeFiles);

    // Push changes to server so that when the representation gets updated,
    // it uses the property values we set.
    meshReaderProxy->UpdateVTKObjects();

    // ensures that new timestep range, if any gets fetched from the server.
    meshReaderProxy->UpdatePipelineInformation();

    // ensures that the FrequencyScale and PhaseShift have correct default
    // values.
    meshReaderProxy->GetProperty("FrequencyScale")
      ->Copy(meshReaderProxy->GetProperty("FrequencyScaleInfo"));
    meshReaderProxy->GetProperty("PhaseShift")
      ->Copy(meshReaderProxy->GetProperty("PhaseShiftInfo"));

    // Make representations.
    controller->Show(meshReaderProxy, 0, meshView->getViewProxy());
    controller->Show(meshReaderProxy, 1, meshView->getViewProxy());
    controller->Hide(
      meshReaderProxy, 1, meshView->getViewProxy()); // keeping what old code was doing.

    // We have already made the representations and pushed everything to the
    // server manager.  Thus, there is no state left to be modified.
    meshReader->setModifiedState(pqProxy::UNMODIFIED);
  }

  QStringList particlesFiles = this->ui->particlesFile->filenames();
  if (!particlesFiles.isEmpty())
  {
    pqPipelineSource* particlesReader =
      builder->createReader("sources", "SLACParticleReader", particlesFiles, this->Server);

    // Make representations.
    controller->Show(particlesReader->getSourceProxy(), 0, meshView->getViewProxy());
    controller->SetVisibility(particlesReader->getSourceProxy(), 0, meshView->getViewProxy(),
      manager->actionShowParticles()->isChecked()); // keeping what old code was doing.

    // We have already made the representations and pushed everything to the
    // server manager.  Thus, there is no state left to be modified.
    particlesReader->setModifiedState(pqProxy::UNMODIFIED);
  }

  END_UNDO_SET();
  Q_EMIT this->createdPipeline();
}

 */
