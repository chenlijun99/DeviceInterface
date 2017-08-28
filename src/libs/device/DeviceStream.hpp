#ifndef DEVICE_H
#define DEVICE_H

#include <inttypes.h>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

#include <sol.hpp>

class DeviceConfiguration;
class Parameter;
class Flag;
class Register;

struct IOException : public std::runtime_error {
	explicit IOException(const char *message)
		: std::runtime_error(message) { }

	explicit IOException(const std::string &message)
		: std::runtime_error(message) { }
};

class DeviceStream
{
public:
	DeviceStream(const std::string &bus, std::shared_ptr<sol::state> lua);

	virtual void open();
	virtual void close();

	uint8_t read(uint16_t address);
	std::vector<uint8_t> multiread(uint16_t startAddress, uint16_t size);
	void write(uint16_t address, uint8_t data);
	void multiwrite(uint16_t address, const std::vector<uint8_t> &data);

protected:
	virtual uint8_t basicRead();
	virtual std::vector<uint8_t> basicRead(uint16_t size);
	virtual void basicWrite(sol::variadic_args args);

	void defineBasicIOFunctionsForLua();
	void getIOFunctionsFromLua();

	int fileDescriptor_;
    std::string bus_;
    std::shared_ptr<sol::state> lua_;
	std::map<std::string, sol::protected_function> deviceFunctions_;
};

#endif // DEVICE_H
