#ifndef DEVICE_INFO_HPP
#define DEVICE_INFO_HPP

#include <libudev.h>

#include <vector>
#include <string>

class DeviceInfo
{
public:
	DeviceInfo() = default;
	DeviceInfo(const std::string &deviceSysfsPath);
	DeviceInfo(const DeviceInfo &other);
	~DeviceInfo();
	static std::vector<DeviceInfo> availableDevices(const std::__cxx11::string &subsystem);

    std::string deviceNode() const;
    std::string formattedDescription() const;
    std::string shortDescription() const;

private:
    void retrieveInformations();

    udev *udevContext_ = nullptr;
    udev_device *device_ = nullptr;

    // device file in /dev
    std::string deviceNode_;
    // device file in sysfs
    std::string deviceSysfsPath_;

    // informations about the i2c device
    std::string name_;
    std::string manufacturer_;
    std::string product_;
    std::string idVendor_;
    std::string idProduct_;
};

#endif //DEVICE_INFO_HPP
