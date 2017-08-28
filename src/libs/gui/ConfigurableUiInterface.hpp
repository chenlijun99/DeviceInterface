#ifndef CONFIGURABLEUIINTERFACE_HPP
#define CONFIGURABLEUIINTERFACE_HPP

class QWidget;

class ConfigurableUiInterface
{
public:
    virtual ~ConfigurableUiInterface() { }
	virtual void clearInterface(QWidget *widget);
};

#endif // UIINTERFACE_HPP
