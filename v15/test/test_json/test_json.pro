TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    jsonpacket.h

SRC_PATH=../..
INCLUDEPATH +=$$SRC_PATH/cppjson/include
INCLUDEPATH +=$$SRC_PATH

SOURCES += $$SRC_PATH/cppjson/json_reader.cpp $$SRC_PATH/cppjson/json_writer.cpp  $$SRC_PATH/cppjson/json_value.cpp

INCLUDEPATH +=$$SRC_PATH

LIBS+=-L/root/build/2/build-libjson-Unnamed-Debug -ljson
LIBS+=-L/root/build/2/build-libsocket-Unnamed-Debug -lsocket
LIBS+=-L/root/build/2/build-libtool-Unnamed-Debug -ltool
