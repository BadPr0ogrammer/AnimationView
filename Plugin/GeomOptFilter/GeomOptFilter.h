#pragma once

#include <vtkSmartPointer.h>
#include <vtkUnstructuredGridAlgorithm.h>
#include <vtkThreshold.h>

#ifdef GEOMOPTFILTER_EXPORTS
#define MY_EXPORTS __declspec(dllexport)
#else
#define MY_EXPORTS __declspec(dllimport)
#endif

class MY_EXPORTS GeomOptFilter : public vtkUnstructuredGridAlgorithm
{
public:
	static GeomOptFilter* New();
	vtkTypeMacro(GeomOptFilter, vtkUnstructuredGridAlgorithm);
	virtual void PrintSelf(ostream& os, vtkIndent indent);

protected:
	GeomOptFilter();
	virtual ~GeomOptFilter();

	int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
	void SetTagThreshold(const char* tag, double thr);
private:
	const char* m_tag = nullptr;
	double m_thresh_val = 0;
	vtkNew<vtkThreshold> m_vtkThreshold;
};
