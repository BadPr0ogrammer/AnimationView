#include <QApplication>
#include <QFileDialog>
#include <QSizePolicy>
#include <QMessageBox>
#include <QResizeEvent>
#include <QDoubleSpinBox>
#include <QStandardItem>
#include <QToolButton>
#include <QStyleFactory>
#include <QAction>
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QComboBox>
#include <QLabel>
#include <QDockWidget>
#include <QStatusBar>
#include <QColor>
#include <QColorDialog>
#include <QSizePolicy>

#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderWidget.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkActor.h>
#include <QVTKOpenGLNativeWidget.h>
#include <QVTKRenderWidget.h>
#include <vtkCamera.h>
#include <vtkTransform.h>
#include <vtkTextProperty.h>
#include <vtkImageData.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkImageShiftScale.h>
#include <vtkImageMapToColors.h>
#include <vtkImageMapper3D.h>
#include <vtkImageProperty.h>
#include <vtkProperty.h>
#include <vtkImageReslice.h>
#include <vtkMatrix4x4.h>
#include <vtkPlane.h>
#include <vtkImageMapper.h>
#include <vtkMath.h>

#include "vtuanimationview.h"
#include "mouseinteractorstyle.h"
#include "ReadFiles.h"
#include "Settings.h"
#include "SetupDlg.h"
#include "ColorTables.h"

using namespace std;

#define SQR(a) ((a)*(a))

