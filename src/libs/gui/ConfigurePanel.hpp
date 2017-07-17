#ifndef CONFIGUREPANEL_HPP
#define CONFIGUREPANEL_HPP

#include <ConfigurePanelInterface.hpp>

#include <ConfigurableDeviceDockWidget.hpp>

class ConfigurePanel : public ConfigurableDeviceDockWidget
{
	Q_OBJECT
public:
	ConfigurePanel(QWidget *parent = nullptr);

public slots:
	virtual void receiveConfiguration(std::shared_ptr<Configuration> configuration);
	void configure();

private:
	interface::ConfigurePanel *ui_;
};

#endif // CONFIGUREPANEL_H
