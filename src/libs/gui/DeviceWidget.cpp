#include <DeviceWidget.hpp>

DeviceWidget::DeviceWidget(QWidget *parent)
	: QWidget(parent)
{
	setEnabled(false);
}


void DeviceWidget::receiveDevice(std::shared_ptr<Device> device)
{
	device_ = device;
	activate();
}

void DeviceWidget::activate()
{
	if (device_)
		setEnabled(true);
}
