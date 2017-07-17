#ifndef MAINWINDOWINTERFACE_HPP
#define MAINWINDOWINTERFACE_HPP


class CommandPanel;
class ConfigurePanel;
class MonitoringPanel;
class FirmwarePanel;

class QMainWindow;
class QMenu;
class QAction;

namespace interface
{

class MainWindow
{
public:
	QMenu *configurationMenu;
	QAction *fetchConfigurationAction;
	QMenu *deviceMenu;
	QAction *openDeviceAction;
	QMenu *helpMenu;
	QAction *aboutAction;
	QAction *aboutQtAction;

	CommandPanel *commandPanel;
	ConfigurePanel *configurePanel;
	FirmwarePanel *firmwarePanel;
	MonitoringPanel *monitoringPanel;

	void setupInterface(QMainWindow *mainWindow);

private:
	void setupMenuBar(QMainWindow *mainWindow);
	void centerAndResize(QMainWindow *mainWindow);
};

}

#endif // MAINWINDOWINTERFACE_H
