#include "ConfigurableDeviceDockWidget.hpp"

ConfigurableDeviceDockWidget::ConfigurableDeviceDockWidget(QWidget *parent)
	: DeviceDockWidget(parent)
{
	setEnabled(false);
}


void ConfigurableDeviceDockWidget::receiveConfiguration(std::shared_ptr<Configuration> configuration)
{
	configuration_ = configuration;
	activate();
}

void ConfigurableDeviceDockWidget::activate()
{
	setEnabled(configuration_ && device_);
}
