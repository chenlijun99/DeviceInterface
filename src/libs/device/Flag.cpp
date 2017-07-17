#include <Flag.hpp>

Flag::Flag(const sol::table &table)
{
	name_ = table.get<std::string>("name");
	register_ = table.get<std::string>("register");
	nthBit_ = table.get<uint8_t>("nthbit");

	description_ = table.get_or<std::string>("description", "");

	onName_ = table.get_or<std::string>("on", "");
	offName_ = table.get_or<std::string>("off", "");
}
