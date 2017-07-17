#ifndef qt_FLAGADAPTER_HPP
#define qt_FLAGADAPTER_HPP

#include <device//Flag.hpp>

#include <QString>
#include <QPair>

namespace adapter
{
namespace qt
{
class Flag
{
public:
	Flag(const ::Flag &adaptee)
		: flag_(adaptee)
	{ }

	QString getName() const
	{ return QString::fromStdString(flag_.getName()); }

	QPair<QString, QString> getStatusNames() const
	{
		std::pair<std::string, std::string> statusNames = flag_.getStatusNames();
		return QPair<QString, QString>(
					QString::fromStdString(statusNames.first),
					QString::fromStdString(statusNames.second));
	}
	QString getOnStateName() const
	{ return QString::fromStdString(flag_.getOnStateName()); }
	QString getOffStateName() const
	{ return QString::fromStdString(flag_.getOffStateName()); }
	QString belongsTo() const
	{ return QString::fromStdString(flag_.belongsTo()); }
	uint8_t getBitLocation() const
	{ return flag_.getBitLocation(); }

private:
	const ::Flag &flag_;

};
}
}

#endif // FLAG_HPP
