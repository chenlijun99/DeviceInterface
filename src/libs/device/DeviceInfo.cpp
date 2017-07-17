#include <DeviceInfo.hpp>

#include <iostream>

DeviceInfo::DeviceInfo(const std::string &deviceSysfsPath)
{
	udevContext_ = udev_new();

	// create the udev device
	deviceSysfsPath_ = deviceSysfsPath;
	device_ = udev_device_new_from_syspath(udevContext_,
										   deviceSysfsPath_.c_str());
	retrieveInformations();
}

DeviceInfo::DeviceInfo(const DeviceInfo &other)
{
	udevContext_ = udev_ref(other.udevContext_);
	device_ = udev_device_ref(other.device_);

	deviceSysfsPath_ = other.deviceSysfsPath_;
	deviceNode_ = other.deviceNode_;
	name_ = other.name_;
	idVendor_ = other.idVendor_;
	idProduct_ = other.idProduct_;
	manufacturer_ = other.manufacturer_;
	product_ = other.product_;
}

DeviceInfo::~DeviceInfo()
{
	udev_device_unref(device_);
	udev_unref(udevContext_);
}

std::vector<DeviceInfo> DeviceInfo::availableDevices(const std::string &subsystem)
{
	std::vector<DeviceInfo> devices;

	// Create the udev context by reading the udev conf files
	udev *udevContext;
	udevContext = udev_new();
	if (!udevContext) {
		std::cerr << "Can't create udev context\n";
		return devices;
	}

	// Create a list of the devices present in the sysfs
	udev_enumerate *enumerate;
	enumerate = udev_enumerate_new(udevContext);

	// add i2c-dev as filter
	udev_enumerate_add_match_subsystem(enumerate, subsystem.c_str());

	// look for i2c devices
	udev_enumerate_scan_devices(enumerate);


	// get the first entry to the list of devices.
	udev_list_entry *deviceListFirstEntry;
	deviceListFirstEntry = udev_enumerate_get_list_entry(enumerate);

	//For each entry starting from 'deviceListFirstEntry'
	udev_list_entry *deviceEntry;
	udev_list_entry_foreach(deviceEntry, deviceListFirstEntry) {

		/*
		 * Get the filename of the /sys entry for the device
		 * and create a udev_device object (dev) representing it
		 */
		const char *path;
		path = udev_list_entry_get_name(deviceEntry);
		devices.push_back(DeviceInfo(path));
	}

	udev_enumerate_unref(enumerate);
	udev_unref(udevContext);

	return devices;
}

std::string DeviceInfo::deviceNode() const
{
	return deviceNode_;
}

std::string DeviceInfo::formattedDescription() const
{
	return ("Device node: " + deviceNode_ + "\n"
			"Manufacturer: " + manufacturer_ + "\n"
			"Product: " + product_ + "\n"
			"Vendor id: " + idVendor_ + "\n"
			"Product id: " + idProduct_ + "\n");
}

std::string DeviceInfo::shortDescription() const
{
	return name_.empty() ? deviceNode_ : name_;
}

void DeviceInfo::retrieveInformations()
{
	const char* value = nullptr;

	// 'device_' points now to a device in sysfs

	// get the path of the device node in /dev
	// e.g. /dev/i2c-1
	value = udev_device_get_devnode(device_);
	deviceNode_ = value ? value : "";

	// get the name of the device
	value = udev_device_get_sysattr_value(device_, "name");
	name_ = value ? value : "";

	/*
	 * some other information are not stored at the device level
	 * e.g. if we have an usb-i2c device, then the manufacturer, product,
	 * vendorId, productId are likely to be stored at the usb level
	 * Thus we need to reach to the parent (usb) level
	 */

	device_ = udev_device_get_parent_with_subsystem_devtype(device_,"usb", "usb_device");

	// so if there is an usb parent now 'device_' points to it
	if (device_) {
		// fetch all the meaningfulinformation about the device
		value = udev_device_get_sysattr_value(device_, "idVendor");
		idVendor_ = value ? value : "";
		value = udev_device_get_sysattr_value(device_, "idProduct");
		idProduct_ = value ? value : "";
		value = udev_device_get_sysattr_value(device_, "product");
		manufacturer_ = value ? value : "";
		value = udev_device_get_sysattr_value(device_, "product");
		product_ = value ? value : "";
	}
}
