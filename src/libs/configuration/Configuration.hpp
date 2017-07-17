#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>

#include <sol.hpp>

struct ConfigFileSemanticError : public std::runtime_error {

};

class Configuration
{
public:
	Configuration(const std::string &filename);

	DeviceConfiguration getDeviceConfiguration() const;
	UiConfiguration getUiConfiguration() const;

	DeviceConfiguration& getDeviceConfigurationRef();
	UiConfiguration& getUiConfigurationRef();

private:
	void validate();

	std::unique_ptr<DeviceConfiguration> deviceConfiguration_;
	std::unique_ptr<UiConfiguration> uiConfiguration_;
	sol::state lua_;
};

#endif // CONFIGURATION_HPP
