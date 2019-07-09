QT             += core gui location quickwidgets
CONFIG         += c++11
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AirportMap
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SOURCES += \
    src/color_select_button.cpp \
    src/control_panel.cpp \
    src/font_manager.cc \
    src/main.cpp \
    src/main_window.cpp

HEADERS += \
    src/color_select_button.h \
    src/control_panel.h \
    src/font_manager.h \
    src/gui_config.h \
    src/main_window.h

RESOURCES += \
    resources.qrc

FORMS += \
    src/control_panel.ui
