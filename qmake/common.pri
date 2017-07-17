CONFIG += c++14 silent DEBUG

INCLUDEPATH += \
    $$PROJECT_ROOT/src/libs \
    $$PROJECT_ROOT/src/libs/gui \
    $$PROJECT_ROOT/third_party/json/include \
    $$PROJECT_ROOT/third_party/Catch/include \
    $$PROJECT_ROOT/third_party/sol/include \
    /usr/include/lua5.1/

LIBS += -L$$BUILD_ROOT/lib
