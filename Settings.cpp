#include <QStandardPaths>
#include <QMessageBox>
#include <QDir>
#include <QSettings>

#include "Settings.h"

Settings::Settings()
{
	QString s = QStandardPaths::writableLocation(
#ifdef _WINDOWS
		QStandardPaths::DocumentsLocation
#else
		QStandardPaths::HomeLocation
#endif
	);
	if (!s.isEmpty()) {
		m_ini_path = s + QDir::separator() + "VtuAnimationView";
		QDir dir;
		if (!dir.exists(m_ini_path))
			dir.mkpath(m_ini_path);
		m_ini_path += QDir::separator();
		m_ini_path += "config.ini";

		delete m_settings;
		m_settings = new QSettings(m_ini_path, QSettings::IniFormat);
		if (m_settings->status() == QSettings::NoError) {

			m_bkg_color = QColor(m_settings->value("BkgColor").toString());
			m_scalar_threshold = m_settings->value("ScalarThreshold").toDouble();
			m_camera_position[0] = m_settings->value("CameraPositionX").toDouble();
			m_camera_position[1] = m_settings->value("CameraPositionY").toDouble();
			m_camera_position[2] = m_settings->value("CameraPositionZ").toDouble();			
			m_camera_focal_point[0] = m_settings->value("CameraFocalPointX").toDouble();
			m_camera_focal_point[1] = m_settings->value("CameraFocalPointY").toDouble();
			m_camera_focal_point[2] = m_settings->value("CameraFocalPointZ").toDouble();
			m_camera_view_up[0] = m_settings->value("CameraViewUpX").toDouble();
			m_camera_view_up[1] = m_settings->value("CameraViewUpY").toDouble();
			m_camera_view_up[2] = m_settings->value("CameraViewUpZ").toDouble();
			m_camera_parallel_scale = m_settings->value("CameraParallelScale").toDouble();
			m_palette_idx = m_settings->value("PaletteIndex").toInt();
			m_actor_position[0] = m_settings->value("ActorPositionX").toDouble();
			m_actor_position[1] = m_settings->value("ActorPositionY").toDouble();
			m_actor_position[2] = m_settings->value("ActorPositionZ").toDouble();
			return;
		}
	}
	delete m_settings;
	m_settings = nullptr;
	QMessageBox::warning(nullptr, "VtuAnimationView", "Файл настроек не создан");
}

void Settings::Save()
{
	if (m_settings->status() != QSettings::NoError) {
		QMessageBox::warning(nullptr, "VtuAnimationView", "Файл настроек не создан");
		return;
	}
	m_settings->setValue("BkgColor", m_bkg_color.name());
	m_settings->setValue("ScalarThreshold", m_scalar_threshold);
	m_settings->setValue("CameraPositionX", m_camera_position[0]);
	m_settings->setValue("CameraPositionY", m_camera_position[1]);
	m_settings->setValue("CameraPositionZ", m_camera_position[2]);
	m_settings->setValue("CameraFocalPointX", m_camera_focal_point[0]);
	m_settings->setValue("CameraFocalPointY", m_camera_focal_point[1]);
	m_settings->setValue("CameraFocalPointZ", m_camera_focal_point[2]);
	m_settings->setValue("CameraViewUpX", m_camera_view_up[0]);
	m_settings->setValue("CameraViewUpY", m_camera_view_up[1]);
	m_settings->setValue("CameraViewUpZ", m_camera_view_up[2]);
	m_settings->setValue("CameraParallelScale", m_camera_parallel_scale);
	m_settings->setValue("PaletteIndex", m_palette_idx);
	m_settings->setValue("ActorPositionX", m_actor_position[0]);
	m_settings->setValue("ActorPositionY", m_actor_position[1]);
	m_settings->setValue("ActorPositionZ", m_actor_position[2]);

	m_settings->sync();
}
