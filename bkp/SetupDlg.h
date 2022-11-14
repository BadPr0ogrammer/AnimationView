#pragma once

#include <QDialog>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QComboBox>

class Settings;

class SetupDlg : public QDialog
{
	Q_OBJECT
public:
	Settings* m_settings = nullptr;
	QPushButton* m_bkg_color = nullptr;
	QDoubleSpinBox* m_camera_X_pos = nullptr, *m_camera_Y_pos = nullptr, *m_camera_Z_pos = nullptr;
	QDoubleSpinBox* m_camera_X_FP = nullptr, *m_camera_Y_FP = nullptr, *m_camera_Z_FP = nullptr;
	QDoubleSpinBox* m_camera_X_up = nullptr, * m_camera_Y_up = nullptr, * m_camera_Z_up = nullptr;
	QDoubleSpinBox* m_camera_par_scale = nullptr;
	QComboBox* m_paletter = nullptr;

	SetupDlg(Settings* p);

public slots:
	void changeColor();
	void acceptSettings();
	void rejectSettings();
};
