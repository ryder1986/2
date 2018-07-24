TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    test.cpp
SRC_PATH=../..
INCLUDEPATH +=$$SRC_PATH/cppjson/include
SOURCES += $$SRC_PATH/cppjson/json_reader.cpp $$SRC_PATH/cppjson/json_writer.cpp  $$SRC_PATH/cppjson/json_value.cpp

HEADERS+=$$SRC_PATH/tool.h \
    test.h
SOURCES += $$SRC_PATH/tool.cpp
INCLUDEPATH +=$$SRC_PATH
HEADERS+=$$SRC_PATH/socket.h
SOURCES+=$$SRC_PATH/socket.cpp
LIBS+=-lpthread
