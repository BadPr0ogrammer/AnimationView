#ifndef VTUANIMATIONVIEW_H
#define VTUANIMATIONVIEW_H

#include <QMainWindow>
#include <QMutex>
#include <QTimer>
#include <QTreeView>
#include <QStandardItemModel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QLabel>
#include <QToolButton>
#include <QTextEdit>

#include <vtkNew.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
#include <QVTKRenderWidget.h>
#include <vtkUnstructuredGrid.h>
#include <vtkResampleToImage.h>
#include <vtkDataSetMapper.h>
#include <vtkThreshold.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarActor.h>
#include <vtkImageData.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkCellDataToPointData.h>
#include <vtkImageSlice.h>
#include <vtkImageResliceMapper.h>
#include <vtkImplicitPlaneWidget2.h>
#include <vtkImplicitPlaneRepresentation.h>

#include "ReadFiles.h"

class MouseInteractorStyle;
class VtuFileReader;
class Settings;
class Image_slice_callback;

class VtuAnimationView : public QMainWindow
{
	Q_OBJECT

public:
	VtuAnimationView(QWidget* parent  = nullptr);
	~VtuAnimationView();

	QComboBox* m_channel_cb = nullptr;
	QSlider* m_time_sld = nullptr;
	QLabel* m_counter_lb = nullptr;
	QLabel* m_picked_val_lb = nullptr;
	QLabel* m_scalar_threshold_lb = nullptr;
	QToolButton* m_reslice_wgt_btn = nullptr;
	QLabel* m_sb_msg_text = nullptr;

	QTreeView* m_tree_view = nullptr;
	QStandardItemModel* m_tree_model = nullptr;
	QStandardItem* m_tree_root = nullptr;

	MouseInteractorStyle* m_interactor_style = nullptr;
	QVTKRenderWidget* m_qvtk_render_widget = nullptr;
	
	vtkSmartPointer<vtkRenderer> m_renderer;
	vtkSmartPointer<vtkActor> m_actor;
	vtkSmartPointer<vtkDataSetMapper> m_dsmapper;
	vtkSmartPointer<vtkScalarBarActor> m_sbar;
	
	vtkNew<vtkImplicitPlaneWidget2> m_impl_plane_widget2;
	vtkNew<vtkImplicitPlaneRepresentation> m_impl_plane_repr;
	vtkNew<vtkImageSlice> m_image_reslice;
	vtkNew<vtkImageResliceMapper> m_image_mapper;

	Image_slice_callback* m_image_slice_callback;
	VtuFileReader* m_file_reader = nullptr;

	std::map<int, data_t*> m_data_map;
	int m_data_idx = 0;

	double m_thresh_val = 0;
	int m_cur_attr_idx = 0;
	std::vector<std::string> m_attrs;
	QTimer m_timer;
	QMutex m_mutex;
	Settings* m_settings = nullptr;
	unsigned long m_impl_plane_widget2_id = ULONG_MAX;

	void setTimeSlider();
	void setTree();
	void resetInteractor();
	void setPositions(bool actor);
	void getPositions();
	void setImageMapper();
	void setMsgLabel();
	void theTimerUpdate();

public slots:
	void openFile();
	void timer();
	void mediaToBeginBtn();
	void mediaPlayBtn();
	void mediaStopBtn();
	void mediaToEndBtn();
	void timeLineSldChanged(int value);
	void animRateDsbChanged(double value);
	void cameraReset();
	void viewYZ();
	void viewXY();
	void viewXZ();
	void channelCbIdxChanged(int idx);
	void scalarThreshold(int value);
	void cellPicking();
	void close();
	void treeSelectionChanged(const QItemSelection&, const QItemSelection&);
	void about();
	void setupDlg();
	void planeWidget();

protected:
	void resizeEvent(QResizeEvent* event);
};
#endif // VTUANIMATIONVIEW_H
