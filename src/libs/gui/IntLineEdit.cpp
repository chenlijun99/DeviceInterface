#include "IntLineEdit.hpp"
#include "IntValidator.hpp"

IntLineEdit::IntLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	validator_ = new IntValidator(this);
	setValidator(validator_);
}

void IntLineEdit::setRange(int minimum, int maximum)
{
	validator_->setRange(minimum, maximum);
}

int IntLineEdit::number() const
{
	if (text().isEmpty())
		const_cast<IntLineEdit*>(this)->setText("0");

	return validator_->toNumber(text());
}
