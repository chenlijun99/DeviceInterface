#include <Configuration.hpp>

Configuration::Configuration(std::shared_ptr<sol::state> lua)
{
	sol::table interface = lua->get<sol::table>("interface");
	configurePanelConfiguration_ =
			std::make_unique<UiPanelConfiguration>
			(interface.get<sol::table>("configure_panel"));
	monitoringPanelConfiguration_ =
			std::make_unique<UiPanelConfiguration>
			(interface.get<sol::table>("monitoring_panel"));

	deviceStructure_ =
			std::make_unique<DeviceValues>
			(lua->get<sol::table>("device"));
}

adapter::qt::Parameter Configuration::getParameter(const QString &name)
{
	return adapter::qt::Parameter(deviceStructure_->getParameter(name.toStdString()));
}

adapter::qt::ExtraParameter Configuration::getExtraParameter(const QString &name)
{
	return adapter::qt::ExtraParameter(deviceStructure_->getExtraParameter(name.toStdString()));
}

adapter::qt::Register Configuration::getRegister(const QString &name)
{
	return adapter::qt::Register(deviceStructure_->getRegister(name.toStdString()));
}

adapter::qt::Flag Configuration::getFlag(const QString &name)
{
	return adapter::qt::Flag(deviceStructure_->getFlag(name.toStdString()));
}

const UiPanelConfiguration& Configuration::getConfigurePanelConfiguration()
{
	return *configurePanelConfiguration_;
}

const UiPanelConfiguration& Configuration::getMonitoringPanelConfiguration()
{
	return *monitoringPanelConfiguration_;

}
