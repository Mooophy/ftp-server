TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS += -std=c++11 -pthread
LIBS += -pthread
LIBS += -lboost_system
LIBS += -lboost_regex

SOURCES += \
    main.cpp

HEADERS += \
    users.hpp
