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
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkResampleToImage.h>
#include <vtkCellDataToPointData.h>
#include <vtkImageData.h>

class data_t {
public:
	vtkSmartPointer<vtkXMLUnstructuredGridReader> unstruct_reader;
	vtkSmartPointer<vtkResampleToImage> resample_to_image;
	vtkSmartPointer<vtkCellDataToPointData> cell_to_point;
	vtkSmartPointer<vtkImageData> image_data;
	vtkSmartPointer<vtkThreshold> threshold_flt;
	vtkSmartPointer<vtkLookupTable> lut;
	double range_cell[2]{ 0, 0 };

	data_t() {
		unstruct_reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
		resample_to_image = vtkSmartPointer<vtkResampleToImage>::New();
		cell_to_point = vtkSmartPointer<vtkCellDataToPointData>::New();
		image_data = vtkSmartPointer<vtkImageData>::New();
		threshold_flt = vtkSmartPointer<vtkThreshold>::New();
		lut = vtkSmartPointer<vtkLookupTable>::New();
	}
};

class VtuFileReader
{
public:
	std::string m_path;
	std::vector<std::string> m_dir_fnames;

	bool readVtuFile(const char* fname, bool init, std::vector<std::string>& attrs, int attr_idx, int threshold, int palette_idx,
		vtkDataSetMapper* dsmapper, double& thresh_val, vtkScalarBarActor* sbar, std::map<int, data_t*>& data_map, int& data_idx, bool slice);
	void scanVtuDir(const char* dir_name);
};
