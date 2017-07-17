#ifndef MONITORINGPANEL_HPP
#define MONITORINGPANEL_HPP

#include <QDockWidget>

#include <sol.hpp>

#include <ConfigurableDeviceDockWidget.hpp>

namespace interface {
class MonitoringPanel;
}

class MonitoringPanel : public ConfigurableDeviceDockWidget
{
	Q_OBJECT
public:
	MonitoringPanel(QWidget *parent = Q_NULLPTR);
public slots:
	void receiveConfiguration(std::shared_ptr<Configuration> device);
	void receiveDevice(std::shared_ptr<Device> device) override;
	void toggleMonitor(bool toggle);
	void update();
private:
	interface::MonitoringPanel *ui_;
	QTimer *monitorUpdateTimer_;
};

#endif // MONITORINGPANEL_HPP
