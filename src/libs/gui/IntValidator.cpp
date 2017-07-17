#include "IntValidator.hpp"

IntValidator::IntValidator(QObject *parent)
	: QRegExpValidator(parent)
{
	// by default the validator doesn't check for input number range
	hasRange_ = false;

	/*
	 * accepted inputs are
	 * 1. start with "0x" followed by number and/or uppercase letters from A to F
	 * 2. start with "0x" followed by number and/or lowercase letters from a to f
	 * 3. start with "b" followed by 0 or 1
	 * 4. A normal number
	 */
	setRegExp(QRegExp("(^0x([0-9]|[A-F])+$)"
					  "|(^0x([0-9]|[a-f])+$)"
					  "|(^b([0-1])+$)"
					  "|(^[0-9]+$)"));
}

void IntValidator::setRange(int minimum, int maximum)
{
	minimum_ = minimum;
	maximum_ = maximum;
	hasRange_ = true;
}

int IntValidator::toNumber(const QString &input) const
{
	int number;

	// if the 2nd char is an x, then the string is a hex number
	// perform conversion from hex value to int
	if (input.size() > 1 && input[1] == 'x') {
		bool conversion;
		number = input.toInt(&conversion, 16);

	// if the 1st char is an b, then the string is a binary number
	// perform conversion from binary value to int
	} else if (input[0] == 'b') {
		bool conversion;
		number = input.mid(1).toInt(&conversion, 2);
	} else {
		// default base 10 conversion
		number = QString(input).toInt();
	}

	return number;
}

QValidator::State IntValidator::validate(QString &input, int &pos) const
{
	QValidator::State state = QRegExpValidator::validate(input, pos);

	if (state == QValidator::Acceptable) {
		if (hasRange_) {
			int number = toNumber(input);
			if (number < minimum_ || number > maximum_)
				return QValidator::Invalid;
			else
				return QValidator::Acceptable;
		} else {
			return state;
		}
	} else {
		return state;
	}
}
