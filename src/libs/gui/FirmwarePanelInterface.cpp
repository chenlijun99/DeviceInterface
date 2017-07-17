#include <FirmwarePanelInterface.hpp>
#include <ToggleButton.hpp>

#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>

namespace interface
{
void FirmwarePanel::setupInterface(QDockWidget *widget)
{
	QFrame *mainWidget = new QFrame();
	mainWidget->setFrameStyle(QFrame::Box | QFrame::Sunken);

	QGridLayout *mainLayout = new QGridLayout();

	// create and arrange descriptive labels
	QLabel *label;

	label = new QLabel(QString("Power"));
	deviceToggleButton = new ToggleButton("On", "Off", Qt::green, Qt::red);
	mainLayout->addWidget(label, 0, 0);
	mainLayout->addWidget(deviceToggleButton, 0, 1);

	label = new QLabel(QString("DIM"));
	mainLayout->addWidget(label, 1, 0);
	dimSlider = new QSlider;
	dimSlider->setOrientation(Qt::Horizontal);
	dimSlider->setRange(0, 1023);
	mainLayout->addWidget(dimSlider, 1, 1);
	mainWidget->setLayout(mainLayout);

	widget->setWidget(mainWidget);
	widget->setWindowTitle(QObject::tr("Control Panel"));
}
} // end of namespace interface
