#include <DeviceStream.hpp>
#include <iostream>

#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

DeviceStream::DeviceStream(const std::string &bus, std::shared_ptr<sol::state> lua)
	: bus_(bus),
	  lua_(lua)
{
	defineBasicIOFunctionsForLua();
	getIOFunctionsFromLua();
}

/*
 * public methods
 */

void DeviceStream::open()
{
	fileDescriptor_ = ::open(bus_.c_str(), O_RDWR);
	if (fileDescriptor_ == -1) {
		throw IOException(std::string("Unable to open ")
						  + bus_ + " :"
						  + strerror(errno));
	}
}

void DeviceStream::close()
{
	if (::close(fileDescriptor_) == -1) {
		throw IOException(std::string("Unable to close the device: ") + strerror(errno));
	}
}


uint8_t DeviceStream::read(uint16_t address)
{
	auto value = deviceFunctions_["read"](address);
	if (value.valid()) {
		return value;
	} else {
		sol::error error = value;
		throw IOException(error.what());
	}
}

std::vector<uint8_t> DeviceStream::multiread(uint16_t startAddress, uint16_t size)
{
	auto result = deviceFunctions_["multiread"](startAddress, size);
	if (result.valid()) {
		sol::object returnValue = result;
		if (returnValue.is<std::vector<uint8_t>>()) {
			return returnValue.as<std::vector<uint8_t>>();
		} else if (returnValue.is<sol::table>()) {
			std::vector<uint8_t> data;
			returnValue.as<sol::table>().for_each([&](sol::object key, sol::object value ) {
				data.push_back(value.as<uint8_t>());
			});
			return data;
		}
	} else {
		sol::error error = result;
		throw IOException(error.what());
	}
}

void DeviceStream::write(uint16_t address, uint8_t data)
{
	auto result = deviceFunctions_["write"](address, data);
	if (!result.valid()) {
		sol::error error = result;
		throw IOException(error.what());
	}
}

void DeviceStream::multiwrite(uint16_t address, const std::vector<uint8_t> &data)
{
	auto result = deviceFunctions_["multiwrite"](address, data);
	if (!result.valid()) {
		sol::error error = result;
		throw IOException(error.what());
	}
}

/*
 * private methods
 */


uint8_t DeviceStream::basicRead()
{
	uint8_t buffer;
	int res = ::read(fileDescriptor_, &buffer, 1);
	if (res < 0 || res != 1) {
		throw IOException(std::string("Read failure: ") + strerror(errno));
	}
	return buffer;
}

std::vector<uint8_t> DeviceStream::basicRead(uint16_t size)
{
	std::vector<uint8_t> buffer(size);
	int res = ::read(fileDescriptor_, &buffer[0], size);
	if (res < 0 || res != size) {
		throw IOException(std::string("Read failure: ") + strerror(errno));
	}
	return buffer;
}

void DeviceStream::basicWrite(sol::variadic_args args)
{
	std::vector<uint8_t> data;
	for (sol::object arg : args) {
		if (arg.is<uint8_t>()) {
			data.push_back(arg.as<uint8_t>());
		} else if (arg.is<std::vector<uint8_t>>()) {
			for (const auto& n : arg.as<std::vector<uint8_t>>()) {
				data.push_back(n);
			}
		} else if (arg.is<sol::table>()) {
			arg.as<sol::table>().for_each([&](sol::object key, sol::object value) {
				data.push_back(value.as<uint8_t>());
			});
		}
	}
	if (!data.empty()) {
		int res = ::write(fileDescriptor_, &data[0], data.size());
		if (res < 0 || res != data.size()) {
			throw IOException(std::string("Write failure: ") + strerror(errno));
		}
	}
}


void DeviceStream::defineBasicIOFunctionsForLua()
{
	auto basicRead1 = [this]() -> uint8_t {
					  return basicRead();
	};
	auto basicRead2 = [this](uint16_t size) -> std::vector<uint8_t> {
		return basicRead(size);
	};
	lua_->set_function("basic_read", sol::overload(basicRead1, basicRead2));
	lua_->set_function("basic_write", &DeviceStream::basicWrite, this);
}

void DeviceStream::getIOFunctionsFromLua()
{
	lua_->get<sol::table>("device").get<sol::table>("operations")
			.for_each([&](sol::object key, sol::object value ) {
		deviceFunctions_[key.as<std::string>()] = value.as<sol::protected_function>();
	});

	// set default multi read&write if user doesn't define them
	if (deviceFunctions_.find("multiwrite") == deviceFunctions_.end()) {
		auto multiwrite = [this](uint16_t startAddress, const std::vector<std::uint8_t> &data) {
			for (decltype(data.size()) i = 0; i < data.size(); ++i) {
				deviceFunctions_["write"](startAddress + i, data[i]);
			}
		};
		lua_->set_function("multiwrite", multiwrite);
		deviceFunctions_["multiwrite"] =
				lua_->get<sol::protected_function>("multiwrite");
	}

	if (deviceFunctions_.find("multiread") == deviceFunctions_.end()) {
		auto multiread = [this](uint16_t startAddress, size_t size) -> std::vector<uint8_t> {
			std::vector<uint8_t> buffer;
			for (size_t i = 0; i < size; ++i) {
				buffer.push_back(deviceFunctions_["read"](startAddress + i));
			}
			return buffer;
		};
		lua_->set_function("multiread", multiread);
		deviceFunctions_["multiread"] =
				lua_->get<sol::protected_function>("multiread");
	}

}
