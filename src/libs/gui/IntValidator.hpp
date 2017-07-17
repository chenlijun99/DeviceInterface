#ifndef INTVALIDATOR_HPP
#define INTVALIDATOR_HPP

#include <QRegExpValidator>

class IntValidator : public QRegExpValidator
{
public:
	IntValidator(QObject *parent = Q_NULLPTR);

	void setRange(int bottom, int top);
	int toNumber(const QString &input) const;
	QValidator::State validate(QString &input, int &pos) const override;

private:
	bool hasRange_ = false;
	int minimum_;
	int maximum_;
};

#endif // INTVALIDATOR_HPP
