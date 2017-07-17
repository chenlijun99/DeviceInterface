#include <ConfigurePanel.hpp>

#include <UiPanelConfiguration.hpp>

ConfigurePanel::ConfigurePanel(QWidget *parent)
	: ConfigurableDeviceDockWidget(parent),
	  ui_(new interface::ConfigurePanel)
{
}

void ConfigurePanel::receiveConfiguration(std::shared_ptr<Configuration> configuration)
{
	ConfigurableDeviceDockWidget::receiveConfiguration(configuration);

	using adapter::qt::Flag;
	using adapter::qt::Parameter;
	ui_->setupInterface(this, configuration->getConfigurePanelConfiguration());

	for (const auto &flagName :
		 configuration->getConfigurePanelConfiguration().getFlagNames()) {
		Flag flag = configuration->getFlag(flagName);
		ui_->flagToggleButtons[flagName]
				->setStatesTexts(flag.getOnStateName(), flag.getOffStateName());
		ui_->previousFlagToggleButtons[flagName]
				->setStatesTexts(flag.getOnStateName(), flag.getOffStateName());
	}

	for (const auto &parameterName :
		 configuration->getConfigurePanelConfiguration().getParamterNames()) {
		Parameter parameter = configuration->getParameter(parameterName);
		ui_->parameterLineEdits[parameterName]
				->setRange(0, parameter.getMaxValue());
	}

	connect(ui_->configureButton, &QPushButton::clicked,
			this, &ConfigurePanel::configure);
}

void ConfigurePanel::configure()
{
	UiPanelConfiguration config =
			configuration_->getConfigurePanelConfiguration();
	device_->setBufferedIO(false);
	device_->setParameterValue("dim", 0);
	device_->setBufferedIO(true);

	for (const QString& parameterName : config.getParamterNames()) {
		if (parameterName == "dim") {
			continue;
		}

		device_->setParameterValue(parameterName.toStdString(),
								   ui_->parameterLineEdits[parameterName]->number());
		ui_->previousParameterLineEdits[parameterName]
				->setText(QString::number(ui_->parameterLineEdits[parameterName]->number()));
	}

	for (const QString& flagName : config.getFlagNames()) {

		device_->setFlagStatus(flagName.toStdString(),
							   ui_->flagToggleButtons[flagName]->isChecked());

		ui_->previousFlagToggleButtons[flagName]
				->setChecked(ui_->flagToggleButtons[flagName]->isChecked());
	}
	device_->flush();

	device_->setBufferedIO(false);
	device_->setParameterValue("dim",
							   ui_->parameterLineEdits["dim"]->number());
	ui_->previousParameterLineEdits["dim"]->setText(
				QString::number(ui_->parameterLineEdits["dim"]->number()));
	device_->setBufferedIO(true);
}
