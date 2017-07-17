#include <cstdio>
#include <cerrno>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>

#include <CommandPanel.hpp>
#include <CommandTable.hpp>
#include <device/Device.hpp>


CommandPanel::CommandPanel(QWidget *parent)
	: DeviceDockWidget(parent)
{
    setWindowTitle(tr("Command Panel"));
    setupInterface();
    setupEvents();
}

void CommandPanel::setupInterface()
{
    // mainWidget will contain all the other widgets
    QFrame *mainWidget = new QFrame(this);
    mainWidget->setFrameStyle(QFrame::Box | QFrame::Sunken);


    // create Table
    commandTable_ = new CommandTable();

    // create buttons
    addCommandButton_ = new QPushButton("Add Command");
    saveCommandsButton_ = new QPushButton("Save");
    importCommandsButton_ = new QPushButton("Import");
    executeAllCommandsButton_ = new QPushButton("Execute all");

    // arrange buttons
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addCommandButton_, 0, Qt::AlignLeft);
    buttonsLayout->addWidget(saveCommandsButton_, 0, Qt::AlignLeft);
    buttonsLayout->addWidget(importCommandsButton_, 0, Qt::AlignLeft);
    buttonsLayout->addWidget(executeAllCommandsButton_, 1, Qt::AlignRight);

    // arrange all together
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(commandTable_);
    mainLayout->addLayout(buttonsLayout);


    // apply mainLayout to mainWidget
    mainWidget->setLayout(mainLayout);

    // set mainWidget as the central widget of the dock widget
    setWidget(mainWidget);
}

void CommandPanel::setupEvents()
{
    // when "Add Command" button is clicked, add a command in the table
    connect(addCommandButton_, &QPushButton::clicked,
            commandTable_, &CommandTable::addCommand);

    connect(executeAllCommandsButton_, &QPushButton::clicked,
            this, &CommandPanel::executeAllCommands);
    connect(commandTable_, &CommandTable::executionRequested,
            this, &CommandPanel::executeCommand);
}

void CommandPanel::executeCommand(int row)
{
	device_->setBufferedIO(true);
	const uint8_t registerIndex = commandTable_->registerIndex(row).toUInt();

	if (commandTable_->operation(row) == "Read") {

		// in the command panel we'll just perform single register read
		// thus there's no need to use and array, a 8 bit variable is enough
		uint8_t buffer;

//		if (device_->read(registerIndex, &buffer) != sizeof(buffer)) {
//			commandTable_->setFeedBack(row, QString(tr("Failed to read from device: ")
//													+ qt_error_string(errno)));
//			return;
//		}
		buffer =  device_->getRegisterValue(registerIndex);
		commandTable_->setFeedBack(row, QString::number(buffer));
	} else {
		const uint8_t data = commandTable_->data(row).toUInt();

		device_->setRegisterValue(registerIndex, data);
//		if (res <= 0) {
//			commandTable_->setFeedBack(row, QString(tr("Failed to write to device: ")
//													   + qt_error_string(errno)));
//			return;
//		}
		commandTable_->setFeedBack(row, QString(tr("1 byte(s) written")));
	}
	device_->setBufferedIO(false);
}

void CommandPanel::executeAllCommands()
{
	for (int i = 0; i < commandTable_->rowCount(); ++i) {
		if (commandTable_->toBeExecuted(i))
			executeCommand(i);
	}
}
