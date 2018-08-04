TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS+=test.h
SOURCES += main.cpp \
    test.cpp
SRC_PATH=../..
#INCLUDEPATH +=$$SRC_PATH/cppjson/include
#SOURCES += $$SRC_PATH/cppjson/json_reader.cpp $$SRC_PATH/cppjson/json_writer.cpp  $$SRC_PATH/cppjson/json_value.cpp

#HEADERS+=$$SRC_PATH/tool.h \
#    test.h
#SOURCES += $$SRC_PATH/tool.cpp
INCLUDEPATH +=$$SRC_PATH
INCLUDEPATH +=$$SRC_PATH/cppjson/include
HEADERS+=$$SRC_PATH/socket.h
SOURCES+=$$SRC_PATH/server.cpp
HEADERS+=$$SRC_PATH/server.h
#SOURCES+=$$SRC_PATH/socket.cpp
LIBS+=-L/root/build/2/build-libsocket-Unnamed-Debug -lsocket
LIBS+=-L/root/build/2/build-libtool-Unnamed-Debug -ltool
LIBS+=-lpthread

