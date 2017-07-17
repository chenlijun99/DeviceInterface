#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <memory>

#include <QMainWindow>

#include <sol.hpp>

#include <device/Device.hpp>

#include <Configuration.hpp>

namespace interface {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
	void deviceOpened(std::shared_ptr<Device> device);
	void configurationFetched(std::shared_ptr<Configuration> configuration);
	void errorOccured(const QString &errorMessage);

public slots:
	void openDevice();
	void fetchConfiguration();

	void aboutQt();
	void about();
//	void resetLua();
private:
	void setupEvents();

	interface::MainWindow *ui_;

	std::shared_ptr<Device> device_;
	std::shared_ptr<sol::state> lua_;
};

#endif // MAINWINDOW_H
