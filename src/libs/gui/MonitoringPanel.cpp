#include <QFrame>
#include <QTimer>
#include <QSizePolicy>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>

#include <gui/MonitoringPanel.hpp>
#include <gui/MonitoringPanelInterface.hpp>
#include <gui/ToggleButton.hpp>
#include <gui/UiPanelConfiguration.hpp>

MonitoringPanel::MonitoringPanel(QWidget *parent)
	: ConfigurableDeviceDockWidget(parent),
	  ui_(new interface::MonitoringPanel)

{
}

void MonitoringPanel::receiveConfiguration(std::shared_ptr<Configuration> configuration)
{
	ConfigurableDeviceDockWidget::receiveConfiguration(configuration);
	ui_->setupInterface(this, configuration_->getMonitoringPanelConfiguration());
}

void MonitoringPanel::receiveDevice(std::shared_ptr<Device> device)
{
	DeviceDockWidget::receiveDevice(device);

	monitorUpdateTimer_ = new QTimer(this);
	connect(monitorUpdateTimer_, SIGNAL(timeout()), this, SLOT(update()));

	connect(ui_->toggleMonitoringButton, SIGNAL(toggled(bool)),
			this, SLOT(toggleMonitor(bool)));
}


void MonitoringPanel::toggleMonitor(bool toggle)
{
	if (toggle) {
		monitorUpdateTimer_->start(1000);
	} else {
		monitorUpdateTimer_->stop();
	}
}

void MonitoringPanel::update()
{
	try {
		device_->update();
	}
	catch (const IOException &e) {
		emit ioErrorOccured(e.what());
		for (auto i = ui_->extraParameterValues.begin(); i != ui_->extraParameterValues.end(); ++i) {
			i.value()->setText("Error");
		}
		for (auto i = ui_->parameterValues.begin(); i != ui_->parameterValues.end(); ++i) {
			i.value()->setText("Error");
		}

		for (auto i = ui_->flagStatuses.begin(); i != ui_->flagStatuses.end(); ++i) {
			i.value()->setText("Error");
		}
		return;
	}

	for (auto i = ui_->extraParameterValues.begin(); i != ui_->extraParameterValues.end(); ++i) {
		i.value()->setText(QString::number(
							   static_cast<uint32_t>(
								   device_->getExtraParameterValue(i.key().toStdString()))));
	}

	for (auto i = ui_->parameterValues.begin(); i != ui_->parameterValues.end(); ++i) {
		i.value()->setText(QString::number(
							   static_cast<uint32_t>(
								   device_->getParameterValue(i.key().toStdString()))));
	}

	for (auto i = ui_->flagStatuses.begin(); i != ui_->flagStatuses.end(); ++i) {
		i.value()->setText(device_->getFlagStatus(i.key().toStdString()) ? "On" : "Off");
	}
}
