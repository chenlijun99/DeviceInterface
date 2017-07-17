#include <QPalette>
#include <QPainter>
#include <QString>

#include "ToggleButton.hpp"

ToggleButton::ToggleButton(QWidget *parent)
	: QPushButton(parent)
{
	setCheckable(true);
	setChecked(false);
}

ToggleButton::ToggleButton(const QString &name, QWidget *parent)
	: ToggleButton(parent)
{
	onStateText_ = name;
	offStateText_ = name;
}

ToggleButton::ToggleButton(const QString &name,
						   const QColor &onStateColor,
						   const QColor &offStateColor,
						   QWidget *parent)
	: ToggleButton(parent)
{
	  onStateText_ = name;
	  offStateText_ = name;
	  onStateColor_  = onStateColor;
	  offStateColor_  = offStateColor;
}

ToggleButton::ToggleButton(const QString &onStateText, const QString &offStateText,
						   QWidget *parent)
	: ToggleButton(parent)
{
	  onStateText_ = onStateText;
	  offStateText_ = offStateText;
}

ToggleButton::ToggleButton(const QString &onStateText, const QString &offStateText,
						   const QColor &onStateColor, const QColor &offStateColor,
						   QWidget *parent)
	: ToggleButton(parent)
{
	  onStateText_ = onStateText;
	  offStateText_ = offStateText;
	  onStateColor_ = onStateColor;
	  offStateColor_ = offStateColor;
}

void ToggleButton::setStatesTexts(const QString& on, const QString &off)
{
	onStateText_ = on;
	offStateText_ = off;
}

void ToggleButton::setStatesColors(const QColor &on, const QColor &off)
{
	onStateColor_ = on;
	offStateColor_ = off;
}

void ToggleButton::paintEvent(QPaintEvent *event)
{
	if (isChecked()) {
		if (onStateColor_.isValid() && offStateColor_.isValid()) {
			QPalette pal = palette();
			pal.setColor(QPalette::Button, onStateColor_);
			setPalette(pal);
		}
		setText(onStateText_);
	} else {
		if (onStateColor_.isValid() && offStateColor_.isValid()) {
			QPalette pal = palette();
			pal.setColor(QPalette::Button, offStateColor_);
			setPalette(pal);
		}
		setText(offStateText_);
	}

	QPushButton::paintEvent(event);
}
