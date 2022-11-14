#include "myloaddatareaction.h"

#include <QSet>

#include "pqActiveObjects.h"
#include "pqApplicationCore.h"
#include "pqDataRepresentation.h"
#include "pqObjectBuilder.h"
#include "pqPipelineSource.h"
#include "pqFileDialog.h"
#include "pqCoreUtilities.h"
#include "pqSelectReaderDialog.h"

#include "vtkPVDReader.h"
#include "vtkStringList.h"

myLoadDataReaction::myLoadDataReaction(QAction* parentObject)
  : Superclass(parentObject)
{
}

void myLoadDataReaction::onTriggered()
{
    QList<pqPipelineSource*> sources = loadData();
    pqPipelineSource* source;
    foreach(source, sources)
    {
        Q_EMIT this->loadedData(source);
    }
}
