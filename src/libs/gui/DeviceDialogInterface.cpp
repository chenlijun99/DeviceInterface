#include <DeviceDialogInterface.hpp>
#include <IntLineEdit.hpp>

#include <QObject>
#include <QDialog>
#include <QGroupBox>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>


namespace interface {

void DeviceDialog::setupInterface(QDialog *dialog)
{
	QLabel *chooseDeviceLabel = new QLabel(QObject::tr("Choose a device"));
	const char defaultInfoText[] = "Device node:\n"
								   "Manufacturer:\n"
								   "Product:\n"
								   "Vendor id:\n"
								   "Product id:\n" ;

	QGridLayout *genericDeviceWidgetLayout = new QGridLayout;
	genericDeviceWidget = new QWidget;
	devicesComboBox = new QComboBox();
	deviceInfoLabel = new QLabel(QObject::tr(defaultInfoText));
	genericDeviceWidgetLayout->addWidget(chooseDeviceLabel, 0, 0);
	genericDeviceWidgetLayout->addWidget(devicesComboBox, 0, 1);
	genericDeviceWidgetLayout->addWidget(deviceInfoLabel, 1, 0, 1, 2);
	genericDeviceWidget->setLayout(genericDeviceWidgetLayout);

	QGridLayout *i2cDeviceWidgetLayout = new QGridLayout;
	i2cDeviceWidget = new QWidget;
	i2cDevicesComboBox = new QComboBox();
	chooseDeviceLabel = new QLabel(QObject::tr("Choose a device"));
	i2cDeviceInfoLabel = new QLabel(QObject::tr(defaultInfoText));
	i2cAddressEdit = new IntLineEdit;
	i2cAddressEdit->setRange(0, 127);
	i2cAddressEdit->setPlaceholderText(QObject::tr("Range: 0-127"));
//	i2cAddressComboBox = new QComboBox;
//	i2cAddressComboBox->hide();
//	busScanButton = new QPushButton(QObject::tr("Bus scan"));
//	busScanButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QLabel *deviceAddressLabel = new QLabel(QObject::tr("Address"));
	i2cDeviceWidgetLayout->addWidget(chooseDeviceLabel, 0, 0);
	i2cDeviceWidgetLayout->addWidget(i2cDevicesComboBox, 0, 1);
	i2cDeviceWidgetLayout->addWidget(i2cDeviceInfoLabel, 1, 0, 1, 2);
	i2cDeviceWidgetLayout->addWidget(deviceAddressLabel, 2, 0);
	i2cDeviceWidgetLayout->addWidget(i2cAddressEdit, 2, 1);
//	i2cDeviceWidgetLayout->addWidget(i2cAddressComboBox, 2, 1);
//	i2cDeviceWidgetLayout->addWidget(busScanButton, 2, 2, Qt::AlignRight);
	i2cDeviceWidget->setLayout(i2cDeviceWidgetLayout);

	QGridLayout *miscWidgetLayout = new QGridLayout;
	miscWidget = new QWidget;
	QLabel *pathEditLabel = new QLabel(QObject::tr("Edit"));
	pathEdit = new QLineEdit;
	openFileDialogButton = new QPushButton(QObject::tr("Browse"));
	miscWidgetLayout->addWidget(pathEditLabel, 0, 0);
	miscWidgetLayout->addWidget(pathEdit, 0, 1);
	miscWidgetLayout->addWidget(openFileDialogButton, 0, 2);
	miscWidget->setLayout(miscWidgetLayout);

	deviceStackedWidget = new QStackedWidget;
	deviceStackedWidget->addWidget(genericDeviceWidget);
	deviceStackedWidget->addWidget(i2cDeviceWidget);
	deviceStackedWidget->addWidget(miscWidget);
	QGridLayout *deviceGroupLayout = new QGridLayout;
	deviceGroupLayout->addWidget(deviceStackedWidget, 0, 0);
	QGroupBox *deviceGroup = new QGroupBox(QObject::tr("Device"), dialog);
	deviceGroup->setLayout(deviceGroupLayout);

	QHBoxLayout *deviceTypeLayout = new QHBoxLayout;
	QLabel *deviceTypeLabel = new QLabel(QObject::tr("Device type"));
	deviceTypeComboBox = new QComboBox;
	deviceTypeComboBox->addItems(QStringList() << "Generic" << "I2C" << "Misc");
	deviceTypeLayout->addWidget(deviceTypeLabel);
	deviceTypeLayout->addWidget(deviceTypeComboBox);

	// setup button box
	buttonBox = new QDialogButtonBox();
	buttonBox->addButton(QObject::tr("Connect"), QDialogButtonBox::AcceptRole);
	buttonBox->addButton(QDialogButtonBox::Cancel);

	// arrange all together
	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addLayout(deviceTypeLayout, 0, 0);
	mainLayout->addWidget(deviceGroup, 1, 0);
	mainLayout->addWidget(buttonBox, 2, 0);

	dialog->setLayout(mainLayout);
	dialog->setWindowTitle(QObject::tr("Select a device"));
}

}
