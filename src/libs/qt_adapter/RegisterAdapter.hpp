#ifndef qt_REGISTERADAPTER_HPP
#define qt_REGISTERADAPTER_HPP

#include <QString>

#include <device/Register.hpp>

namespace adapter {
namespace qt {

class Register
{
public:
	Register(const ::Register &adaptee)
		: register_(adaptee)
	{
	}

	uint16_t address() const
	{
		return register_.getAddress();
	}
	bool isWritable() const
	{
		return register_.isWritable();
	}
	bool isReadable() const
	{
		return register_.isReadable();
	}
	QString name() const
	{
		return QString::fromStdString(register_.getName());
	}
	QString description() const
	{
		return QString::fromStdString(register_.getDescription());
	}

private:
	const ::Register &register_;
};

}

}

#endif // REGISTER_HPP
