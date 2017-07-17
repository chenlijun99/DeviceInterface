#ifndef qt_DEVICEINFOADAPTER_HPP
#define qt_DEVICEINFOADAPTER_HPP

#include <device/DeviceInfo.hpp>

#include <QVector>

namespace adapter
{
namespace qt
{
class DeviceInfo
{
public:
	DeviceInfo() = default;
	DeviceInfo(const ::DeviceInfo &adaptee)
		 : deviceInfo_(adaptee)
	{
	}


	static QVector<DeviceInfo>availableDevices(const QString &subsystem)
	{
		QVector<DeviceInfo> adapters;
		for (const auto &deviceInfo :
			 ::DeviceInfo::availableDevices(subsystem.toStdString())) {
			adapters.push_back(DeviceInfo(deviceInfo));
		}
		return adapters;
	}

	QString deviceNode() const
	{
		return QString::fromStdString(deviceInfo_.deviceNode());
	}
	QString formattedDescription() const
	{
		return QString::fromStdString(deviceInfo_.formattedDescription());
	}
	QString shortDescription() const
	{
		return QString::fromStdString(deviceInfo_.shortDescription());
	}

private:
	const ::DeviceInfo deviceInfo_;

};
} // end of namespace qt
} // end of namespace adapter

#endif // DEVICEINFO_HPP
