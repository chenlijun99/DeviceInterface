#include "ExtraParameter.hpp"

ExtraParameter::ExtraParameter(const sol::table &table)
{
	name_ = table.get<std::string>("name");
	auto getter = table.get<sol::optional<sol::protected_function>>("get");
	if (getter) {
		getter_ = getter.value();
	}
	auto setter = table.get<sol::optional<sol::protected_function>>("set");
	if (setter) {
		setter_ = setter.value();
	}
}

//uint32_t ExtraParameter::getValue() const
//{
//	auto result = getter_();
//	if (result.valid()) {
//		return result;
//	} else {
//		sol::error error = result;
//		throw ioexception(error.what());
//	}
//}

//void extraparameter::setvalue(uint32_t value)
//{
//	auto result = setter_(value);
//	if (!result.valid()) {
//		sol::error error = result;
//		throw ioexception(error.what());
//	}
//}

sol::protected_function ExtraParameter::getGetter() const
{
	return getter_;
}
sol::protected_function ExtraParameter::getSetter() const
{
	return setter_;
}

bool ExtraParameter::hasGetter() const
{
	return getter_ != sol::nil;
}

bool ExtraParameter::hasSetter() const
{
	return setter_ != sol::nil;
}
