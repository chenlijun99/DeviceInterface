#ifndef REGISTER_H
#define REGISTER_H

#include <string>

#include <sol.hpp>

class Register
{
public:
	Register() = default;
	Register(const sol::table &table);

	std::string getName()          const   { return name_; }
	uint16_t getAddress()          const   { return address_; }
	std::string getDescription()   const   { return description_; }
	bool isWritable()           const   { return writable_; }
	bool isReadable()           const   { return readable_; }

//	friend void to_json(nlohmann::json &j, const Register &p);
//	friend void from_json(const nlohmann::json &j, Register &p);

private:
	std::string name_;
	uint16_t address_  = 0;
	std::string description_;

	bool writable_ = false;
	bool readable_ = false;
};

#endif // REGISTER_H
