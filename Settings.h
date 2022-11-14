#pragma once

#include <QString>
#include <QColor>

class QSettings;

class Settings
{
public:
	QString m_ini_path;
	QColor m_bkg_color;
	double m_scalar_threshold = 0;
	double m_camera_position[3]{ 0, 0, 0 };
	double m_camera_focal_point[3]{ 0, 0, 0 };
	double m_camera_view_up[3]{ 0, 0, 0 };
	double m_camera_parallel_scale = 0;
	double m_actor_position[3]{ 0, 0, 0 };
	int m_palette_idx = 0;

	QSettings* m_settings = nullptr;

	Settings();
	void Save();
};

