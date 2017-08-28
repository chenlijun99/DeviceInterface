#include <Device.hpp>

#include <I2CDeviceStream.hpp>

namespace {
bool isBigEndian()
{
	union {
		uint32_t value;
		uint8_t bytes[4];
	} n = {0x01020304};

	return n.bytes[0] == 1;
}
}


Device::Device(const std::string &bus, const std::string &configFile)
	: Device(bus, createLuaState(configFile))
{
}

Device::Device(const std::string &bus, uint16_t slaveAddress, const std::string &configFile)
	: Device(bus, slaveAddress, createLuaState(configFile))
{
}

Device::Device(const std::string &bus, std::shared_ptr<sol::state> lua)
	: lua_(lua),
	  stream_(std::make_unique<DeviceStream>(bus, lua_)),
      values_(std::make_unique<DeviceStructure>(lua_->get<sol::table>("device"))),
	  buffer_(values_->maxAddress())
{
	defineFunctionsForLua();
	stream_->open();
}

Device::Device(const std::string &bus, uint16_t slaveAddress,  std::shared_ptr<sol::state> lua)
	: lua_(lua),
	  stream_(std::make_unique<I2CDeviceStream>(bus, slaveAddress, lua_)),
      values_(std::make_unique<DeviceStructure>(lua_->get<sol::table>("device"))),
	  buffer_(values_->maxAddress())
{
	defineFunctionsForLua();
	stream_->open();
}

Device::~Device()
{
	stream_->close();
}

void Device::setRegisterValue(const std::string &registerName, uint8_t value)
{
	setRegisterValue(values_->getRegister(registerName).getAddress(), value);
}
void Device::setRegisterValue(uint16_t address, uint8_t value)
{
	setValue({address}, value);
}
uint8_t Device::getRegisterValue(const std::string &registerName) const
{
	return getRegisterValue(values_->getRegister(registerName).getAddress());
}
uint8_t Device::getRegisterValue(uint16_t address) const
{
	return getValue({address});
}

void Device::setTransformedParameterValue(const std::string &parameterName, const std::string &value)
{
    Parameter p = values_->getParameter(parameterName);

    if (p.getTransformOnSetFunction() != sol::nil) {
        setParameterValue(p, p.getTransformOnSetFunction()(value));
        return;
    }
    setParameterValue(p, std::stoul(value));
}
void Device::setParameterValue(const std::string &parameterName, uint64_t value)
{
	Parameter p = values_->getParameter(parameterName);
	setParameterValue(p, value);
}
void Device::setParameterValue(const Parameter &p, uint64_t value)
{
	setValue(p.getAddresses(), value, getParameterMaxValue(p));
}

std::string Device::getTransformedParameterValue(const std::string &parameterName)
{
    Parameter p = values_->getParameter(parameterName);
    auto value = getParameterValue(p);

    if (p.getTransformOnGetFunction() != sol::nil) {
        return p.getTransformOnGetFunction()(value).get<std::string>();
    }
    return std::to_string(value);
}

uint32_t Device::getParameterValue(const std::string &parameterName) const
{
	Parameter p = values_->getParameter(parameterName);
	return getParameterValue(p);
}
uint32_t Device::getParameterValue(const Parameter &p) const
{
	return getValue(p.getAddresses(), getParameterMaxValue(p));
}
uint32_t Device::getParameterMaxValue(const std::string &parameterName) const
{
	Parameter p = values_->getParameter(parameterName);
	return getParameterMaxValue(p);
}
uint32_t Device::getParameterMaxValue(const Parameter &p) const
{
	return p.getMaxValue();
}

void Device::setExtraParameterValue(const std::string &name, const std::string &value)
{
	values_->getExtraParameter(name).getSetter()(value);
}

std::string Device::getExtraParameterValue(const std::string &name) const
{
	return values_->getExtraParameter(name).getGetter()();
}

void Device::setFlagStatus(std::string flagName, bool value)
{
	Flag f = values_->getFlag(flagName);
	uint64_t status = getRegisterValue(f.getAddress());
	if (value) {
		status |= (1 << (f.getBitLocation() - 1));
	} else {
		status &= (0 << (f.getBitLocation() - 1));
	}
	setRegisterValue(f.getAddress(), status);
}
bool Device::getFlagStatus(std::string flagName) const
{
	Flag f = values_->getFlag(flagName);
	uint64_t status = getRegisterValue(f.getAddress());
	uint64_t mask = (1 << (f.getBitLocation() - 1));
	return status & mask;
}

