#include "DeviceValues.hpp"

DeviceValues::DeviceValues(const sol::table &table)
{
	auto registers = table.get<sol::optional<sol::table>>("registers");
	auto parameters = table.get<sol::optional<sol::table>>("parameters");
	auto extraParameters = table.get<sol::optional<sol::table>>("extra_parameters");
	auto flags = table.get<sol::optional<sol::table>>("flags");
	if (registers) {
		registers.value().for_each([&](sol::object key, sol::object value ) {
			registers_[value.as<sol::table>()["name"]] = Register(value.as<sol::table>());
		});
	}
	if (parameters) {
		parameters.value().for_each([&](sol::object key, sol::object value ) {
			parameters_[value.as<sol::table>()["name"]] = Parameter(value.as<sol::table>());
		});
	}
	if (extraParameters) {
		extraParameters.value().for_each([&](sol::object key, sol::object value ) {
			extraParameters_[value.as<sol::table>()["name"]] = ExtraParameter(value.as<sol::table>());
		});
	};
	if (flags) {
		flags.value().for_each([&](sol::object key, sol::object value ) {
			flags_[value.as<sol::table>()["name"]] = Flag(value.as<sol::table>());
		});
	}
}


const Register& DeviceValues::getRegister(const std::string &name) const
{
	return registers_.at(name);
}

const Parameter& DeviceValues::getParameter(const std::string &name) const
{
	return parameters_.at(name);
}

const Flag& DeviceValues::getFlag(const std::string &name) const
{
	return flags_.at(name);
}

const ExtraParameter& DeviceValues::getExtraParameter(const std::string &name) const
{
	return extraParameters_.at(name);
}

size_t DeviceValues::maxAddress() const
{
	// get the Parameter in the map which has the highest address
	std::map<std::string, Parameter>::const_iterator maxElement =
			std::max_element(parameters_.begin(), parameters_.end(),
							 [](const std::pair<std::string,Parameter> &lhs,
							 const std::pair<std::string,Parameter> &rhs)
	{
		return (*std::max_element(lhs.second.getAddresses().begin(), lhs.second.getAddresses().end()))
				< (*std::max_element(rhs.second.getAddresses().begin(), rhs.second.getAddresses().end()));
	});

	// from the obtained Parameter get the highest address between those stored in it
	return static_cast<size_t>(*std::max_element(maxElement->second.getAddresses().begin(),
												 maxElement->second.getAddresses().end()));
}
