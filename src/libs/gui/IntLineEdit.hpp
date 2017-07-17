#ifndef INTLINEEDIT_HPP
#define INTLINEEDIT_HPP

#include <QLineEdit>

class IntValidator;

class IntLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	IntLineEdit(QWidget *parent = nullptr);

	void setRange(int minimum, int maximum);
	int number() const;

private:
	IntValidator *validator_;
};

#endif // DECHEXLINEEDIT_H
