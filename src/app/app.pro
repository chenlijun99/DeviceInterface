TEMPLATE = app
TARGET = DeviceInterface
DESTDIR = $$PROJECT_ROOT/bin

include($$COMMON_PRI)

QT += widgets
LIBS += -lgui -lconfiguration -ldevice -lqt_adapter -ludev -llua5.1

SOURCES += \
    main.cpp \

HEADERS += \
    Application.hpp
