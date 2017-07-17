#ifndef TOGGLEBUTTON_HPP
#define TOGGLEBUTTON_HPP

#include <QPushButton>

class QString;
class QColor;

class ToggleButton : public QPushButton
{
	Q_OBJECT
public:
	ToggleButton(QWidget *parent = Q_NULLPTR);
	ToggleButton(const QString &name,
				 QWidget *parent = Q_NULLPTR);
	ToggleButton(const QString &name,
				 const QColor &onStateColor,
				 const QColor &offStateColor,
				 QWidget *parent = Q_NULLPTR);
	ToggleButton(const QString &onStateText, const QString &offStateText,
				 QWidget *parent = Q_NULLPTR);
	ToggleButton(const QString &onStateText, const QString &offStateText,
				 const QColor &onStateColor, const QColor &offStateColor,
				 QWidget *parent = Q_NULLPTR);

	void setStatesTexts(const QString& on, const QString &off);
	void setStatesColors(const QColor &on, const QColor &off);

private:
	QString onStateText_;
	QString offStateText_;
	QColor onStateColor_;
	QColor offStateColor_;

protected slots:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // TOGGLEBUTTON_HPP
