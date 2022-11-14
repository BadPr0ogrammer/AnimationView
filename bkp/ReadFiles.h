#pragma once

#include <vector>
#include <string>

#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkUnstructuredGrid.h>
#include <vtkThreshold.h>
#include <vtkLogLookupTable.h>
#include <vtkScalarBarActor.h>
#include <vtkResampleToImage.h>
#include <vtkActor.h>

class VtuFileReader
{
public:
	std::string m_path;
	std::vector<std::string> m_dir_fnames;

	bool readVtuFile(bool init, const char* fname, int& timer_idx, std::vector<std::string>& attrs, int attr_idx, int threshold, int palette_idx,
		vtkDataSetMapper* dsmapper, double* range_cell, vtkThreshold* threshold_flt, double& thresh_val, vtkScalarBarActor* sbar, 
		std::vector<vtkSmartPointer<vtkImageData>>& image_data_vec, std::vector<int>& image_data_ids, bool slice, vtkSmartPointer<vtkLookupTable>& lut1, vtkSmartPointer<vtkLookupTable>& lut2);
	void scanVtuDir(const char* dir_name);
};
