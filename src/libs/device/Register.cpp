#include <Register.hpp>

Register::Register(const sol::table &table)
{
	name_ = table.get<std::string>("name");
	address_ = table.get<uint16_t>("address");

//	writable_ = table["writable"].get_or(false);
//	readable_ = table["readable"].get_or(false);

//	description_ = table["description"].get_or("");
}
