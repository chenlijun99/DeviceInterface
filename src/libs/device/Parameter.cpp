#include <Parameter.hpp>

Parameter::Parameter(const sol::table &table)
{
	name_ = table.get<std::string>("name");

	table.get<sol::table>("addresses").for_each([&](sol::object key, sol::object value ) {
		addresses_.push_back(value.as<uint8_t>());
	});

	writable_ = table.get<bool>("writable");
	readable_ = table.get<bool>("readable");

	description_ = table.get_or<std::string>("description", "");
	size_ = table.get_or<uint8_t>("size", 0);

    auto transformOnSet = table.get<sol::optional<sol::protected_function>>("transformOnSet");
    if (transformOnSet) {
       transformOnSet_ = transformOnSet.value();
    }
    auto transformOnGet = table.get<sol::optional<sol::protected_function>>("transformOnGet");
    if (transformOnGet) {
       transformOnGet_ = transformOnGet.value();
    }
}
