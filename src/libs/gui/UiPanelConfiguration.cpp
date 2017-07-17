#include <UiPanelConfiguration.hpp>

#include <iostream>

UiPanelConfiguration::UiPanelConfiguration(const sol::table &table)
{
	auto parameters = table.get<sol::optional<sol::table>>("parameters");
	auto extraParameters = table.get<sol::optional<sol::table>>("extra_parameters");
	auto flags = table.get<sol::optional<sol::table>>("flags");

	if (parameters) {
		parameters.value().for_each([&](sol::object key, sol::object value ) {
			parameters_.push_back(QString::fromStdString(value.as<std::string>()));
		});
	}
	if (extraParameters) {
		extraParameters.value().for_each([&](sol::object key, sol::object value ) {
			extraParameters_.push_back(QString::fromStdString(value.as<std::string>()));
		});
	}
	if (flags) {
		flags.value().for_each([&](sol::object key, sol::object value ) {
			flags_.push_back(QString::fromStdString(value.as<std::string>()));
		});
	}
}

const QVector<QString>& UiPanelConfiguration::getParamterNames() const
{
	return parameters_;
}

const QVector<QString>& UiPanelConfiguration::getFlagNames() const
{
	return flags_;
}

const QVector<QString>& UiPanelConfiguration::getExtraParamterNames() const
{
	return extraParameters_;
}
