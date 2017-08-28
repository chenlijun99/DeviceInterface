#include <ConfigurePanel.hpp>

#include <UiPanelConfiguration.hpp>

ConfigurePanel::ConfigurePanel(QWidget *parent)
	: ConfigurableDeviceDockWidget(parent),
	  ui_(new interface::ConfigurePanel)
{
}

ConfigurePanel::~ConfigurePanel()
{
    delete ui_;
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
         configuration->getConfigurePanelConfiguration().getParameterNames()) {
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
    device_->setTransformedParameterValue("dim", "0");
	device_->setBufferedIO(true);

    for (const QString& parameterName : config.getParameterNames()) {
		if (parameterName == "dim") {
			continue;
		}

        device_->setTransformedParameterValue(parameterName.toStdString(),
                                   std::to_string(ui_->parameterLineEdits[parameterName]->number()));
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
    device_->setTransformedParameterValue("dim",
                               std::to_string(ui_->parameterLineEdits["dim"]->number()));
	ui_->previousParameterLineEdits["dim"]->setText(
				QString::number(ui_->parameterLineEdits["dim"]->number()));
	device_->setBufferedIO(true);
}
