#ifndef COMMANDWINDOW_H
#define COMMANDWINDOW_H

#include <DeviceDockWidget.hpp>

class QPushButton;
class CommandTable;

class CommandPanel : public DeviceDockWidget
{
    Q_OBJECT
public:
    CommandPanel(QWidget *parent = Q_NULLPTR);

public slots:
    ///
    /// \brief executeCommand
    /// \param row
    /// execute the command in the CommandTable at @row
    void executeCommand(int row);
    void executeAllCommands();

private:
	void setupInterface() ;
	void setupEvents();

    CommandTable *commandTable_;
    QPushButton *addCommandButton_;
    QPushButton *saveCommandsButton_;
    QPushButton *importCommandsButton_;
    QPushButton *executeAllCommandsButton_;
};

#endif // COMMANDWINDOW_H
