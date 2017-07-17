#include <fstream>

#include <QAction>
#include <QErrorMessage>
#include <QMessageBox>
#include <QFileDialog>
#include <QStatusBar>
#include <QTimer>

#include <device/Device.hpp>

#include <MainWindow.hpp>
#include <MainWindowInterface.hpp>
#include <DeviceDockWidget.hpp>
#include <ConfigurableDeviceDockWidget.hpp>
#include <DeviceDialog.hpp>
#include <CommandPanel.hpp>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	  ui_(new interface::MainWindow)
{
	ui_->setupInterface(this);
	setupEvents();

	fetchConfiguration();
}

void MainWindow::setupEvents()
{
	connect(ui_->fetchConfigurationAction, &QAction::triggered,
			this, &MainWindow::fetchConfiguration);
	connect(ui_->openDeviceAction, &QAction::triggered,
			this, &MainWindow::openDevice);
	connect(ui_->aboutAction, &QAction::triggered,
			this, &MainWindow::about);
	connect(ui_->aboutQtAction, &QAction::triggered,
			this, &MainWindow::aboutQt);

	QList<DeviceDockWidget*> panels = findChildren<DeviceDockWidget*>();
	for (auto &panel : panels) {
		connect(this, &MainWindow::deviceOpened,
				panel, &DeviceDockWidget::receiveDevice);
		connect(panel, &DeviceDockWidget::ioErrorOccured,
				[=](const QString& error){
			statusBar()->setStyleSheet("QStatusBar { color: red }");
			statusBar()->showMessage(error, 2000);
		});
	}

	QList<ConfigurableDeviceDockWidget*> configurablePanels
			= findChildren<ConfigurableDeviceDockWidget*>();
	for (auto &panel : configurablePanels) {
		connect(this, &MainWindow::configurationFetched,
				panel, &ConfigurableDeviceDockWidget::receiveConfiguration);
	}

	QErrorMessage *errorMessage = new QErrorMessage(this);
	connect(this, SIGNAL(errorOccured(QString)),
			errorMessage, SLOT(showMessage(QString)));
}

MainWindow::~MainWindow()
{
	delete ui_;
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About"),
					   tr("This program aims to provide an high level interface to hardware devices"));
}

void MainWindow::aboutQt()
{
	QMessageBox::aboutQt(this);
}

void MainWindow::openDevice()
{
	static DeviceDialog *openDeviceDialog = new DeviceDialog(this);
	if (openDeviceDialog->exec()) {
		try {
			if (openDeviceDialog->deviceIsI2C()) {
				device_ = std::make_shared<Device>(openDeviceDialog->selectedDevice().toStdString(),
									 openDeviceDialog->deviceAddress(),
									 lua_);
			} else {
				device_ = std::make_shared<Device>(openDeviceDialog->selectedDevice().toStdString(),
									 lua_);
			}
		}
		catch (IOException e) {
			emit errorOccured(QString::fromStdString(e.what()));
			return;
		}

		emit deviceOpened(device_);
	}
}

void MainWindow::fetchConfiguration()
{
	QDir dir(QDir::homePath() + "/.config/DeviceInterface");
	dir.mkpath(".");

	if (!lua_ && QFile::exists(dir.absoluteFilePath(".last.lua"))) {
		lua_ = std::make_shared<sol::state>();
		lua_->script_file(dir.absoluteFilePath(".last.lua").toStdString());
		std::shared_ptr<Configuration> configuration =
				std::make_shared<Configuration>(lua_);
		emit configurationFetched(configuration);
		return;
	}

	QString configFileName =
			QFileDialog::getOpenFileName(this,
										 tr("Select a device config file"),
										 dir.path(),
										 tr("Config file (*.lua)"));
	if (!configFileName.isNull()) {
		lua_ = std::make_shared<sol::state>();
		lua_->script_file(configFileName.toStdString());
		QFile::copy(configFileName, dir.absoluteFilePath(QFileInfo(configFileName).fileName()));
		QFile::remove(dir.absoluteFilePath(".last.lua"));
		QFile::copy(configFileName, dir.absoluteFilePath(".last.lua"));
		std::shared_ptr<Configuration> configuration =
				std::make_shared<Configuration>(lua_);
		emit configurationFetched(configuration);
	}
}

//void MainWindow::resetLua()
//{
//	QDir dir(QDir::homePath() + "/.config/DeviceInterface");
//	delete configuration_;
//	configuration_ = new Configuration(dir.absoluteFilePath(".last.lua").toStdString());
//	emit configurationFetched(configuration_);
//}
