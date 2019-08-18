QT             += core gui location quickwidgets sql printsupport
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
    src/custom_check_box.cpp \
    src/font_manager.cc \
    src/graph_sheet.cpp \
    src/graph_window.cpp \
    src/main.cpp \
    src/main_window.cpp \
    src/sql_query_model.cpp \
    src/state_of_parameters.cpp \
    third_party/qcustomplot/qcustomplot.cc

HEADERS += \
    src/color_select_button.h \
    src/control_panel.h \
    src/custom_check_box.h \
    src/font_manager.h \
    src/graph_sheet.h \
    src/graph_window.h \
    src/gui_config.h \
    src/main_window.h \
    src/sql_query_model.h \
    src/state_of_parameters.h \
    third_party/qcustomplot/qcustomplot.h

RESOURCES += \
    resources.qrc

FORMS += \
    src/control_panel.ui
