#ifndef DEVICEDIALOGINTERFACE_HPP
#define DEVICEDIALOGINTERFACE_HPP

class QDialog;
class QGroupBox;
class QLabel;
class QComboBox;
class IntLineEdit;
class QPushButton;
class QLineEdit;
class QDialogButtonBox;
class QWidget;
class QStackedWidget;

namespace interface
{

class DeviceDialog
{
public:
	QComboBox *deviceTypeComboBox;
	QStackedWidget *deviceStackedWidget;

	// when device type is a known device type (UART, I2C, etc.)
	QWidget *genericDeviceWidget;
	QComboBox *devicesComboBox;
	QLabel *deviceInfoLabel;

	// only for i2c devices
	QWidget *i2cDeviceWidget;
	QComboBox *i2cDevicesComboBox;
	QLabel *i2cDeviceInfoLabel;
//	QPushButton *busScanButton;
	// mutually exclusive
//	QComboBox *i2cAddressComboBox;
	IntLineEdit *i2cAddressEdit;

	// when user wants to open anything as a file with basic open and write APIs
	QWidget *miscWidget;
	QLineEdit *pathEdit;
	QPushButton *openFileDialogButton;

	QDialogButtonBox *buttonBox;

	void setupInterface(QDialog *dialog);
};

}

#endif // DEVICEDIALOGINTERFACE_HPP
