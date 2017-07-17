#include "ConfigurableUiInterface.hpp"

#include <QWidget>

void ConfigurableUiInterface::clearInterface(QWidget *widget)
{
	for (auto child :
		 widget->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
		delete child;
	}
}
