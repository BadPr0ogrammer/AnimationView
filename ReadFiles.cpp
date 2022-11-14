#include <QDir>
#include <QString>
#include <QStringList>
#include <QDebug>

#include <string>

#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkCellData.h>
#include <vtkDataSetMapper.h>
#include <vtkColorTransferFunction.h>
#include <vtkLogLookupTable.h>
#include <vtkScalarBarActor.h>
#include <vtkThreshold.h>
#include <vtkTextProperty.h>
#include <vtkUnstructuredGridToExplicitStructuredGrid.h>
#include <vtkInformation.h>
#include <vtkThreshold.h>
#include <vtkLookupTable.h>
#include <vtkImageData.h>
#include <vtkCellDataToPointData.h>
#include <vtkRenderer.h>

using namespace std;

#include "ReadFiles.h"
#include "ParseFileName.h"
#include "ColorTables.h"

bool VtuFileReader::readVtuFile(bool init, const char* fname, int& timer_idx, std::vector<std::string>& attrs, int attr_idx, int threshold, int palette_idx,
	vtkDataSetMapper* dsmapper, double* range_cell, vtkThreshold* threshold_flt, double& thresh_val, vtkScalarBarActor* sbar, 
	std::vector<vtkSmartPointer<vtkImageData>>& image_data_vec, std::vector<int>& image_data_ids, bool slice, vtkSmartPointer<vtkLookupTable> &lut1, vtkSmartPointer<vtkLookupTable>& lut2)
{
	std::vector<int>::iterator it;
	if ((it = std::find(image_data_ids.begin(), image_data_ids.end(), timer_idx)) == image_data_ids.end()) {
		vtkNew<vtkXMLUnstructuredGridReader> unstruct_reader;
		vtkNew<vtkResampleToImage> resample_to_image;
		vtkNew<vtkCellDataToPointData> cell_to_point;

		if (fname && (m_path.empty() || timer_idx == m_dir_fnames.size() - 1))
			m_path = parseDirName(fname);
		if (m_dir_fnames.empty() || timer_idx == m_dir_fnames.size() - 1)
			scanVtuDir(m_path.c_str());
		if (m_dir_fnames.empty()) {
			qDebug() << "dir fnames is empty";
			return false;
		}
		if (fname || timer_idx >= m_dir_fnames.size())
			timer_idx = 0;

		string name = m_path + "/" + m_dir_fnames[timer_idx];
		unstruct_reader->SetFileName(name.c_str());
		unstruct_reader->Update();
		if (!unstruct_reader->GetOutput()) {
			qDebug() << "grid is null";
			return false;
		}
		if (init) {
			auto* grid = unstruct_reader->GetOutput();
			int n = grid->GetCellData()->GetNumberOfArrays();
			attrs.clear();
			for (int i = 0; i < n; i++)
				attrs.push_back(grid->GetCellData()->GetArrayName(i));
			if (attrs.empty()) {
				qDebug() << "Attrs is empty";
				return false;
			}
		}
		if (unstruct_reader->GetOutput()->GetCellData()->SetActiveAttribute(attrs[attr_idx].c_str(), vtkDataSetAttributes::SCALARS) == -1) {
			qDebug() << "Attribute " << attrs[attr_idx].c_str() << " is abscent";
			return false;
		}
		double* p_rg = unstruct_reader->GetOutput()->GetCellData()->GetScalars(attrs[attr_idx].c_str())->GetRange();
		if (!p_rg || std::fabs(p_rg[1] - p_rg[0]) < DBL_EPSILON) {
			qDebug() << "Scalar " << attrs[attr_idx].c_str() << " is flat";
			return false;
		}
		range_cell[0] = p_rg[0];
		range_cell[1] = p_rg[1];

		cell_to_point->SetInputConnection(unstruct_reader->GetOutputPort());
		cell_to_point->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, attrs[attr_idx].c_str());

		resample_to_image->SetInputConnection(cell_to_point->GetOutputPort());
		resample_to_image->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, attrs[attr_idx].c_str());
		resample_to_image->SetUseInputBounds(true);
		resample_to_image->SetSamplingDimensions(100, 100, 100);
		resample_to_image->Update();

		vtkSmartPointer<vtkImageData> image_data = vtkSmartPointer<vtkImageData>::New();
		image_data->DeepCopy(resample_to_image->GetOutput());
		image_data_vec.push_back(image_data);
		image_data_ids.push_back(timer_idx);
		it = image_data_ids.begin() + timer_idx;
	}
	if (!slice) {
		thresh_val = threshold / 100.0 * (range_cell[1] - range_cell[0]) + range_cell[0];

		threshold_flt->RemoveAllInputConnections(0);
		threshold_flt->SetInputData(image_data_vec[*it]);
		threshold_flt->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, attrs[attr_idx].c_str());
		threshold_flt->SetThresholdFunction(vtkThreshold::THRESHOLD_UPPER);
		threshold_flt->SetUpperThreshold(thresh_val);
		threshold_flt->Update();

		dsmapper->RemoveAllInputConnections(0);
		dsmapper->SetScalarModeToUsePointData();
		dsmapper->SetInputConnection(threshold_flt->GetOutputPort());
		dsmapper->SetScalarRange(range_cell[0], range_cell[1]);
		lut1 = generate_lookup_table_by_idx(palette_idx, range_cell[0], range_cell[1]);
		dsmapper->SetLookupTable(lut1);
		dsmapper->Update();
	}
	if (init) {		
		sbar->SetLookupTable(!slice ? lut1 : lut2);
		sbar->GetPositionCoordinate()->SetCoordinateSystemToDisplay();
		sbar->GetPositionCoordinate()->SetValue(1800, 1200, 0.0);
		sbar->UnconstrainedFontSizeOff();
		sbar->AnnotationTextScalingOn();
		sbar->SetMaximumWidthInPixels(80);
		sbar->SetMaximumHeightInPixels(800);
		sbar->GetTitleTextProperty()->SetFontSize(8);
		sbar->SetTitle(attrs[attr_idx].c_str());
		sbar->SetLabelFormat("%.2f");
	}
	timer_idx++;
	if (timer_idx >= m_dir_fnames.size())
		timer_idx = 0;

	return true;
}

