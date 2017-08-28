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
    uint32_t getMaxValue()         const { return
                size_ != 0 ? pow(2, size_) - 1 : pow(2, addresses_.size() * 8) - 1; }
    bool hasDescription()       const { return !description_.empty(); }
    bool isWritable()           const { return writable_; }
    bool isReadable()           const { return readable_; }

    sol::protected_function getTransformOnSetFunction() const { return transformOnSet_; }
    sol::protected_function getTransformOnGetFunction() const { return transformOnGet_; }
private:
    std::string name_;
    std::string description_;
    std::vector<uint16_t> addresses_;
	uint8_t size_ = 0;
	bool writable_ = false;
	bool readable_ = false;
    sol::protected_function transformOnSet_;
    sol::protected_function transformOnGet_;
};

#endif // PARAMETER_H
