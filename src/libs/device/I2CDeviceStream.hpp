#ifndef I2CDEVICE_HPP
#define I2CDEVICE_HPP

#include <device/DeviceStream.hpp>

class I2CDeviceStream : public DeviceStream
{
public:
	I2CDeviceStream(const std::string &bus, uint16_t slaveAddress, std::shared_ptr<sol::state> lua);

protected:
	virtual void open() override;

	uint16_t address_;
};

#endif // I2CDEVICE_HPP
