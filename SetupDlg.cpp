#include <QFormLayout>
#include <QLabel>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QTabWidget>

#include "SetupDlg.h"
#include "Settings.h"
#include "ColorTables.h"

SetupDlg::SetupDlg(Settings* p) : m_settings(p)
{
	setWindowTitle("Настройки");
	
	QVBoxLayout* vbox = new QVBoxLayout;
	setLayout(vbox);
	setFixedSize(400, 340);

	QTabWidget* tab_wgt = new QTabWidget;
	vbox->addWidget(tab_wgt);
	{
		QFrame* frm = new QFrame;
		QFormLayout* layout = new QFormLayout();
		frm->setLayout(layout);
		tab_wgt->addTab(frm, "Камера");

		m_camera_X_pos = new QDoubleSpinBox;
		m_camera_X_pos->setRange(-1.e5, 1.e5);
		m_camera_X_pos->setValue(m_settings->m_camera_position[0]);
		m_camera_Y_pos = new QDoubleSpinBox;
		m_camera_Y_pos->setRange(-1.e5, 1.e5);
		m_camera_Y_pos->setValue(m_settings->m_camera_position[1]);
		m_camera_Z_pos = new QDoubleSpinBox;
		m_camera_Z_pos->setRange(-1.e5, 1.e5);
		m_camera_Z_pos->setValue(m_settings->m_camera_position[2]);

		QHBoxLayout* hbox = new QHBoxLayout;
		hbox->addWidget(m_camera_X_pos);
		hbox->addWidget(m_camera_Y_pos);
		hbox->addWidget(m_camera_Z_pos);
		layout->addRow("Камера", hbox);

		m_camera_X_FP = new QDoubleSpinBox;
		m_camera_X_FP->setRange(-1.e5, 1.e5);
		m_camera_X_FP->setValue(m_settings->m_camera_position[0]);
		m_camera_Y_FP = new QDoubleSpinBox;
		m_camera_Y_FP->setRange(-1.e5, 1.e5);
		m_camera_Y_FP->setValue(m_settings->m_camera_position[1]);
		m_camera_Z_FP = new QDoubleSpinBox;
		m_camera_Z_FP->setRange(-1.e5, 1.e5);
		m_camera_Z_FP->setValue(m_settings->m_camera_position[2]);

		QHBoxLayout* hbox1 = new QHBoxLayout;
		hbox1->addWidget(m_camera_X_FP);
		hbox1->addWidget(m_camera_Y_FP);
		hbox1->addWidget(m_camera_Z_FP);
		layout->addRow("Фокус", hbox1);

		m_camera_X_up = new QDoubleSpinBox;
		m_camera_X_up->setRange(-1, 1);
		m_camera_X_up->setValue(m_settings->m_camera_view_up[0]);
		m_camera_Y_up = new QDoubleSpinBox;
		m_camera_Y_up->setRange(-1, 1);
		m_camera_Y_up->setValue(m_settings->m_camera_view_up[1]);
		m_camera_Z_up = new QDoubleSpinBox;
		m_camera_Z_up->setRange(-1, 1);
		m_camera_Z_up->setValue(m_settings->m_camera_view_up[2]);

		QHBoxLayout* hbox2 = new QHBoxLayout;
		hbox2->addWidget(m_camera_X_up);
		hbox2->addWidget(m_camera_Y_up);
		hbox2->addWidget(m_camera_Z_up);
		layout->addRow("Верх", hbox2);

		m_camera_par_scale = new QDoubleSpinBox;
		m_camera_par_scale->setRange(0, 1.e5);
		m_camera_par_scale->setValue(m_settings->m_camera_parallel_scale);
		layout->addRow("Масштаб", m_camera_par_scale);
	}
	{
		QFrame* frm = new QFrame;
		QFormLayout* layout = new QFormLayout();
		frm->setLayout(layout);
		tab_wgt->addTab(frm, "Оформление");

		m_bkg_color = new QPushButton;
		layout->addRow("Цвет фона", m_bkg_color);
		QString qss = QString("background-color: %1").arg(m_settings->m_bkg_color.name());
		m_bkg_color->setStyleSheet(qss);

		m_paletter = new QComboBox;
		for (int i = 0; i < ColorTables_num; i++)
			m_paletter->addItem(ColorTables_names[i]);
		m_paletter->setCurrentIndex(m_settings->m_palette_idx);
		layout->addRow("Палитра GL-вида", m_paletter);
	}
	QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
	vbox->addWidget(buttonBox);

	connect(m_bkg_color, SIGNAL(clicked()), this, SLOT(changeColor()));
	connect(buttonBox, SIGNAL(accepted()), this, SLOT(acceptSettings()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(rejectSettings()));
}

void SetupDlg::changeColor()
{
	m_settings->m_bkg_color = QColorDialog::getColor(m_settings->m_bkg_color, this);

	QString qss = QString("background-color: %1").arg(m_settings->m_bkg_color.name());
	m_bkg_color->setStyleSheet(qss);
}

void SetupDlg::acceptSettings()
{
	m_settings->m_bkg_color = m_bkg_color->palette().color(QPalette::Button);
	m_settings->m_palette_idx = m_paletter->currentIndex();
	if (m_settings->m_palette_idx == -1)
		m_settings->m_palette_idx = 0;

	close();
	setResult(QDialog::Accepted);
}

void SetupDlg::rejectSettings()
{
	close();
	setResult(QDialog::Rejected);
}
