#ifndef DEVICESTRUCTURE_HPP
#define DEVICESTRUCTURE_HPP

#include <map>
#include <string>

#include <sol.hpp>

#include <device/Register.hpp>
#include <device/Parameter.hpp>
#include <device/Flag.hpp>
#include <device/ExtraParameter.hpp>

class DeviceStructure
{
public:
    DeviceStructure(const sol::table &table);

	const Register& getRegister(const std::string &name) const;
	const Parameter& getParameter(const std::string &name) const;
	const Flag& getFlag(const std::string &name) const;
	const ExtraParameter& getExtraParameter(const std::string &name) const;

	size_t maxAddress() const;
	std::vector<uint16_t> writableAddresses() const;
	std::vector<uint16_t> readableAddresses() const;

private:
	std::map<std::string, ExtraParameter> extraParameters_;
	std::map<std::string, Parameter> parameters_;
	std::map<std::string, Flag> flags_;
	std::map<std::string, Register> registers_;
};

#endif // DEVICESTRUCTURE_HPP
