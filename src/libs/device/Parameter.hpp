#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include <vector>
#include <cmath>

#include <sol.hpp>

class Parameter
{
public:
	Parameter() = default;
	Parameter(const sol::table &table);

	std::string getDescription()   const { return description_; }
	std::string getName()          const { return name_; }
	const std::vector<uint16_t> & getAddresses()
                                const { return addresses_; }
	uint64_t getMaxValue()         const { return
                size_ != 0 ? pow(2, size_) - 1 : pow(2, addresses_.size() * 8) - 1; }
    bool hasDescription()       const { return !description_.empty(); }
    bool isWritable()           const { return writable_; }
    bool isReadable()           const { return readable_; }

//    friend void to_json(nlohmann::json &j, const Parameter &p);
//    friend void from_json(const nlohmann::json &j, Parameter &p);

private:
    std::string name_;
    std::string description_;
    std::vector<uint16_t> addresses_;
	uint8_t size_ = 0;
	bool writable_ = false;
	bool readable_ = false;
};

#endif // PARAMETER_H
