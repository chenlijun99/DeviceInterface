#ifndef UIPANEL_HPP
#define UIPANEL_HPP

#include <QVector>
#include <QString>

#include <sol.hpp>

class UiPanelConfiguration
{
public:
	UiPanelConfiguration(const sol::table &table);

	const QVector<QString>& getExtraParamterNames() const;
    const QVector<QString>& getParameterNames() const;
	const QVector<QString>& getFlagNames() const;

private:
	QVector<QString> flags_;
	QVector<QString> parameters_;
	QVector<QString> extraParameters_;
};

#endif // UIPANEL_HPP
