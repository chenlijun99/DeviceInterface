#ifndef UIINTERFACE_HPP
#define UIINTERFACE_HPP

class QWidget;

class ConfigurableUiInterface
{
public:
	virtual void clearInterface(QWidget *widget);

protected:
};

#endif // UIINTERFACE_HPP
