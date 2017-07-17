#ifndef COMMANDTABLE_H
#define COMMANDTABLE_H

#include <QTableWidget>
#include <QList>
#include <QPair>

class QCheckBox;
class QComboBox;
class QPushButton;
class QSignalMapper;

class CommandTable : public QTableWidget
{
    Q_OBJECT
public:
    CommandTable(QWidget *parent = Q_NULLPTR);

    ///
    /// \brief toBeExecuted
    /// \param row
    /// \return true if the execute checkbox at @row is checked, false otherwise
    bool toBeExecuted(int row);

    ///
    /// \brief operation
    /// \param row
    /// \return a string that identifies the operation to be done at @row ("Read" or "Write")
    QString operation(int row);

    QString data(int row);
    QString registerIndex(int row);

    enum ColumnOf
    {
        ExecuteCheckBox = 0,	// just to be sure that enum starts with 0
        Operation,
        RegisterIndex,
        Data,
        Feedback,
		ExecuteButton
    };

public slots:
    ///
    /// \brief addCommand
    /// add a new row and fill it with widgets
    void addCommand();

    ///
    /// \brief setFeedBack
    /// \param row
    /// \param executionResult
    /// set text of FeedBack field at @row as @executionResult
    void setFeedBack(int row, const QString &executionResult);

    ///
    /// \brief disableDataEdit
    /// if operation is read, disable data edit
    void triggerDataEdit(int row);

signals:
    ///
    /// \brief executionRequested
    /// \param row
    /// this signal notifies that a request for execution
    /// of the command at @row has been raised
    void executionRequested(int row);

private:
    QSignalMapper *comboBoxMapper_;
    QSignalMapper *executeButtonsMapper_;

    ///
    /// \brief resizeEvent
    /// \param event
    /// overrided resizeEvent makes the table fit its container
    /// and the colums assume the ratio that I want
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void setupHorizontalHeader();

    ///
    /// \brief setupCellsWidgets
    /// \param row
    /// fill each column of @row with appropriate widgets
    /// (e.g. a combo box containing two items ("read" and "write") for the "operation" column
    void setupWidgetsAtRow(int row);

    void setupEvents();
};

#endif // COMMANDTABLE_H
