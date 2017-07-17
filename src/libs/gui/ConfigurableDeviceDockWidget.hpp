#ifndef CONFIGURABLEDEVICEDOCKWIDGET_HPP
#define CONFIGURABLEDEVICEDOCKWIDGET_HPP

#include <DeviceDockWidget.hpp>
#include <Configuration.hpp>

#include <sol.hpp>

class ConfigurableDeviceDockWidget : public DeviceDockWidget
{
	Q_OBJECT
public:
	ConfigurableDeviceDockWidget(QWidget *parent = nullptr);

public slots:
	virtual void receiveConfiguration(std::shared_ptr<Configuration> configuration);
	virtual void activate() override;

protected:
	std::shared_ptr<Configuration> configuration_;
};

#endif // CONFIGURABLEDEVICEDOCKWIDGET_HPP
