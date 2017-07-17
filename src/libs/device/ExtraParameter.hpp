#ifndef EXTRAPARAMETER_HPP
#define EXTRAPARAMETER_HPP

#include <sol.hpp>

#include <device/DeviceStream.hpp>

class ExtraParameter
{
public:
	ExtraParameter() = default;
	ExtraParameter(const sol::table &table);

	const std::string& getName() const;
	sol::protected_function getGetter() const;
	sol::protected_function getSetter() const;

	bool hasGetter() const;
	bool hasSetter() const;

private:
	std::string name_;
	sol::protected_function getter_;
	sol::protected_function setter_;
};

#endif // EXTRAPARAMETER_HPP
