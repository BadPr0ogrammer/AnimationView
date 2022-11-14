#include "GeomOptFilter.h"

#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkDataObject.h>
#include <vtkObjectFactory.h>
#include <vtkDemandDrivenPipeline.h>

#include <vtkDataSet.h>
#include <vtkPolyData.h>
#include <vtkPolygon.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkUnstructuredGrid.h >

#include <vtkIdList.h>
#include <vtkIdTypeArray.h>
#include <vtkDataArray.h>

#include <vtkSmartPointer.h>
#include <vtkMath.h>

using namespace std;

vtkStandardNewMacro(GeomOptFilter);

GeomOptFilter::GeomOptFilter()
{
	// by default, process active cell scalars
	this->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, vtkDataSetAttributes::SCALARS);
}

void GeomOptFilter::SetTagThreshold(const char* tag, double thr)
{
	m_tag = tag;
	m_thresh_val = thr;
}

GeomOptFilter::~GeomOptFilter()
{
}

int GeomOptFilter::RequestData(vtkInformation* vtkNotUsed(request),
	vtkInformationVector** inputVector, vtkInformationVector* outputVector)
{
	vtkInformation* inInfo = inputVector[0]->GetInformationObject(0);
	vtkInformation* outInfo = outputVector->GetInformationObject(0);

	vtkDataSet* input = vtkDataSet::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));
	vtkUnstructuredGrid* output = vtkUnstructuredGrid::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

	m_vtkThreshold->SetInputData(input);
	m_vtkThreshold->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, m_tag);
	m_vtkThreshold->SetThresholdFunction(vtkThreshold::THRESHOLD_UPPER);
	m_vtkThreshold->SetUpperThreshold(m_thresh_val);
	m_vtkThreshold->Update();

	output->DeepCopy(m_vtkThreshold->GetOutputDataObject(0));

	return 1;
}

void GeomOptFilter::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);

	os << indent << "GeomOptFilter: " << "\n";
	os << indent << this->m_tag << "\n";
	os << indent << this->m_thresh_val << "\n";
}
