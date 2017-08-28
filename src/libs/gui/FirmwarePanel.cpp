#include <FirmwarePanel.hpp>
#include <FirmwarePanelInterface.hpp>
#include <ToggleButton.hpp>
#include <device/DeviceStream.hpp>

#include <QLabel>
#include <QSlider>
#include <QSizePolicy>
#include <QFrame>
#include <QGridLayout>

FirmwarePanel::FirmwarePanel(QWidget *parent)
	: DeviceDockWidget(parent),
	  ui_(new interface::FirmwarePanel)
{
	ui_->setupInterface(this);
	setupEvents();
}
FirmwarePanel::~FirmwarePanel()
{
    delete ui_;
}

void FirmwarePanel::setupEvents()
{
	connect(ui_->deviceToggleButton, &ToggleButton::toggled,
			this, &FirmwarePanel::toggleDevice);
	connect(ui_->dimSlider, &QSlider::valueChanged,
			this, &FirmwarePanel::setDim);
}

void FirmwarePanel::toggleDevice(bool toggle)
{
	device_->setBufferedIO(false);
	if (toggle) {
		device_->setParameterValue("dim",device_->getParameterValue("dim"));
	} else {
		device_->setParameterValue("dim", 0);
	}
	device_->setBufferedIO(true);
}

void FirmwarePanel::setDim(int value)
{
	device_->setBufferedIO(false);
	device_->setParameterValue("dim", value);
	device_->setBufferedIO(true);
}
