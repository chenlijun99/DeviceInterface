#include <DeviceDockWidget.hpp>

DeviceDockWidget::DeviceDockWidget(QWidget *parent)
	: QDockWidget(parent)
{
	setEnabled(false);
}


void DeviceDockWidget::receiveDevice(std::shared_ptr<Device> device)
{
	device_ = device;
	activate();
}

void DeviceDockWidget::activate()
{
	setEnabled(device_ ? true : false);
}