vtkSmartPointer<vtkLookupTable> generate_jet_lookup_table()
{
	vtkSmartPointer<vtkLookupTable> lookup_table = vtkSmartPointer<vtkLookupTable>::New();
	int num_colors = 77;
	lookup_table->SetNumberOfTableValues(num_colors);

	auto transfer_func = vtkSmartPointer<vtkColorTransferFunction>::New();
	transfer_func->AddRGBPoint(0, 0, 0, 127. / 255);
	transfer_func->AddRGBPoint(11. / 77, 0, 0, 1);
	transfer_func->AddRGBPoint(12. / 77, 0, 14 / 255., 1);
	transfer_func->AddRGBPoint(29. / 77, 0, 1, 1);
	transfer_func->AddRGBPoint(30. / 77, 14. / 255, 1, 240. / 255);
	transfer_func->AddRGBPoint(48. / 77, 1, 1, 0);
	transfer_func->AddRGBPoint(49. / 77, 1, 240. / 255, 0);
	transfer_func->AddRGBPoint(67. / 77, 1, 0, 0);
	transfer_func->AddRGBPoint(68. / 77, 240. / 255, 0, 0);
	transfer_func->AddRGBPoint(1, 127. / 255, 0, 0);

	for (int i = 0; i < num_colors; i++) {
		float s = (float)i / num_colors;
		double* cc = transfer_func->GetColor(s);
		lookup_table->SetTableValue(i, cc[0], cc[1], cc[2], 1.0);
	}
	lookup_table->Build();
	return lookup_table;
}

void VtuFileReader::scanVtuDir(const char* dir_name)
{
	QDir directory(dir_name);
	QStringList filter; filter << "*.vtu";
	QStringList file_lst = directory.entryList(filter, QDir::Files, QDir::Name);

	m_dir_fnames.clear();
	foreach(QString name, file_lst)
		m_dir_fnames.push_back(name.toUtf8().constData());
}
