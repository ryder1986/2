TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
TARGET=test
HEADERS += \
    jsonpacket.h

SRC_PATH=../..
INCLUDEPATH +=$$SRC_PATH/cppjson/include


INCLUDEPATH +=$$SRC_PATH

HEADERS+=$$SRC_PATH/tool.h

QMAKE_LFLAGS+=-L$$OUT_PWD/../build-jsonlib-Unnamed-Debug -ljsonlib

#file1.path=./
#file1.files+=libjson*
#INSTALLS+=file1

DISTFILES += \
    build.sh
