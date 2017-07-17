#ifndef FIRMWAREPANELINTERFACE_HPP
#define FIRMWAREPANELINTERFACE_HPP

#include <ConfigurableUiInterface.hpp>

class QDockWidget;
class ToggleButton;
class QSlider;

namespace interface
{
class FirmwarePanel
{
public:
	ToggleButton *deviceToggleButton;
	QSlider *dimSlider;
	void setupInterface(QDockWidget *widget);
};
}

#endif // FIRMWAREPANELINTERFACE_HPP