void Device::setValue(std::vector<uint16_t> addresses, uint64_t value)
{
	setValue(addresses, value, pow(2, addresses.size() * 8) - 1);
}
void Device::setValue(std::vector<uint16_t> addresses, uint64_t value,
					  uint64_t maxValue)
{
	// set to 0 the bits that shouldn't be considered
	value &= maxValue;

	union ValueBytes
	{
		unsigned long value;
		uint8_t bytes[sizeof(uint64_t)];
	};
	ValueBytes valueBytes;
	valueBytes.value = value;

	// write the value in the buffer
	if (isBigEndian()) {
		for (size_t i = 0; i < addresses.size(); ++i) {
			buffer_[addresses[i]] = valueBytes.bytes[i];
		}
	} else {
		for (size_t i = 0, j = addresses.size() - 1; i < addresses.size(); ++i, --j) {
			buffer_[addresses[j]] = valueBytes.bytes[i];
		}
	}

	if (!hasBufferedIO()) {
		stream_->multiwrite(addresses[0],
				std::vector<uint8_t> {buffer_.cbegin() + addresses[0],
					buffer_.cbegin() + 1 + addresses[addresses.size() - 1]});
	}
}
uint32_t Device::getValue(std::vector<uint16_t> addresses) const
{
	return getValue(addresses, pow(2, addresses.size() * 8) - 1);
}
uint32_t Device::getValue(std::vector<uint16_t> addresses, uint64_t maxValue) const
{
	// concatenate bytes from buffer_ in a unique value
	uint64_t value = 0;

	if (!hasBufferedIO()) {
		std::vector<uint8_t> buffer = stream_->multiread(addresses[0], addresses.size());

		{
			int i = 0;
			for (const auto& address : addresses) {
				buffer_[address] = buffer[i++];
			}
		}
	}

	{
		int shift = addresses.size() - 1;
		for (const auto& address : addresses) {
			value |= buffer_[address];
			value <<= shift-- * 8;
		}
	}

	// set to 0 the bits that shouldn't be considered
	value &= maxValue;
	return value;
}

void Device::update()
{
	buffer_ = stream_->multiread(0, buffer_.size());
}

void Device::flush()
{
	std::vector<uint8_t> buffer(buffer_.begin(), buffer_.begin() + 29);
	stream_->multiwrite(0, buffer);
}

const DeviceStructure& Device::getDeviceStructure() const
{
	return *values_;
}

std::shared_ptr<sol::state> Device::createLuaState(const std::string &configFile)
{
	std::shared_ptr<sol::state> lua = std::make_shared<sol::state>();
	auto result = lua->do_file(configFile);
	if (!result.valid()) {
		sol::error error = result;
		throw ConfigurationSyntaxError(error.what());
	}
	return lua;
}

void Device::defineFunctionsForLua()
{
	auto errorHandler = [](std::string errorMessage) ->std::string {
		return std::string("Error in lua: ") + errorMessage;
	};
	lua_->set_function("error_handler", errorHandler);
	sol::protected_function::set_default_handler((*lua_)["error_handler"]);

    lua_->set_function("getParameterMaxValue",
                      static_cast<uint32_t (Device::*)(const std::string&) const>(&Device::getParameterMaxValue),
                      this);
    lua_->set_function("getParameterValue",
					  static_cast<uint32_t (Device::*)(const std::string&) const>(&Device::getParameterValue),
					  this);
	lua_->set_function("setParameterValue",
					  static_cast<void (Device::*)(const std::string&, uint64_t getValue)>(&Device::setParameterValue),
					  this);
	lua_->set_function("getFlagStatus", &Device::getFlagStatus, this);
	lua_->set_function("setFlagStatus", &Device::setFlagStatus, this);
	lua_->set_function("getRegisterValue",
					  static_cast<uint8_t (Device::*)(const std::string&) const>(&Device::getRegisterValue),
					  this);
	lua_->set_function("setRegisterValue",
					  static_cast<void (Device::*)(const std::string&, uint8_t)>(&Device::setRegisterValue),
					  this);
}

void Device::setBufferedIO(bool buffered)
{
	bufferedIO_ = buffered;

}

bool Device::hasBufferedIO() const
{
	return bufferedIO_;

}
