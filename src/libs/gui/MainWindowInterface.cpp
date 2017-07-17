#include <MainWindowInterface.hpp>

#include <CommandPanel.hpp>
#include <ConfigurePanel.hpp>
#include <MonitoringPanel.hpp>
#include <FirmwarePanel.hpp>

#include <QObject>
#include <QDesktopWidget>
#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QMenu>
#include <QLayout>
#include <QStyle>
#include <QAction>
#include <QMessageBox>
#include <QErrorMessage>
#include <QSize>

namespace interface {

void MainWindow::setupInterface(QMainWindow *mainWindow)
{
    setupMenuBar(mainWindow);
	commandPanel = new ::CommandPanel(mainWindow);
	configurePanel = new ::ConfigurePanel(mainWindow);
	firmwarePanel = new ::FirmwarePanel(mainWindow);
	monitoringPanel = new ::MonitoringPanel(mainWindow);
	mainWindow->addDockWidget(Qt::LeftDockWidgetArea, configurePanel);
	mainWindow->addDockWidget(Qt::RightDockWidgetArea, firmwarePanel);
	mainWindow->addDockWidget(Qt::RightDockWidgetArea, monitoringPanel);
	mainWindow->setCentralWidget(commandPanel);
	mainWindow->statusBar()->show();
	centerAndResize(mainWindow);
}

void MainWindow::setupMenuBar(QMainWindow *mainWindow)
{
	deviceMenu = mainWindow->menuBar()->addMenu(QObject::tr("&Device"));
	openDeviceAction = deviceMenu->addAction(QObject::tr("Open Device"));

	configurationMenu = mainWindow->menuBar()->addMenu(QObject::tr("&Configuration"));
	fetchConfigurationAction = configurationMenu->addAction(QObject::tr("Open Configuration"));

	helpMenu = mainWindow->menuBar()->addMenu(QObject::tr("&Help"));
	aboutAction = helpMenu->addAction(QObject::tr("About"));
	aboutQtAction = helpMenu->addAction(QObject::tr("About Qt"));
}

void MainWindow::centerAndResize(QMainWindow *mainWindow)
{
    // get the dimension available on this screen
    QSize availableSize = qApp->desktop()->availableGeometry().size();

    int width = availableSize.width();
    int height = availableSize.height();

    // use 90 %
    width *= 0.9;
    height *= 0.9;

    QSize newSize(width, height);

    mainWindow->setGeometry(QStyle::alignedRect(
                                Qt::LeftToRight,
                                Qt::AlignCenter,
                                newSize,
                                qApp->desktop()->availableGeometry()
                                ));
}

} // end of namespace interface
