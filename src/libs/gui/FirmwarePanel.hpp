#ifndef FIRMWAREPANEL_HPP
#define FIRMWAREPANEL_HPP

#include "DeviceDockWidget.hpp"
#include "QDockWidget"
#include "FirmwarePanelInterface.hpp"

class FirmwarePanel : public DeviceDockWidget
{
	Q_OBJECT
public:
	FirmwarePanel(QWidget *parent = Q_NULLPTR);
    ~FirmwarePanel();
public slots:
	void toggleDevice(bool toggle);
	void setDim(int value);

private:
	void setupEvents();
	interface::FirmwarePanel *ui_;
};

#endif // FIRMWAREPANEL_HPP
