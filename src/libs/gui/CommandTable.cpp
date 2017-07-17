#include <CommandTable.hpp>
#include <IntLineEdit.hpp>

#include <QList>
#include <QAction>
#include <QStringList>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QColumnView>
#include <QSize>
#include <QHeaderView>
#include <QDebug>
#include <QResizeEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QTableWidgetItem>

CommandTable::CommandTable(QWidget *parent)
    : QTableWidget(parent)
{
    setupHorizontalHeader();
    verticalHeader()->setVisible(false);
    executeButtonsMapper_ = new QSignalMapper(this);
    comboBoxMapper_ = new QSignalMapper(this);
    // initialize table with one row
    setRowCount(1);

    // setup widgets for the first row
    setupWidgetsAtRow(rowCount()-1);
}

void CommandTable::setupHorizontalHeader()
{
    QStringList headerLabels;
    headerLabels << "On" << "Operation"
				 << "Address" << "Data"
				 << "Feedback" << "Execute";

    setColumnCount(headerLabels.size());
    setHorizontalHeaderLabels(headerLabels);
}

void CommandTable::setupWidgetsAtRow(int row)
{
    // a ugly way to centralize the checkbox
    QCheckBox *executeCheckBox = new QCheckBox(this);
    executeCheckBox->setChecked(true);
    QWidget *checkBoxWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(checkBoxWidget);
    layout->addWidget(executeCheckBox);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    checkBoxWidget->setLayout(layout);
    setCellWidget(row, ColumnOf::ExecuteCheckBox, checkBoxWidget);


    QComboBox *operationComboBox = new QComboBox(this);
    operationComboBox->addItem(tr("Write"));
    operationComboBox->addItem(tr("Read"));
    setCellWidget(row, ColumnOf::Operation, operationComboBox);


    IntLineEdit *registerIndexEdit = new IntLineEdit(this);
    setCellWidget(row, ColumnOf::RegisterIndex, registerIndexEdit);


    IntLineEdit *dataEdit = new IntLineEdit(this);
    dataEdit->setRange(0,255);
    setCellWidget(row, ColumnOf::Data, dataEdit);
    comboBoxMapper_->setMapping(operationComboBox, row);
    connect(operationComboBox, SIGNAL(currentTextChanged(QString)),
            comboBoxMapper_, SLOT(map()));
    connect(comboBoxMapper_, SIGNAL(mapped(int)),
            this, SLOT(triggerDataEdit(int)));

	setItem(row, ColumnOf::Feedback, new QTableWidgetItem(0));


    QPushButton *executeButton = new QPushButton(tr("Execute"), this);
    setCellWidget(row, ColumnOf::ExecuteButton, executeButton);
    // map button of each row to the corresponding row
    executeButtonsMapper_->setMapping(executeButton, row);
    connect(executeButton, SIGNAL(clicked(bool)),
            executeButtonsMapper_, SLOT(map()));
    connect(executeButtonsMapper_, SIGNAL(mapped(int)),
            this, SIGNAL(executionRequested(int)));
}

void CommandTable::resizeEvent(QResizeEvent *event)
{
    QTableWidget::resizeEvent(event);

    // table must fit to its parent, i.e. container
    int width = parentWidget()->size().width();

    // width ratios for each column
    this->setColumnWidth(ColumnOf::ExecuteCheckBox, width * 0.05);
	this->setColumnWidth(ColumnOf::Operation, width * 0.15);
    this->setColumnWidth(ColumnOf::RegisterIndex, width * 0.10);
    this->setColumnWidth(ColumnOf::Data, width * 0.20);
	this->setColumnWidth(ColumnOf::Feedback, width * 0.20);
    this->setColumnWidth(ColumnOf::ExecuteButton, width * 0.05);

    // otherwise there would be a small space empty (ugly).
    horizontalHeader()->setStretchLastSection(true);
}

void CommandTable::addCommand()
{
    // add one row
    insertRow(rowCount());

    // setup the added row with cell widgets
    setupWidgetsAtRow(rowCount()-1);
}

void CommandTable::setFeedBack(int row, const QString& executionResult)
{
    item(row, ColumnOf::Feedback)->setText(executionResult);
}

bool CommandTable::toBeExecuted(int row)
{
    QCheckBox *checkbox = cellWidget(row, ColumnOf::ExecuteCheckBox)->findChild<QCheckBox*>();
    return checkbox->isChecked();
}

QString CommandTable::operation(int row)
{
    return qobject_cast<QComboBox*>(cellWidget(row, ColumnOf::Operation))->currentText();
}
QString CommandTable::data(int row)
{
    return qobject_cast<IntLineEdit*>(cellWidget(row, ColumnOf::Data))->text();
}
QString CommandTable::registerIndex(int row)
{
    return qobject_cast<IntLineEdit*>(cellWidget(row, ColumnOf::RegisterIndex))->text();
}

void CommandTable::triggerDataEdit(int row)
{
    if (operation(row) == "Read")
        qobject_cast<IntLineEdit*>(cellWidget(row, ColumnOf::Data))->setEnabled(false);
    else
        qobject_cast<IntLineEdit*>(cellWidget(row, ColumnOf::Data))->setEnabled(true);
}
