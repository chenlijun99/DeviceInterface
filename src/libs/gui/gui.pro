include($$COMMON_LIBRARY_PRI)

QT += core gui widgets

HEADERS += \
    MainWindow.hpp \
    MainWindowInterface.hpp \
    ConfigurePanel.hpp \
    ConfigurePanelInterface.hpp \
    IntLineEdit.hpp \
    IntValidator.hpp \
    ToggleButton.hpp \
    CommandTable.hpp \
    CommandPanel.hpp \
    MonitoringPanel.hpp \
    FirmwarePanel.hpp \
    DeviceDialog.hpp \
    FirmwarePanelInterface.hpp \
    MonitoringPanelInterface.hpp \
    DeviceDialogInterface.hpp \
    DeviceDockWidget.hpp \
    ConfigurableUiInterface.hpp \
    UiPanelConfiguration.hpp \
#    UiPanelConfiguration.hpp \
    DeviceWidget.hpp \
    ConfigurableDeviceDockWidget.hpp \
    Configuration.hpp

SOURCES += \
    MainWindow.cpp \
    MainWindowInterface.cpp \
    ConfigurePanel.cpp \
    IntLineEdit.cpp \
    IntValidator.cpp \
    ToggleButton.cpp \
    CommandTable.cpp \
    CommandPanel.cpp \
    MonitoringPanel.cpp \
    FirmwarePanel.cpp \
    DeviceDialog.cpp \
    FirmwarePanelInterface.cpp \
    MonitoringPanelInterface.cpp \
    ConfigurePanelInterface.cpp \
    DeviceDialogInterface.cpp \
    DeviceDockWidget.cpp \
    ConfigurableUiInterface.cpp \
    UiPanelConfiguration.cpp \
#    UiConfiguration.cpp \
#    ConfigurableWidget.cpp \
    DeviceWidget.cpp \
    ConfigurableDeviceDockWidget.cpp \
    Configuration.cpp
