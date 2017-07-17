#ifndef qt_PARAMTERADAPTER_HPP
#define qt_PARAMTERADAPTER_HPP

#include <device/Parameter.hpp>

#include <QString>
#include <QVector>

namespace adapter
{
namespace qt {
class Parameter
{
public:
	Parameter(const ::Parameter &adaptee)
		: parameter_(adaptee)
	{
	}

	QString getName() const
	{
		return QString::fromStdString(parameter_.getName());
	}

	QString getDescription() const
	{
		return QString::fromStdString(parameter_.getDescription());
	}

	QVector<uint16_t> getAddresses() const
	{
		return QVector<uint16_t>::fromStdVector(parameter_.getAddresses());
	}

	bool hasDescription() const
	{
		return parameter_.hasDescription();
	}
	uint64_t getMaxValue() const
	{
		return parameter_.getMaxValue();

	}
	bool isWritable() const
	{
		return parameter_.isWritable();
	}
	bool isReadable() const
	{
		return parameter_.isReadable();
	}
private:
	const ::Parameter &parameter_;
};

}
}


#endif // PARAMTERADAPTER_HPP
