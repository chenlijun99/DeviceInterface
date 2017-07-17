#ifndef DEVICEDOCKWIDGET_HPP
#define DEVICEDOCKWIDGET_HPP

#include <QDockWidget>

#include <device/Device.hpp>

class DeviceDockWidget : public QDockWidget
{
	Q_OBJECT
public:
	DeviceDockWidget(QWidget *parent = nullptr);

public slots:
	virtual void receiveDevice(std::shared_ptr<Device> device);

signals:
	void ioErrorOccured(const QString &message);

protected:
	virtual void activate();

	std::shared_ptr<Device> device_;
};

#endif // DEVICEDOCKWIDGET_HPP
