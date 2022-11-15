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

bool VtuFileReader::readVtuFile(const char* fname, bool init, std::vector<std::string>& attrs, int attr_idx, int threshold, int palette_idx,
	vtkDataSetMapper* dsmapper, double& thresh_val, vtkScalarBarActor* sbar, std::map<int, data_t*>& data_map, int& data_idx, bool slice)
{
	if (fname && m_path.empty())
		m_path = parseDirName(fname);
	if (m_dir_fnames.empty())
		scanVtuDir(m_path.c_str());
	if (m_dir_fnames.empty()) {
		qDebug() << "dir fnames is empty";
		return false;
	}
	if (fname)
		data_idx = 0;
	if (data_idx >= m_dir_fnames.size())
		data_idx = 0;

	data_t* data = data_map[data_idx];
	if (!data) {
		data_t* data = new data_t();

		string name = m_path + "/" + m_dir_fnames[data_idx];
		QFileInfo fileinfo(name.c_str());
		if (!fileinfo.isFile()) {
			qDebug() << name.c_str() << " is not file";
			delete data;
			return false;
		}
		data->unstruct_reader->SetFileName(name.c_str());
		data->unstruct_reader->Update();
		if (!data->unstruct_reader->GetOutput()) {
			qDebug() << "grid is null";
			delete data;
			return false;
		}
		if (init) {
			auto* grid = data->unstruct_reader->GetOutput();
			int n = grid->GetCellData()->GetNumberOfArrays();
			attrs.clear();
			for (int i = 0; i < n; i++)
				attrs.push_back(grid->GetCellData()->GetArrayName(i));
			if (attrs.empty()) {
				qDebug() << "Attrs is empty";
				delete data;
				return false;
			}
		}
		if (data->unstruct_reader->GetOutput()->GetCellData()->SetActiveAttribute(attrs[attr_idx].c_str(), vtkDataSetAttributes::SCALARS) == -1) {
			qDebug() << "Attribute " << attrs[attr_idx].c_str() << " is abscent";
			delete data;
			return false;
		}
		double* p_rg = data->unstruct_reader->GetOutput()->GetCellData()->GetScalars(attrs[attr_idx].c_str())->GetRange();
		if (!p_rg || std::fabs(p_rg[1] - p_rg[0]) < DBL_EPSILON) {
			qDebug() << "Scalar " << attrs[attr_idx].c_str() << " is flat";
			delete data;
			return false;
		}
		data->range_cell[0] = p_rg[0];
		data->range_cell[1] = p_rg[1];

		data->cell_to_point->SetInputConnection(data->unstruct_reader->GetOutputPort());
		data->cell_to_point->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, attrs[attr_idx].c_str());

		data->resample_to_image->SetInputConnection(data->cell_to_point->GetOutputPort());
		data->resample_to_image->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, attrs[attr_idx].c_str());
		data->resample_to_image->SetUseInputBounds(true);
		data->resample_to_image->SetSamplingDimensions(100, 100, 100);
		data->resample_to_image->Update();

		//data->data->DeepCopy(data->resample_to_image->GetOutput());
		data->image_data = data->resample_to_image->GetOutput();
		data_map[data_idx] = data;
	}
	data = data_map[data_idx];
	data->lut = generate_lookup_table_by_idx(palette_idx, data->range_cell[0], data->range_cell[1]);
	if (!slice) {
		thresh_val = threshold / 100.0 * (data->range_cell[1] - data->range_cell[0]) + data->range_cell[0];

		data->threshold_flt->SetInputData(data->unstruct_reader->GetOutput());//image_data
		//threshold_flt->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, attrs[attr_idx].c_str());
		data->threshold_flt->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_CELLS, attrs[attr_idx].c_str());
		data->threshold_flt->SetThresholdFunction(vtkThreshold::THRESHOLD_UPPER);
		data->threshold_flt->SetUpperThreshold(thresh_val);
		data->threshold_flt->Update();

		dsmapper->RemoveAllInputs();
		//dsmapper->SetScalarModeToUsePointData();
		dsmapper->SetScalarModeToUseCellData();
		dsmapper->SetInputConnection(data->threshold_flt->GetOutputPort());
		dsmapper->SetScalarRange(data->range_cell[0], data->range_cell[1]);
		dsmapper->SetLookupTable(data->lut);
		dsmapper->Update();
	}
	if (init) {
		sbar->SetLookupTable(data->lut);
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
