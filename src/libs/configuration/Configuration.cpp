#include <Configuration.hpp>
#include <iostream>

Configuration::Configuration(const std::string &filename)
{
	lua_.script_file(filename);
	lua_.open_libraries(sol::lib::base);
	deviceConfiguration_ = std::unique_ptr<DeviceConfiguration>
						   (new DeviceConfiguration(lua_, lua_.get<sol::table>("device")));
	uiConfiguration_ = std::unique_ptr<UiConfiguration>
					   (new UiConfiguration(lua_, lua_.get<sol::table>("interface")));
	validate();
}

DeviceConfiguration Configuration::getDeviceConfiguration() const
{
	return *deviceConfiguration_;
}

UiConfiguration Configuration::getUiConfiguration() const
{
	return *uiConfiguration_;
}


DeviceConfiguration& Configuration::getDeviceConfigurationRef()
{
	return *deviceConfiguration_;
}

UiConfiguration& Configuration::getUiConfigurationRef()
{
	return *uiConfiguration_;
}

void Configuration::validate()
{

}