//$(QTDIR)/include;$(QTDIR)/include/QtCore;$(QTDIR)/mkspecs/win32-msvc;$(QTDIR)/include/QtGui;$(QTDIR)/include/QtANGLE;$(QTDIR)/include/QtWidgets;$(VTK_DIR)/Common/Color;$(VTK_ROOT)/Common/Color;$(VTK_DIR)/Common/Core;$(VTK_ROOT)/Common/Core;$(VTK_DIR)/Utilities/KWIML;$(VTK_ROOT)/Utilities/KWIML;$(VTK_DIR)/Utilities/KWSys;$(VTK_ROOT)/Utilities/KWSys;$(VTK_DIR)/Common/DataModel;$(VTK_ROOT)/Common/DataModel;$(VTK_DIR)/Common/Math;$(VTK_ROOT)/Common/Math;$(VTK_DIR)/ThirdParty/kissfft/vtkkissfft;$(VTK_ROOT)/ThirdParty/kissfft/vtkkissfft;$(VTK_DIR)/ThirdParty/kissfft;$(VTK_ROOT)/ThirdParty/kissfft;$(VTK_DIR)/Common/Transforms;$(VTK_ROOT)/Common/Transforms;$(VTK_DIR)/Filters/Core;$(VTK_ROOT)/Filters/Core;$(VTK_DIR)/Common/ExecutionModel;$(VTK_ROOT)/Common/ExecutionModel;$(VTK_DIR)/Common/Misc;$(VTK_ROOT)/Common/Misc;$(VTK_DIR)/Filters/Sources;$(VTK_ROOT)/Filters/Sources;$(VTK_DIR)/Infovis/Core;$(VTK_ROOT)/Infovis/Core;$(VTK_DIR)/IO/Image;$(VTK_ROOT)/IO/Image;$(VTK_DIR)/Imaging/Core;$(VTK_ROOT)/Imaging/Core;$(VTK_DIR)/Imaging/Sources;$(VTK_ROOT)/Imaging/Sources;$(VTK_DIR)/Rendering/FreeType;$(VTK_ROOT)/Rendering/FreeType;$(VTK_DIR)/Rendering/Core;$(VTK_ROOT)/Rendering/Core;$(VTK_DIR)/ThirdParty/freetype/vtkfreetype;$(VTK_ROOT)/ThirdParty/freetype/vtkfreetype;$(VTK_ROOT)/ThirdParty/freetype/vtkfreetype/include;$(VTK_DIR)/ThirdParty/freetype;$(VTK_ROOT)/ThirdParty/freetype;$(VTK_DIR)/ThirdParty/zlib/vtkzlib;$(VTK_ROOT)/ThirdParty/zlib/vtkzlib;$(VTK_DIR)/ThirdParty/zlib;$(VTK_ROOT)/ThirdParty/zlib;$(VTK_DIR)/Interaction/Style;$(VTK_ROOT)/Interaction/Style;$(VTK_DIR)/Rendering/ContextOpenGL2;$(VTK_ROOT)/Rendering/ContextOpenGL2;$(VTK_DIR)/Rendering/Context2D;$(VTK_ROOT)/Rendering/Context2D;$(VTK_DIR)/Rendering/OpenGL2;$(VTK_ROOT)/Rendering/OpenGL2;$(VTK_DIR)/Filters/General;$(VTK_ROOT)/Filters/General;$(VTK_DIR)/Rendering/HyperTreeGrid;$(VTK_ROOT)/Rendering/HyperTreeGrid;$(VTK_DIR)/Rendering/UI;$(VTK_ROOT)/Rendering/UI;$(VTK_DIR)/ThirdParty/glew/vtkglew;$(VTK_ROOT)/ThirdParty/glew/vtkglew;$(VTK_DIR)/ThirdParty/glew;$(VTK_ROOT)/ThirdParty/glew;$(VTK_DIR)/Rendering/GL2PSOpenGL2;$(VTK_ROOT)/Rendering/GL2PSOpenGL2;$(VTK_DIR)/Views/Qt;$(VTK_ROOT)/Views/Qt;$(VTK_DIR)/GUISupport/Qt;$(VTK_ROOT)/GUISupport/Qt;$(VTK_DIR)/Interaction/Widgets;$(VTK_ROOT)/Interaction/Widgets;$(QTDIR)/include/QtOpenGL;$(VTK_DIR)/Views/Core;$(VTK_ROOT)/Views/Core;$(VTK_DIR)/Views/Infovis;$(VTK_ROOT)/Views/Infovis;$(VTK_DIR)/Rendering/Qt;$(VTK_ROOT)/Rendering/Qt;$(VTK_DIR)/Rendering/Label;$(VTK_ROOT)/Rendering/Label
//vtkRenderingContextOpenGL2-9.2d.lib;vtkRenderingGL2PSOpenGL2-9.2d.lib;vtkViewsQt-9.2d.lib;vtkRenderingQt-9.2d.lib;vtkViewsInfovis-9.2d.lib;vtkViewsCore-9.2d.lib;vtkInfovisCore-9.2d.lib;vtkGUISupportQt-9.2d.lib;vtkRenderingOpenGL2-9.2d.lib;vtkRenderingHyperTreeGrid-9.2d.lib;vtkRenderingUI-9.2d.lib;vtkglew-9.2d.lib;opengl32.lib;vtkInteractionWidgets-9.2d.lib;vtkInteractionStyle-9.2d.lib;vtkRenderingContext2D-9.2d.lib;vtkImagingSources-9.2d.lib;vtkIOImage-9.2d.lib;vtkImagingCore-9.2d.lib;C:\src\qt-5.15\lib\Qt5OpenGL.lib;C:\src\qt-5.15\lib\Qt5Widgets.lib;C:\src\qt-5.15\lib\Qt5Gui->lib;C:\src\qt-5.15\lib\Qt5Core.lib;vtkRenderingLabel-9.2d.lib;vtkRenderingFreeType-9.2d.lib;vtkRenderingCore-9.2d.lib;vtkCommonColor-9.2d.lib;vtkFiltersSources-9.2d.lib;vtkfreetype-9.2d.lib;vtkzlib-9.2d.lib;vtkFiltersGeneral-9.2d.lib;vtkFiltersCore-9.2d.lib;vtkCommonExecutionModel-9.2d.lib;vtkCommonDataModel-9.2d.lib;vtkCommonMisc-9.2d.lib;vtkCommonTransforms-9.2d.lib;vtkCommonMath-9.2d.lib;vtkCommonCore-9.2d.lib;vtksys-9.2d.lib;ws2_32.lib;dbghelp.lib;psapi.lib;vtkkissfft-9.2d.lib;
//$(VTK_DIR)/Common/Color;$(VTK_ROOT)/Common/Color;$(VTK_DIR)/Common/Core;$(VTK_ROOT)/Common/Core;$(VTK_DIR)/Utilities/KWIML;$(VTK_ROOT)/Utilities/KWIML;$(VTK_DIR)/Utilities/KWSys;$(VTK_ROOT)/Utilities/KWSys;$(VTK_DIR)/Common/DataModel;$(VTK_ROOT)/Common/DataModel;$(VTK_DIR)/Common/Math;$(VTK_ROOT)/Common/Math;$(VTK_DIR)/ThirdParty/kissfft/vtkkissfft;$(VTK_ROOT)/ThirdParty/kissfft/vtkkissfft;$(VTK_DIR)/ThirdParty/kissfft;$(VTK_ROOT)/ThirdParty/kissfft;$(VTK_DIR)/Common/Transforms;$(VTK_ROOT)/Common/Transforms;$(VTK_DIR)/Filters/Core;$(VTK_ROOT)/Filters/Core;$(VTK_DIR)/Common/ExecutionModel;$(VTK_ROOT)/Common/ExecutionModel;$(VTK_DIR)/Common/Misc;$(VTK_ROOT)/Common/Misc;$(VTK_DIR)/Filters/Sources;$(VTK_ROOT)/Filters/Sources;$(VTK_DIR)/Infovis/Core;$(VTK_ROOT)/Infovis/Core;$(VTK_DIR)/IO/Image;$(VTK_ROOT)/IO/Image;$(VTK_DIR)/Imaging/Core;$(VTK_ROOT)/Imaging/Core;$(VTK_DIR)/Imaging/Sources;$(VTK_ROOT)/Imaging/Sources;$(VTK_DIR)/Rendering/FreeType;$(VTK_ROOT)/Rendering/FreeType;$(VTK_DIR)/Rendering/Core;$(VTK_ROOT)/Rendering/Core;$(VTK_DIR)/ThirdParty/freetype/vtkfreetype;$(VTK_ROOT)/ThirdParty/freetype/vtkfreetype;$(VTK_ROOT)/ThirdParty/freetype/vtkfreetype/include;$(VTK_DIR)/ThirdParty/freetype;$(VTK_ROOT)/ThirdParty/freetype;$(VTK_DIR)/ThirdParty/zlib/vtkzlib;$(VTK_ROOT)/ThirdParty/zlib/vtkzlib;$(VTK_DIR)/ThirdParty/zlib;$(VTK_ROOT)/ThirdParty/zlib;$(VTK_DIR)/Interaction/Style;$(VTK_ROOT)/Interaction/Style;$(VTK_DIR)/Rendering/ContextOpenGL2;$(VTK_ROOT)/Rendering/ContextOpenGL2;$(VTK_DIR)/Rendering/Context2D;$(VTK_ROOT)/Rendering/Context2D;$(VTK_DIR)/Rendering/OpenGL2;$(VTK_ROOT)/Rendering/OpenGL2;$(VTK_DIR)/Filters/General;$(VTK_ROOT)/Filters/General;$(VTK_DIR)/Rendering/HyperTreeGrid;$(VTK_ROOT)/Rendering/HyperTreeGrid;$(VTK_DIR)/Rendering/UI;$(VTK_ROOT)/Rendering/UI;$(VTK_DIR)/ThirdParty/glew/vtkglew;$(VTK_ROOT)/ThirdParty/glew/vtkglew;$(VTK_DIR)/ThirdParty/glew;$(VTK_ROOT)/ThirdParty/glew;$(VTK_DIR)/Rendering/GL2PSOpenGL2;$(VTK_ROOT)/Rendering/GL2PSOpenGL2;$(VTK_DIR)/Views/Qt;$(VTK_ROOT)/Views/Qt;$(VTK_DIR)/GUISupport/Qt;$(VTK_ROOT)/GUISupport/Qt;$(VTK_DIR)/Interaction/Widgets;$(VTK_ROOT)/Interaction/Widgets;$(QTDIR)/include/QtOpenGL;$(VTK_DIR)/Views/Core;$(VTK_ROOT)/Views/Core;$(VTK_DIR)/Views/Infovis;$(VTK_ROOT)/Views/Infovis;$(VTK_DIR)/Rendering/Qt;$(VTK_ROOT)/Rendering/Qt;$(VTK_DIR)/Rendering/Label;$(VTK_ROOT)/Rendering/Label;$(VTK_DIR)/Filters/Modeling;$(VTK_ROOT)/Filters/Modeling;$(VTK_DIR)/Filters/Geometry;$(VTK_ROOT)/Filters/Geometry;$(VTK_DIR)/IO/XML;$(VTK_ROOT)/IO/XML;$(VTK_DIR)/Rendering/Annotation;$(VTK_ROOT)/Rendering/Annotation;

