#include <UiConfiguration.hpp>

UiConfiguration::UiConfiguration(sol::state &lua, const sol::table &table)
	: lua_(lua),
	  configurePanelConfiguration_(lua_, table.get<sol::table>("configure_panel")),
	  monitoringPanelConfiguration_(lua_, table.get<sol::table>("monitoring_panel"))
{
}

UiPanelConfiguration UiConfiguration::getConfigurePanel() const
{
	return configurePanelConfiguration_;
}

UiPanelConfiguration UiConfiguration::getMonitoringPanel() const
{
	return monitoringPanelConfiguration_;
}
