#ifndef qt_EXTRAPARAMETERADAPTER_HPP
#define qt_EXTRAPARAMETERADAPTER_HPP

#include <QString>

#include <device/ExtraParameter.hpp>

namespace adapter
{
namespace qt {

class ExtraParameter
{
public:
	ExtraParameter(const ::ExtraParameter &adaptee)
		: extraParameter_(adaptee)
	{
	}

	sol::protected_function getSetter() const
	{
		return extraParameter_.getSetter();

	}
	sol::protected_function getGetter() const
	{
		return extraParameter_.getGetter();
	}

	QString getName() const
	{
		return QString::fromStdString(extraParameter_.getName());
	}

private:
	const ::ExtraParameter &extraParameter_;

};

} // end of namespace qt
} // end of namespace adapter

#endif // qt_EXTRAPARAMETERADAPTER_HPP
