#ifndef CONFIGUREPANELINTERFACE_HPP
#define CONFIGUREPANELINTERFACE_HPP

#include <ConfigurableUiInterface.hpp>

#include <ToggleButton.hpp>
#include <IntLineEdit.hpp>

#include <QMap>

class UiPanelConfiguration;
class DeviceConfiguration;

class QDockWidget;

namespace interface
{
class ConfigurePanel : public ConfigurableUiInterface
{
public:
	QMap<QString, ToggleButton*> flagToggleButtons;
	QMap<QString, IntLineEdit*> parameterLineEdits;
	QPushButton *configureButton;

	QMap<QString, ToggleButton*> previousFlagToggleButtons;
	QMap<QString, IntLineEdit*> previousParameterLineEdits;

	virtual void clearInterface(QWidget *widget) override;
	void setupInterface(QDockWidget *widget,
						const UiPanelConfiguration &uiConfig);
};
}

#endif // CONFIGUREPANELINTERFACE_H
