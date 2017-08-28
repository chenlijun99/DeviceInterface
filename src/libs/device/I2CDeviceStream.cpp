#include "I2CDeviceStream.hpp"

#include <unistd.h>
#include <cerrno>
#include <cstdio>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

I2CDeviceStream::I2CDeviceStream(const std::string &bus, uint16_t slaveAddress, std::shared_ptr<sol::state> lua)
	: DeviceStream(bus, lua),
	  address_(slaveAddress)
{
}

void I2CDeviceStream::open()
{
    DeviceStream::open();
	ioctl(fileDescriptor_, I2C_SLAVE, address_);
}
