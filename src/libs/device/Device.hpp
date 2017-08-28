#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <memory>

#include <sol.hpp>

#include <device/DeviceStream.hpp>
#include <device/DeviceValues.hpp>

struct ConfigurationSyntaxError : public std::runtime_error {
	explicit ConfigurationSyntaxError(const char *message)
		: std::runtime_error(message) { }

	explicit ConfigurationSyntaxError(const std::string &message)
		: std::runtime_error(message) { }
};

struct ConfigurationSemanticError : public std::runtime_error {
	explicit ConfigurationSemanticError(const char *message)
		: std::runtime_error(message) { }

	explicit ConfigurationSemanticError(const std::string &message)
		: std::runtime_error(message) { }
};

class Device
{
public:
	Device(const std::string &bus, const std::string &configFile);
	Device(const std::string &bus, uint16_t slaveAddress, const std::string &configFile);
	Device(const std::string &bus, std::shared_ptr<sol::state> lua);
	Device(const std::string &bus, uint16_t slaveAddress,  std::shared_ptr<sol::state> lua);
	~Device();

	void setParameterValue(const std::string &parameterName, uint64_t value);
	void setParameterValue(const Parameter &p, uint64_t value);
	uint32_t getParameterValue(const std::string &parameterName) const;
	uint32_t getParameterValue(const Parameter &p) const;
	uint32_t getParameterMaxValue(const std::string &parameterName) const;
	uint32_t getParameterMaxValue(const Parameter &p) const;

    void setExtraParameterValue(const std::string &name, const std::string &value);
    std::string getExtraParameterValue(const std::string &name) const;

	void setFlagStatus(std::string flagName, bool getValue);
	bool getFlagStatus(std::string flagName) const;

	void setRegisterValue(const std::string &registerName, uint8_t getValue);
	void setRegisterValue(uint16_t address, uint8_t getValue);
	uint8_t getRegisterValue(const std::string &registerName) const;
	uint8_t getRegisterValue(uint16_t address) const;

	void setBufferedIO(bool buffered);
	bool hasBufferedIO() const;

	void update();
	void flush();

    const DeviceStructure& getDeviceStructure() const;

private:
	void defineFunctionsForLua();
	static std::shared_ptr<sol::state> createLuaState(const std::string &configFile);
	void setValue(std::vector<uint16_t> addresses, uint64_t getValue);
	uint32_t getValue(std::vector<uint16_t> addresses) const;
	uint32_t getValue(std::vector<uint16_t> addresses, uint64_t maxValue) const;
	void setValue(std::vector<uint16_t> addresses, uint64_t getValue,
				  uint64_t maxValue);

	bool bufferedIO_;
    std::shared_ptr<sol::state> lua_;
    std::unique_ptr<DeviceStream> stream_;
    std::unique_ptr<DeviceStructure> values_;
    mutable std::vector<uint8_t> buffer_;
};

#endif // DEVICE_HPP
