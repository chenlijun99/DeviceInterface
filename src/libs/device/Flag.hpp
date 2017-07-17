#ifndef FLAG_H
#define FLAG_H

#include <string>
#include <utility>

#include <sol.hpp>

class Flag
{
public:
	Flag() = default;
	Flag(const sol::table &table);

	std::string getName() const
	{ return name_; }
	std::string belongsTo() const
	{ return register_; }
	std::uint8_t getAddress() const
	{ return address_; }
	std::uint8_t getBitLocation() const
	{ return nthBit_; }
	std::string getOnStateName() const
	{ return onName_.empty() ? name_ : onName_; }
	std::string getOffStateName() const
	{ return offName_.empty() ? name_ : offName_; }
	std::pair<std::string,std::string> getStatusNames() const
	{ return std::make_pair(getOnStateName(), getOffStateName()); }

private:
    std::string name_;
    std::string description_;
	std::string register_;
	std::uint16_t address_ = 0;
	uint8_t nthBit_ = 0;
    std::string onName_;
    std::string offName_;
};

#endif // FLAG_H
