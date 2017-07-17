#ifndef DEVICEWIDGET_HPP
#define DEVICEWIDGET_HPP

#include <memory>

#include <QString>
#include <QWidget>

class Device;

class DeviceWidget : public QWidget
{
	Q_OBJECT
public:
	DeviceWidget(QWidget *parent = nullptr);

public slots:
	virtual void receiveDevice(std::shared_ptr<Device> device);

signals:
	void ioErrorOccured(const QString &message);

protected:
	virtual void activate();

	std::shared_ptr<Device> device_;
};

#endif // DEVICEWIDGET_HPP
