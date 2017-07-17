#ifndef UICONFIGURATION_HPP
#define UICONFIGURATION_HPP

#include <UiPanelConfiguration.hpp>

#include <sol.hpp>

class UiConfiguration
{
public:
	UiConfiguration(sol::state &lua_, const sol::table &table);

	UiPanelConfiguration getConfigurePanel() const;
	UiPanelConfiguration getMonitoringPanel() const;

private:
	sol::state &lua_;

	ConfigurePanelConfiguration configurePanelConfiguration_;
	MonitoringPanelConfiguration monitoringPanelConfiguration_;
};

#endif // UICONFIGURATION_HPP
