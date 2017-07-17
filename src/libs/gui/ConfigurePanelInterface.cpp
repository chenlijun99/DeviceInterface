#include <QGroupBox>
#include <QDockWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTabWidget>

#include <qt_adapter/FlagAdapter.hpp>
#include <qt_adapter/ParameterAdapter.hpp>

#include <UiPanelConfiguration.hpp>
#include <ConfigurePanelInterface.hpp>

namespace interface
{
void ConfigurePanel::setupInterface(QDockWidget *widget,
									const UiPanelConfiguration &uiConfig)
{
	using adapter::qt::Flag;
	using adapter::qt::Parameter;

	clearInterface(widget);

	QGridLayout *configureGroupBoxLayout = new QGridLayout;
	QGridLayout *lastConfigurationGroupBoxLayout = new QGridLayout;

	ToggleButton *flagButton;
	ToggleButton *previousFlagButton;
	for (const auto& flagName : uiConfig.getFlagNames()) {
		flagButton = new ToggleButton;
		previousFlagButton = new ToggleButton();
		flagButton->setStatesColors(Qt::yellow, Qt::gray);
		previousFlagButton->setStatesColors(Qt::yellow, Qt::gray);
		configureGroupBoxLayout->addWidget(flagButton,
										   flagToggleButtons.size() / 3,
										   flagToggleButtons.size() % 3);
		lastConfigurationGroupBoxLayout->addWidget(previousFlagButton,
										   flagToggleButtons.size() / 3,
										   flagToggleButtons.size() % 3);

		flagToggleButtons.insert(flagName, flagButton);
		previousFlagToggleButtons.insert(flagName, previousFlagButton);
	}

	IntLineEdit *parameterLineEdit;
	IntLineEdit *previousParameterLineEdit;
	for (const auto& parameterName : uiConfig.getParamterNames()) {
		parameterLineEdit = new IntLineEdit;
		previousParameterLineEdit = new IntLineEdit;

		int row = parameterLineEdits.size() + flagToggleButtons.size() + 1;

		configureGroupBoxLayout->addWidget(new QLabel(parameterName), row, 0);
		configureGroupBoxLayout->addWidget(parameterLineEdit,
										   row,
										   1,1,2);
		lastConfigurationGroupBoxLayout->addWidget(new QLabel(parameterName), row, 0);
		lastConfigurationGroupBoxLayout->addWidget(previousParameterLineEdit,
										   row,
										   1,1,2);

		parameterLineEdits.insert(parameterName, parameterLineEdit);
		previousParameterLineEdits.insert(parameterName, previousParameterLineEdit);
	}

	configureButton = new QPushButton(QObject::tr("Configure"));
	configureGroupBoxLayout->addWidget(configureButton,
									   parameterLineEdits.size() + flagToggleButtons.size() + 1,
									   2,1,1);
	// just for alignment issues
	QPushButton *uselessButton = new QPushButton(QObject::tr("Configure"));
	QSizePolicy retainSpaceWhenHidden = uselessButton->sizePolicy();
	retainSpaceWhenHidden.setRetainSizeWhenHidden(true);
	uselessButton->setSizePolicy(retainSpaceWhenHidden);
	uselessButton->hide();
	lastConfigurationGroupBoxLayout->addWidget(uselessButton,
									   parameterLineEdits.size() + flagToggleButtons.size() + 1,
									   2,1,1);

	QWidget *configureWidget = new QWidget;
	QWidget *lastConfigurationWidget = new QWidget;
	configureWidget->setLayout(configureGroupBoxLayout);
	lastConfigurationWidget->setLayout(lastConfigurationGroupBoxLayout);

	QTabWidget *tabWidget = new QTabWidget(widget);
	tabWidget->addTab(configureWidget, "Configure");
	tabWidget->addTab(lastConfigurationWidget, "Previous");
	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addWidget(tabWidget);
	QFrame *mainWidget = new QFrame(widget);
	mainWidget->setFrameStyle(QFrame::Box | QFrame::Sunken);
	mainWidget->setLayout(mainLayout);
	widget->setWidget(mainWidget);
	widget->setWindowTitle(QObject::tr("Configure Panel"));
}


void ConfigurePanel::clearInterface(QWidget *widget)
{
	for (auto child : widget->findChildren<QTabWidget*>(QString(), Qt::FindChildrenRecursively)) {
		delete child;
	}
	flagToggleButtons.clear();
	parameterLineEdits.clear();
	previousFlagToggleButtons.clear();
	previousParameterLineEdits.clear();
}

} // end of namespace interface
