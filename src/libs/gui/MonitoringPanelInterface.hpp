#ifndef MONITORINGPANELINTERFACE_HPP
#define MONITORINGPANELINTERFACE_HPP

#include <ConfigurableUiInterface.hpp>

#include <QMap>

class QDockWidget;
class QLabel;
class ToggleButton;

class DeviceConfiguration;
class UiPanelConfiguration;

namespace interface
{
class MonitoringPanel : public ConfigurableUiInterface
{
public:
	QMap<QString, QLabel*> parameterValues;
	QMap<QString, QLabel*> extraParameterValues;
	QMap<QString, QLabel*> flagStatuses;
	ToggleButton *toggleMonitoringButton;

	virtual void clearInterface(QWidget *widget) override;
	void setupInterface(QDockWidget *widget,
						const UiPanelConfiguration &uiConfig);
};

}

#endif // MONITORINGPANELINTERFACE_HPP
