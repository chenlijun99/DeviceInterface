#include <DeviceDialog.hpp>
#include <DeviceDialogInterface.hpp>

#include <IntLineEdit.hpp>

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QFileDialog>

DeviceDialog::DeviceDialog(QWidget *parent)
	: QDialog(parent),
	  ui_(new interface::DeviceDialog())

{
	ui_->setupInterface(this);
	setupEvents();
}

DeviceDialog::~DeviceDialog()
{
    delete ui_;
}

void DeviceDialog::setupEvents()
{
	/*
	 * when overloaded signals/slots are involved, the old connect syntax is easier
	 * connect(portsComboBox_, static_cast<void (QComboBox::*)(int)>(&QComboBox::activated),
	 *      this, &DeviceSelectDialog::showDeviceInformation);
	 */

	// update device informations whenever user selects a i device in the combo box
	connect(ui_->devicesComboBox, SIGNAL(activated(int)),
			this, SLOT(showDeviceInformation(int)));
	// set initial item at the first
	emit ui_->devicesComboBox->activated(0);

	connect(ui_->deviceTypeComboBox, SIGNAL(activated(QString)),
			this, SLOT(changeStackedWidget(QString)));

	connect(ui_->deviceTypeComboBox, SIGNAL(activated(QString)),
			this, SLOT(fillDevicesComboBox(QString)));
	emit ui_->deviceTypeComboBox->activated("Generic");

	connect(ui_->openFileDialogButton, SIGNAL(clicked(bool)),
			this, SLOT(browse()));

//	// when user selects another device reset to address edit
//	connect(devicesComboBox_, SIGNAL(currentIndexChanged(int)),
//			this, SLOT(resetAddressToEdit()));

//	// search for available slaves through a sort of ping to slaves
//	connect(slaveSearchButton_, &QPushButton::clicked,
//			this, &DeviceDialog::busScan);

//	// whenver the item of combo box is changed, check if the current item
//	// is edit
//	connect(slaveAddressComboBox_, SIGNAL(currentIndexChanged(QString)),
//			this, SLOT(resetAddressToEdit(QString)));


	connect(ui_->buttonBox, &QDialogButtonBox::accepted,
			this, &DeviceDialog::accept);
	connect(ui_->buttonBox, &QDialogButtonBox::rejected,
			this, &DeviceDialog::reject);
}

void DeviceDialog::fillDevicesComboBox(const QString &name)
{
	using adapter::qt::DeviceInfo;
	if (name == "Generic") {
		devicesInfo_ = DeviceInfo::availableDevices("tty");
		ui_->devicesComboBox->clear();
		for (const DeviceInfo &deviceInfo : devicesInfo_) {
			ui_->devicesComboBox->addItem(deviceInfo.shortDescription());
		}
	}

	if (name == "I2C") {
		devicesInfo_ = DeviceInfo::availableDevices("i2c-dev");
		ui_->i2cDevicesComboBox->clear();
		for (const DeviceInfo &deviceInfo : devicesInfo_) {
			ui_->i2cDevicesComboBox->addItem(deviceInfo.shortDescription());
		}
	}
}

void DeviceDialog::showDeviceInformation(int comboBoxIndex)
{
//	ui_->deviceInfoLabel->setText(devicesInfo_[comboBoxIndex].formattedDescription());
}

//void DeviceDialog::resetAddressToEdit()
//{
//	if (!slaveAddressComboBox_->isHidden()) {
//		slaveAddressComboBox_->hide();
//		slaveAddressEdit_->show();
//	}
//}

//void DeviceDialog::resetAddressToEdit(const QString &comboBoxItemText)
//{
//	if (comboBoxItemText == "Insert an address...")
//		resetAddressToEdit();
//}

//void DeviceDialog::busScan()
//{
//	slaveAddressComboBox_->clear();
//	slaveAddressEdit_->hide();
//	slaveAddressComboBox_->show();

//	QString currentDeviceNode = devicesInfo_[devicesComboBox_->currentIndex()].deviceNode();
//	QList<uint16_t> slavesAddresses = MasterDevice::availableSlaves(currentDeviceNode);

//	// fill combo box of slave addresses
//	for (auto &address : slavesAddresses)
//		slaveAddressComboBox_->addItem(QString::number(address));

//	// if there no slave is found, show this as the first item
//	if (slaveAddressComboBox_->count() == 0) {
//		slaveAddressComboBox_->addItem(tr("No slave found"));
//	}

//	// add a final item to allow user to go back and edit a custom address
//	slaveAddressComboBox_->addItem(tr("Insert an address..."));
//}

void DeviceDialog::accept()
{
	if (ui_->deviceStackedWidget->currentIndex() == 0 &&
			ui_->devicesComboBox->count() > 0) {
		goto accept;
	}
	if (ui_->deviceStackedWidget->currentIndex() == 1 &&
			ui_->i2cDevicesComboBox->count() > 0) {
		if (!ui_->i2cAddressEdit->text().isEmpty()) {
			goto accept;
		}
	}

	if (!ui_->pathEdit->text().isEmpty()) {
		goto accept;
	}

	return;
accept:
	if (ui_->deviceStackedWidget->currentIndex() == 0)
		selectedDevice_ = &devicesInfo_[ui_->devicesComboBox->currentIndex()];
	if (ui_->deviceStackedWidget->currentIndex() == 1)
		selectedDevice_ = &devicesInfo_[ui_->i2cDevicesComboBox->currentIndex()];
	QDialog::accept();
}

void DeviceDialog::changeStackedWidget(const QString &name)
{
	if (name == "Generic") {
		ui_->deviceStackedWidget->setCurrentIndex(0);
	} else if (name == "I2C") {
		ui_->deviceStackedWidget->setCurrentIndex(1);
	} else {
		ui_->deviceStackedWidget->setCurrentIndex(2);
	}
}

QString DeviceDialog::selectedDevice() const
{
	if (ui_->deviceStackedWidget->currentIndex() != 2)
		return selectedDevice_->deviceNode();
	return ui_->pathEdit->text();
}

void DeviceDialog::browse()
{
	ui_->pathEdit->setText(QFileDialog::getOpenFileName(this, tr("Open"), "/dev/"));
}

bool DeviceDialog::deviceIsI2C() const
{
	return ui_->deviceStackedWidget->currentIndex() == 1;
}

uint16_t DeviceDialog::deviceAddress() const
{
	return ui_->i2cAddressEdit->number();
}
