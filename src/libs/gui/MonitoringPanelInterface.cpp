#include <QDockWidget>
#include <QLabel>
#include <QGridLayout>

#include <ToggleButton.hpp>

#include <qt_adapter/FlagAdapter.hpp>
#include <qt_adapter/ParameterAdapter.hpp>

#include <UiPanelConfiguration.hpp>
#include <MonitoringPanelInterface.hpp>

namespace interface
{

void MonitoringPanel::setupInterface(QDockWidget *widget,
									 const UiPanelConfiguration &uiConfig)
{
	clearInterface(widget);
	using adapter::qt::Flag;
	using adapter::qt::Parameter;

	QFrame *mainWidget = new QFrame();
	mainWidget->setFrameStyle(QFrame::Box | QFrame::Sunken);

	QGridLayout *mainLayout = new QGridLayout();

	QLabel *extraParameterValue;
	for (const auto& extraParameterName : uiConfig.getExtraParamterNames()) {
		mainLayout->addWidget(new QLabel(QString("<b>%1</b>").arg(extraParameterName)),
							  extraParameterValues.size() % 5,
							  (static_cast<unsigned>((extraParameterValues.size())) / 5) * 2);
		extraParameterValue = new QLabel("N/A");
		mainLayout->addWidget(extraParameterValue,
							  extraParameterValues.size() % 5,
							  (static_cast<unsigned>((extraParameterValues.size())) / 5) * 2 + 1);
		extraParameterValues.insert(extraParameterName, extraParameterValue);
	}

	QLabel *parameterValue;
	for (const auto& parameterName : uiConfig.getParamterNames()) {
		mainLayout->addWidget(new QLabel(QString("<b>%1</b>").arg(parameterName)),
							  (extraParameterValues.size() + parameterValues.size()) % 5,
							  ((extraParameterValues.size() + parameterValues.size()) / 5) * 2);
		parameterValue = new QLabel("N/A");
		mainLayout->addWidget(parameterValue,
							  (extraParameterValues.size() + parameterValues.size()) % 5,
							  ((extraParameterValues.size() + parameterValues.size()) / 5) * 2 + 1);
		parameterValues.insert(parameterName, parameterValue);
	}


	QLabel *flagValue;
	for (const auto& flagName : uiConfig.getFlagNames()) {
		mainLayout->addWidget(new QLabel(QString("<b>%1</b>").arg(flagName)),
							  (extraParameterValues.size() + parameterValues.size() + flagStatuses.size()) % 5,
							  ((extraParameterValues.size() + parameterValues.size() + flagStatuses.size()) / 5) * 2);
		flagValue = new QLabel("N/A");
		mainLayout->addWidget(flagValue,
							  (extraParameterValues.size() + parameterValues.size() + flagStatuses.size()) % 5,
							  ((extraParameterValues.size() + parameterValues.size() + flagStatuses.size()) / 5) * 2 + 1);
		flagStatuses.insert(flagName, flagValue);
	}

	toggleMonitoringButton = new ToggleButton(QString("Stop monitoring"),
											  QString("Start monitoring"));
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(mainLayout);
	layout->addWidget(toggleMonitoringButton,0,Qt::AlignLeft);
//	mainLayout->addWidget(toggleMonitoringButton, 6,
//						  ((parameterValues.size() + flagStatuses.size()) / 5) * 2 + 1);

	mainWidget->setLayout(layout);

	widget->setWidget(mainWidget);
	widget->setWindowTitle(QObject::tr("Monitoring panel"));
}

void MonitoringPanel::clearInterface(QWidget *widget)
{
	ConfigurableUiInterface::clearInterface(widget);
	parameterValues.clear();
	flagStatuses.clear();
}

}
