#ifndef DEVICEDIALOG_HPP
#define DEVICEDIALOG_HPP

#include <QDialog>
#include <QVector>
#include <QPair>

namespace interface {
class DeviceDialog;
}

#include <qt_adapter/DeviceInfoAdapter.hpp>

class DeviceDialog : public QDialog
{
	Q_OBJECT
public:
	DeviceDialog(QWidget *parent = nullptr);
    ~DeviceDialog();

	bool deviceIsI2C() const;
	QString selectedDevice() const;
	uint16_t deviceAddress() const;

private slots:
	void changeStackedWidget(const QString &name);
	void showDeviceInformation(int comboBoxIndex);
	void fillDevicesComboBox(const QString &name);
	void browse();
//	void resetAddressToEdit();
//	void resetAddressToEdit(const QString &comboBoxItemText);

//	// just for i2c
//	void busScan();
	void accept() override;

private:
	void setupEvents();

	adapter::qt::DeviceInfo *selectedDevice_ ;
	uint16_t deviceAddress_ ;
	QVector<adapter::qt::DeviceInfo> devicesInfo_;
	interface::DeviceDialog *ui_;

};

#endif // DEVICEDIALOG_HPP
