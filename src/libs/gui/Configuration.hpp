#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <memory>

#include <device/DeviceValues.hpp>
#include <UiPanelConfiguration.hpp>
#include <qt_adapter/ParameterAdapter.hpp>
#include <qt_adapter/FlagAdapter.hpp>
#include <qt_adapter/RegisterAdapter.hpp>
#include <qt_adapter/ExtraParameterAdapter.hpp>

class Configuration
{
public:
	Configuration(std::shared_ptr<sol::state> lua);

	adapter::qt::Parameter getParameter(const QString &name);
	adapter::qt::ExtraParameter getExtraParameter(const QString &name);
	adapter::qt::Register getRegister(const QString &name);
	adapter::qt::Flag getFlag(const QString &name);

	const UiPanelConfiguration& getConfigurePanelConfiguration();
	const UiPanelConfiguration& getMonitoringPanelConfiguration();

private:
	std::unique_ptr<UiPanelConfiguration> configurePanelConfiguration_;
	std::unique_ptr<UiPanelConfiguration> monitoringPanelConfiguration_;

    std::unique_ptr<DeviceStructure> deviceStructure_;
};

#endif // CONFIGURATION_HPP