class Image_slice_callback : public vtkCommand
{
public:
	VtuAnimationView* m_pView;
	Image_slice_callback(VtuAnimationView* p) : m_pView(p) {}
	void Execute(vtkObject* caller, unsigned long evId, void*) override {
		unsigned long f = evId &
			(vtkCommand::LeftButtonPressEvent | vtkCommand::LeftButtonReleaseEvent |
				vtkCommand::RightButtonPressEvent | vtkCommand::RightButtonReleaseEvent |
				vtkCommand::MiddleButtonPressEvent | vtkCommand::MiddleButtonReleaseEvent);
		if (caller && f) {
			vtkNew<vtkPlane> pl;
			m_pView->m_impl_plane_repr->GetPlane(pl);
			m_pView->m_image_mapper->GetSlicePlane()->SetNormal(pl->GetNormal());
			m_pView->m_image_mapper->GetSlicePlane()->SetOrigin(pl->GetOrigin());
			m_pView->m_image_mapper->Modified();
		}
	}
};

VtuAnimationView::VtuAnimationView(QWidget* parent) : QMainWindow(parent)
{
	m_renderer = vtkSmartPointer<vtkRenderer>::New();
	m_actor = vtkSmartPointer<vtkActor>::New();
	m_dsmapper = vtkSmartPointer<vtkDataSetMapper>::New();
	m_sbar = vtkSmartPointer<vtkScalarBarActor>::New();

	m_image_slice_callback = new Image_slice_callback(this);

	setMinimumSize(800, 600);
	setCentralWidget(new QFrame);
	setWindowIcon(QIcon(":/AnimationView/res/film-timeline.png"));
	setWindowTitle("Просмотрщик моделей");

	QToolBar* main_toolb = addToolBar("mainToolBar");

	QMenu* menu_file = menuBar()->addMenu("Файл");
	QMenu* menu_view = menuBar()->addMenu("Вид");
	QMenu* menu_anim = menuBar()->addMenu("Анимация");
	QMenu* menu_op = menuBar()->addMenu("Операции");
	
	QToolButton* btn;
	QAction* act;
	QLabel* label;
	QDoubleSpinBox* dsb;
	QDockWidget* dock;
	QSlider* sld;

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Открыть");
	act->setIcon(QIcon(":/AnimationView/res/document-open.png"));
	btn->setIcon(QIcon(":/AnimationView/res/document-open.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::openFile);
	connect(act, &QAction::triggered, this, &VtuAnimationView::openFile);
	menu_file->addAction(act);

	main_toolb->addSeparator();
	label = new QLabel(" Канал ");
	main_toolb->addWidget(label);

	m_channel_cb = new QComboBox;
	connect(m_channel_cb, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &VtuAnimationView::channelCbIdxChanged);
	main_toolb->addWidget(m_channel_cb);

	main_toolb->addSeparator();
	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("В окно");
	act->setIcon(QIcon(":/AnimationView/res/application-resize-actual.png"));
	btn->setIcon(QIcon(":/AnimationView/res/application-resize-actual.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::cameraReset);
	connect(act, &QAction::triggered, this, &VtuAnimationView::cameraReset);
	menu_view->addAction(act);

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Вид X-Z");
	act->setIcon(QIcon(":/AnimationView/res/view-x-z.png"));
	btn->setIcon(QIcon(":/AnimationView/res/view-x-z.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::viewXZ);
	connect(act, &QAction::triggered, this, &VtuAnimationView::viewXZ);
	menu_view->addAction(act);

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Вид Y-Z");
	act->setIcon(QIcon(":/AnimationView/res/view-y-z.png"));
	btn->setIcon(QIcon(":/AnimationView/res/view-y-z.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::viewYZ);
	connect(act, &QAction::triggered, this, &VtuAnimationView::viewYZ);
	menu_view->addAction(act);

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Вид X-Y");
	act->setIcon(QIcon(":/AnimationView/res/view-x-y.png"));
	btn->setIcon(QIcon(":/AnimationView/res/view-x-y.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::viewXY);
	connect(act, &QAction::triggered, this, &VtuAnimationView::viewXY);
	menu_view->addAction(act);

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("В начало");
	act->setIcon(QIcon(":/AnimationView/res/media-skip-backward.png"));
	btn->setIcon(QIcon(":/AnimationView/res/media-skip-backward.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::mediaToBeginBtn);
	connect(act, &QAction::triggered, this, &VtuAnimationView::mediaToBeginBtn);
	menu_anim->addAction(act);

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Стоп");
	act->setIcon(QIcon(":/AnimationView/res/media-playback-stop.png"));
	btn->setIcon(QIcon(":/AnimationView/res/media-playback-stop.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::mediaStopBtn);
	connect(act, &QAction::triggered, this, &VtuAnimationView::mediaStopBtn);
	menu_anim->addAction(act);

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Старт");
	act->setIcon(QIcon(":/AnimationView/res/media-playback-start.png"));
	btn->setIcon(QIcon(":/AnimationView/res/media-playback-start.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::mediaPlayBtn);
	connect(act, &QAction::triggered, this, &VtuAnimationView::mediaPlayBtn);
	menu_anim->addAction(act);

	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("В конец");
	act->setIcon(QIcon(":/AnimationView/res/media-skip-forward.png"));
	btn->setIcon(QIcon(":/AnimationView/res/media-skip-forward.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::mediaToEndBtn);
	connect(act, &QAction::triggered, this, &VtuAnimationView::mediaToEndBtn);
	menu_anim->addAction(act);

	main_toolb->addSeparator();
	label = new QLabel(" № ");
	main_toolb->addWidget(label);

	m_counter_lb = new QLabel("");
	main_toolb->addWidget(m_counter_lb);
	m_counter_lb->setStyleSheet("border: 1px solid lightgray");
	m_counter_lb->setMinimumSize(40, 20);
	m_counter_lb->setMaximumSize(40, 20);

	main_toolb->addSeparator();
	label = new QLabel(" Интервал ");
	main_toolb->addWidget(label);

	dsb = new QDoubleSpinBox;
	main_toolb->addWidget(dsb);
	connect(dsb, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &VtuAnimationView::animRateDsbChanged);
	dsb->setRange(0.0001, 100);
	dsb->setSingleStep(0.1);

	main_toolb->addSeparator();
	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Узел");
	act->setIcon(QIcon(":/AnimationView/res/cell-picking.png"));
	btn->setIcon(QIcon(":/AnimationView/res/cell-picking.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::cellPicking);
	connect(act, &QAction::triggered, this, &VtuAnimationView::cellPicking);
	menu_op->addAction(act);

	m_picked_val_lb = new QLabel(" ");
	main_toolb->addWidget(m_picked_val_lb);
	m_picked_val_lb->setStyleSheet("border: 1px solid lightgray");
	m_picked_val_lb->setMinimumSize(40, 20);
	m_picked_val_lb->setMaximumSize(40, 20);

	main_toolb->addSeparator();
	label = new QLabel(" Порог ");
	main_toolb->addWidget(label);

	sld = new QSlider;
	sld->setOrientation(Qt::Horizontal);
	sld->setRange(1, 100);
	sld->setMaximumWidth(400);
	main_toolb->addWidget(sld);
	connect(sld, &QSlider::valueChanged, this, &VtuAnimationView::scalarThreshold);

	m_scalar_threshold_lb = new QLabel("");
	main_toolb->addWidget(m_scalar_threshold_lb);
	m_scalar_threshold_lb->setStyleSheet("border: 1px solid lightgray");
	m_scalar_threshold_lb->setMinimumSize(40, 20);
	m_scalar_threshold_lb->setMaximumSize(40, 20);

	main_toolb->addSeparator();
	m_reslice_wgt_btn = new QToolButton;
	m_reslice_wgt_btn->setCheckable(true);
	act = main_toolb->addWidget(m_reslice_wgt_btn);
	act->setText("Преобр.в рег.решетку");
	act->setIcon(QIcon(":/AnimationView/res/sc_hideslide.png"));
	m_reslice_wgt_btn->setIcon(QIcon(":/AnimationView/res/sc_hideslide.png"));
	connect(m_reslice_wgt_btn, &QToolButton::clicked, this, &VtuAnimationView::planeWidget);
	connect(act, &QAction::triggered, this, &VtuAnimationView::planeWidget);
	menu_op->addAction(act);

	main_toolb->addSeparator();
	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Настройки");
	act->setIcon(QIcon(":/AnimationView/res/gear.png"));
	btn->setIcon(QIcon(":/AnimationView/res/gear.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::setupDlg);
	connect(act, &QAction::triggered, this, &VtuAnimationView::setupDlg);
	menu_op->addAction(act);

	main_toolb->addSeparator();
	btn = new QToolButton;
	act = main_toolb->addWidget(btn);
	act->setText("Закрыть");
	act->setIcon(QIcon(":/AnimationView/res/cross-button.png"));
	btn->setIcon(QIcon(":/AnimationView/res/cross-button.png"));
	connect(btn, &QToolButton::clicked, this, &VtuAnimationView::close);
	connect(act, &QAction::triggered, this, &VtuAnimationView::close);
	menu_file->addAction(act);

	act = new QAction;
	act->setText("О программе");
	act->setIcon(QIcon(":/AnimationView/res/film-timeline.png"));
	menu_file->addAction(act);
	connect(act, &QAction::triggered, this, &VtuAnimationView::about);

	m_time_sld = new QSlider;
	m_time_sld->setOrientation(Qt::Horizontal);
	m_time_sld->setTickPosition(QSlider::TicksAbove);
	m_time_sld->setTickInterval(1);
	m_time_sld->setRange(0, 0);

	dock = new QDockWidget("DockBottom", this);
	dock->setWindowTitle("Временная шкала");
	dock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	dock->setWidget(m_time_sld);
	addDockWidget(Qt::BottomDockWidgetArea, dock);

	statusBar()->setSizeGripEnabled(true);
	m_sb_msg_text = new QLabel;
	statusBar()->addWidget(m_sb_msg_text);

	m_tree_view = new QTreeView;
	m_tree_view->setStyle(QStyleFactory::create("windows"));
	m_tree_view->setHeaderHidden(true);
	m_tree_model = new QStandardItemModel;
	m_tree_view->setModel(m_tree_model);
	m_tree_model->setColumnCount(1);

	m_tree_root = new QStandardItem("Файлы");
	m_tree_root->setSelectable(false);
	m_tree_model->invisibleRootItem()->appendRow(m_tree_root);

	dock = new QDockWidget("DockLeft", this);
	dock->setWindowTitle("Vtu модели");
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	dock->setWidget(m_tree_view);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	connect(m_tree_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &VtuAnimationView::treeSelectionChanged);

	m_interactor_style = new MouseInteractorStyle(this);

	m_qvtk_render_widget = new QVTKRenderWidget(centralWidget());
	{
		vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
		m_qvtk_render_widget->setRenderWindow(renderWindow);
	}
	m_qvtk_render_widget->setFixedSize(QSize(2000, 2000));
	m_qvtk_render_widget->renderWindow()->AddRenderer(m_renderer);

	QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy.setHorizontalStretch(10);
	sizePolicy.setVerticalStretch(10);
	m_qvtk_render_widget->setSizePolicy(sizePolicy);

	m_timer.setInterval(1000);
	m_timer.setParent(this);
	m_timer.stop();
	connect(&m_timer, &QTimer::timeout, this, &VtuAnimationView::timer);

	m_settings = new Settings();

	QColor& c = m_settings->m_bkg_color;
	m_renderer->SetBackground(c.redF(), c.greenF(), c.blueF());
}

VtuAnimationView::~VtuAnimationView()
{
	getPositions();

	m_settings->Save();
	delete m_settings;

	delete m_file_reader;
	delete m_qvtk_render_widget;
	delete m_interactor_style;

	for each (auto p in m_data_map)
		delete p.second;
}

void VtuAnimationView::openFile()
{
	m_mutex.lock();
	QString fname = QFileDialog::getOpenFileName(this, "VTK Unstructured Grid Files", QString(), "VTK Unstructured Grid Files (*.vtu)");
	if (!fname.isEmpty()) {
		delete m_file_reader;
		m_file_reader = new VtuFileReader;
		bool slice = m_reslice_wgt_btn->isChecked();
		if (m_file_reader->readVtuFile(fname.toUtf8().constData(), true, m_attrs, m_cur_attr_idx, m_settings->m_scalar_threshold, m_settings->m_palette_idx,
			m_dsmapper, m_thresh_val, m_sbar, m_data_map, m_data_idx, slice)) {
			if (slice)
				setImageMapper();

			m_channel_cb->clear();
			foreach(const string & attr, m_attrs)
				m_channel_cb->addItem(attr.c_str());
			m_channel_cb->setCurrentIndex(m_cur_attr_idx);

			setTree();
			setTimeSlider();
			cameraReset();
			setPositions(false);
			static bool ini = false;
			if (!ini) {
				ini = true;
				m_actor->SetMapper((vtkMapper*)m_dsmapper);
				m_renderer->AddActor(m_actor);
				m_renderer->AddActor((vtkProp*)m_sbar);
				m_actor->SetPosition(m_settings->m_actor_position);
			}
			setMsgLabel();

			m_mutex.unlock();		
			return;
		}
	}
	QMessageBox::warning(this, "VtuAnimationView", "Ошибка чтения файла");
	m_mutex.unlock();
}

void VtuAnimationView::setMsgLabel()
{
	vtkImageData* img = m_data_map[m_data_idx]->image_data;
	if (img) {
		int num_points = img->GetNumberOfPoints();
		int num_cells = img->GetNumberOfCells();
		int* dims = img->GetDimensions();
		double* space = img->GetSpacing();
		double* ori = img->GetOrigin();
		const char* scalar = img->GetScalarTypeAsString();
		double* rg = img->GetScalarRange();
		char buf[1000];
		sprintf(buf, "Величина:%s,Тип:%s,Диапазон(%f,%f),Точек:%d,Ячеек:%d,Размер(%d,%d,%d),Шаг(%f,%f,%f),Начало(%f,%f,%f),Файлов:%d,Текущий:%d",
			m_attrs[m_cur_attr_idx].c_str(), scalar, rg[0], rg[1], num_points, num_cells, dims[0], dims[1], dims[2], space[0], space[1], space[2], ori[0], ori[1], ori[2],
			m_data_map.size(), m_data_idx);
		m_sb_msg_text->setText(buf);
	} else
		m_sb_msg_text->setText("");
}

void VtuAnimationView::timer()
{
	m_data_idx++;
	theTimerUpdate();
}

void VtuAnimationView::theTimerUpdate()
{
	bool act = m_timer.isActive();
	if (act)
		m_timer.stop();
	int old = m_file_reader->m_dir_fnames.size();
	QModelIndex cur = m_tree_view->currentIndex();
	bool slice = m_reslice_wgt_btn->isChecked();
	if (m_file_reader->readVtuFile(nullptr, false, m_attrs, m_cur_attr_idx, m_settings->m_scalar_threshold, m_settings->m_palette_idx,
		m_dsmapper, m_thresh_val, m_sbar, m_data_map, m_data_idx, slice)) {
		if (slice) {
			m_image_mapper->RemoveAllInputs();
			m_image_mapper->SetInputData(m_data_map[m_data_idx]->image_data);
		}
		setTimeSlider();
		QModelIndex idx = m_tree_model->index(m_data_idx, 0, m_tree_root->index());
		m_tree_view->setCurrentIndex(idx);

		m_renderer->GetRenderWindow()->Render();
		if (act)
			m_timer.start();
		setMsgLabel();
	}
}

void VtuAnimationView::resizeEvent(QResizeEvent* ev)
{
	QMainWindow::resizeEvent(ev);
	QSize sz(ev->size());	
	m_qvtk_render_widget->setMinimumSize(sz.width() - m_tree_view->size().width(), sz.height() - menuBar()->height() - statusBar()->height());
}

void VtuAnimationView::setTimeSlider()
{
	disconnect(m_time_sld, &QSlider::valueChanged, this, &VtuAnimationView::timeLineSldChanged);
	m_time_sld->setRange(0, m_file_reader->m_dir_fnames.size() - 1);
	m_time_sld->setValue(m_data_idx);
	m_counter_lb->setText(QString::number(m_data_idx));
	connect(m_time_sld, &QSlider::valueChanged, this, &VtuAnimationView::timeLineSldChanged);
}

void VtuAnimationView::setTree()
{
	disconnect(m_tree_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &VtuAnimationView::treeSelectionChanged);
	m_tree_root->removeRows(0, m_tree_root->rowCount());
	for (int i = 0; i < m_file_reader->m_dir_fnames.size(); ++i) {
		QStandardItem* item0 = new QStandardItem(m_file_reader->m_dir_fnames[i].c_str());
		item0->setEditable(false);
		item0->setSelectable(true);
		m_tree_root->appendRow(item0);
	}
	QModelIndex idx = m_tree_model->index(0, 0, m_tree_root->index());
	m_tree_view->setCurrentIndex(idx);
	m_tree_view->expandAll();
	connect(m_tree_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &VtuAnimationView::treeSelectionChanged);
}

void VtuAnimationView::mediaToBeginBtn()
{
	m_mutex.lock();
	m_data_idx = 0;
	theTimerUpdate();
	m_mutex.unlock();
}

void VtuAnimationView::mediaPlayBtn()
{
	m_timer.start();
}

void VtuAnimationView::mediaStopBtn()
{
	m_timer.stop();
}

void VtuAnimationView::mediaToEndBtn()
{
	m_mutex.lock();
	m_data_idx = m_data_map.size() - 1;
	theTimerUpdate();
	m_mutex.unlock();
}

void VtuAnimationView::timeLineSldChanged(int value)
{
	m_mutex.lock();
	m_data_idx = value;
	theTimerUpdate();
	m_mutex.unlock();
}

void VtuAnimationView::animRateDsbChanged(double value)
{
	m_timer.setInterval(value * 100);
}

void VtuAnimationView::setPositions(bool actor)
{
	vtkCamera* camera = m_renderer->GetActiveCamera();
	if (m_settings->m_camera_position != m_settings->m_camera_focal_point && m_settings->m_camera_parallel_scale != 0) {
		camera->SetPosition(m_settings->m_camera_position);
		camera->SetFocalPoint(m_settings->m_camera_focal_point);
		camera->ComputeViewPlaneNormal();
		camera->SetViewUp(m_settings->m_camera_view_up);
		camera->SetParallelScale(m_settings->m_camera_parallel_scale);
	}
	else
		m_renderer->ResetCamera();
	if (actor && m_actor)
		m_actor->SetPosition(m_settings->m_actor_position);
}

void VtuAnimationView::getPositions()
{
	vtkCamera* camera = m_renderer->GetActiveCamera();
	if (camera) {
		camera->GetPosition(m_settings->m_camera_position);
		camera->GetFocalPoint(m_settings->m_camera_focal_point);
		camera->GetViewUp(m_settings->m_camera_view_up);
		m_settings->m_camera_parallel_scale = camera->GetParallelScale();
	}
	if (m_actor)
		m_actor->GetPosition(m_settings->m_actor_position);
}

void VtuAnimationView::cameraReset()
{
	m_renderer->ResetCamera();
	m_renderer->GetRenderWindow()->Render();
}

void VtuAnimationView::viewYZ()
{
	double* fp = m_renderer->GetActiveCamera()->GetFocalPoint();
	double* p = m_renderer->GetActiveCamera()->GetPosition();
	double dist = std::sqrt(SQR(p[0] - fp[0]) + SQR(p[1] - fp[1]) + SQR(p[2] - fp[2]));
	m_renderer->GetActiveCamera()->SetPosition(fp[0] + dist, fp[1], fp[2]);
	m_renderer->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
	m_renderer->GetRenderWindow()->Render();
}

void VtuAnimationView::viewXY()
{
	double* fp = m_renderer->GetActiveCamera()->GetFocalPoint();
	double* p = m_renderer->GetActiveCamera()->GetPosition();
	double dist = std::sqrt(SQR(p[0] - fp[0]) + SQR(p[1] - fp[1]) + SQR(p[2] - fp[2]));
	m_renderer->GetActiveCamera()->SetPosition(fp[0], fp[1], fp[2] + dist);
	m_renderer->GetActiveCamera()->SetViewUp(0.0, 1.0, 0.0);
	m_renderer->GetRenderWindow()->Render();
}

void VtuAnimationView::viewXZ()
{
	double* fp = m_renderer->GetActiveCamera()->GetFocalPoint();
	double* p = m_renderer->GetActiveCamera()->GetPosition();
	double dist = std::sqrt(SQR(p[0] - fp[0]) + SQR(p[1] - fp[1]) + SQR(p[2] - fp[2]));
	m_renderer->GetActiveCamera()->SetPosition(fp[0], fp[1] - dist, fp[2]);
	m_renderer->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);
	m_renderer->GetRenderWindow()->Render();
}

void VtuAnimationView::channelCbIdxChanged(int idx)
{

}

void VtuAnimationView::scalarThreshold(int value)
{
	m_settings->m_scalar_threshold = value;
	data_t* data = m_data_map[m_data_idx];
	m_thresh_val = value / 100.0 * (data->range_cell[1] - data->range_cell[0]) + data->range_cell[0];
	bool slice = m_reslice_wgt_btn->isChecked();
	if (!slice) {
		data->threshold_flt->SetUpperThreshold(m_thresh_val);
		data->threshold_flt->Update();
	}
	m_renderer->GetRenderWindow()->Render();

	char buf[40] = { 0 };
	sprintf(buf, "%.4f", m_thresh_val);
	m_scalar_threshold_lb->setText(buf);
}

void VtuAnimationView::resetInteractor()
{
	vtkNew<vtkInteractorStyleTrackballCamera> style;
	m_renderer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(style);
	setCursor(Qt::ArrowCursor);
}

void VtuAnimationView::cellPicking()
{
	if (m_interactor_style) {
		resetInteractor();
		delete m_interactor_style;
		m_interactor_style = nullptr;
	}
	else {
		m_interactor_style = new MouseInteractorStyle(this);
		m_interactor_style->m_stag = m_attrs[m_cur_attr_idx];
		m_interactor_style->SetDefaultRenderer(m_renderer);
		m_interactor_style->m_data = m_data_map[m_data_idx]->image_data;
		m_renderer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(m_interactor_style);
		setCursor(Qt::CrossCursor);
	}
}

void VtuAnimationView::close()
{
	m_mutex.lock();
	m_timer.stop();
	m_channel_cb->clear();
	m_attrs.clear();
	m_data_idx = 0;
	m_cur_attr_idx = 0;

	m_renderer->RemoveActor(m_actor);
	m_renderer->RemoveActor((vtkProp*)m_sbar);

	delete m_file_reader;
	m_file_reader = nullptr;

	m_renderer->GetRenderWindow()->Render();
	
	setMsgLabel();
	m_mutex.unlock();
}

void VtuAnimationView::treeSelectionChanged(const QItemSelection&, const QItemSelection&)
{
	disconnect(m_tree_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &VtuAnimationView::treeSelectionChanged);
	QModelIndexList list = m_tree_view->selectionModel()->selectedRows();
	if (list.size()) {
		QModelIndex idx = list.at(0);
		int cur = idx.row();
		if (m_data_idx != cur) {
			m_data_idx = cur;
			theTimerUpdate();
		}
	}
	connect(m_tree_view->selectionModel(), &QItemSelectionModel::selectionChanged, this, &VtuAnimationView::treeSelectionChanged);
}

void VtuAnimationView::about()
{
	QMessageBox msg_box;
	msg_box.setWindowIcon(QPixmap(":/AnimationView/res/logo.png"));
	msg_box.setTextFormat(Qt::RichText);
	msg_box.setText("<span style='font-size:14pt; font-weight:600; color:#990000;'>НТЦ АПМ</span><br>");
	msg_box.setInformativeText("Просмотрщик наборов оптимизационных моделей");
	msg_box.exec();
}

void VtuAnimationView::setupDlg()
{
	getPositions();
	{
		int old_idx = m_settings->m_palette_idx;
		SetupDlg dlg(m_settings);
		if (dlg.exec() == QDialog::Accepted) {
			QColor& c = m_settings->m_bkg_color;
			m_renderer->SetBackground(c.redF(), c.greenF(), c.blueF());
			if (m_settings->m_palette_idx != old_idx) {
				bool slice = m_reslice_wgt_btn->isChecked();
				data_t* data = m_data_map[m_data_idx];
				if (!slice) {
					data->lut = generate_lookup_table_by_idx(m_settings->m_palette_idx, data->range_cell[0], data->range_cell[1]);
					m_dsmapper->SetLookupTable(data->lut);
					m_sbar->SetLookupTable(data->lut);
					m_dsmapper->Update();
				}
				else {
					data->lut = generate_lookup_table_by_idx(m_settings->m_palette_idx, data->range_cell[0], data->range_cell[1]);
					m_image_reslice->GetProperty()->SetLookupTable(data->lut);
					m_sbar->SetLookupTable(data->lut);
					m_image_reslice->Update();
				}
			}
			m_renderer->GetRenderWindow()->Render();
		}
	}
}

void VtuAnimationView::setImageMapper()
{
	data_t *data = m_data_map[m_data_idx];
	vtkImageData* img = m_data_map[m_data_idx]->image_data;

	double bounds[6];
	img->GetBounds(bounds);
	double spacing[3];
	img->GetSpacing(spacing);
	double origin[3];
	img->GetOrigin(origin);
	int extent[6];
	img->GetExtent(extent);
	double center[3];
	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]);
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]);
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]);
	bounds[0] -= 2 * spacing[2]; bounds[1] += 2 * spacing[2]; bounds[2] -= 2 * spacing[2]; bounds[3] += 2 * spacing[2]; bounds[4] -= 2 * spacing[2]; bounds[5] += 2 * spacing[2];

	m_image_mapper->RemoveAllInputs();
	m_image_mapper->SetInputData(img);
	double Normal[3], Center[3];
	m_image_mapper->GetSlicePlane()->GetNormal(Normal);
	m_image_mapper->GetSlicePlane()->GetOrigin(Center);
	m_image_mapper->SliceFacesCameraOff();
	
	m_impl_plane_repr->SetNormal(Normal);
	m_impl_plane_repr->SetOrigin(Center);
	m_impl_plane_repr->SetWidgetBounds(bounds);

	m_impl_plane_widget2->SetInteractor(m_renderer->GetRenderWindow()->GetInteractor());
	m_impl_plane_widget2->SetRepresentation(m_impl_plane_repr);
	m_impl_plane_widget2->On();
	
	data->lut = generate_lookup_table_by_idx(m_settings->m_palette_idx, data->range_cell[0], data->range_cell[1]);
	m_image_reslice->GetProperty()->SetLookupTable(data->lut);
	m_image_reslice->GetProperty()->UseLookupTableScalarRangeOn();
	m_image_reslice->GetProperty()->SetInterpolationType(VTK_CUBIC_INTERPOLATION);
	m_image_reslice->SetMapper(m_image_mapper);
	m_renderer->AddViewProp(m_image_reslice);

	m_renderer->RemoveActor(m_actor);

	if (m_impl_plane_widget2_id != ULONG_MAX)
		m_impl_plane_widget2->RemoveObserver(m_impl_plane_widget2_id);
	m_impl_plane_widget2_id = m_impl_plane_widget2->AddObserver(vtkCommand::InteractionEvent, m_image_slice_callback);
}

void VtuAnimationView::planeWidget()
{
	if (m_reslice_wgt_btn->isChecked()) {
		setImageMapper();
	}
	else {
		m_impl_plane_widget2->Off();
		m_renderer->RemoveViewProp(m_image_reslice);

		m_renderer->AddActor(m_actor);
		m_renderer->GetRenderWindow()->Render();
	}
}

/*
		vtkNew<vtkPlane> plane;
		plane->SetOrigin(center);
		plane->SetNormal(1, 0, 0);

		//m_impl_plane_widget2->Off();*
			vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(m_interactor->GetInteractorStyle());
			if (style)
				style->OnMouseMove();

			/*
			int lastPos[2];
			m_interactor->GetLastEventPosition(lastPos);
			int currPos[2];
			m_interactor->GetEventPosition(currPos);
			if (event == vtkCommand::LeftButtonPressEvent)
				m_slicing = 1;
			else if (event == vtkCommand::LeftButtonReleaseEvent)
				m_slicing = 0;
			else if (event == vtkCommand::MouseMoveEvent) {
				if (m_slicing) {
					// Increment slice position by deltaY of mouse
					int deltaY = lastPos[1] - currPos[1];
					m_reslice->Update();
					double sliceSpacing = m_reslice->GetOutput()->GetSpacing()[2];
					vtkMatrix4x4* matrix = m_reslice->GetResliceAxes();
					// move the center point that we are slicing through
					double point[4];
					double center[4];
					point[0] = 0.0;
					point[1] = 0.0;
					point[2] = sliceSpacing * deltaY;
					point[3] = 1.0;
					matrix->MultiplyPoint(point, center);
					matrix->SetElement(0, 3, center[0]);
					matrix->SetElement(1, 3, center[1]);
					matrix->SetElement(2, 3, center[2]);
					m_interactor->Render();
				}

		// Matrices for axial, coronal, sagittal, oblique view orientations
// static double axialElements[16] = {
//         1, 0, 0, 0,
//         0, 1, 0, 0,
//         0, 0, 1, 0,
//         0, 0, 0, 1 };
// static double coronalElements[16] = {
//         1, 0, 0, 0,
//         0, 0, 1, 0,
//         0,-1, 0, 0,
//         0, 0, 0, 1 };
		// static double obliqueElements[16] = {
		//         1, 0, 0, 0,
		//         0, 0.866025, -0.5, 0,
		//         0, 0.5, 0.866025, 0,
		//         0, 0, 0, 1 };


			//calculate the orthogonal vectors to the normal
			double normal[3];
			m_pView->m_image_plane->GetNormal(normal);
			double origin[3];
			m_pView->m_image_plane->GetOrigin(origin);

			double plane[3] = { 1, 0, 0 };
			double ortho_1[3], ortho_2[3];
			vtkMath::Cross(normal, plane, ortho_1);
			vtkMath::Cross(normal, ortho_1, ortho_2);
			double el[16] = {
				ortho_1[0], ortho_2[0], normal[0], origin[0],
				ortho_1[1], ortho_2[1], normal[1], origin[1],
				ortho_1[2], ortho_2[2], normal[2], origin[2],
				0, 0, 0, 1 };
			vtkNew<vtkMatrix4x4> oblique;
			oblique->DeepCopy(el);

			m_pView->m_image_reslice->SetResliceAxes(oblique);

*/