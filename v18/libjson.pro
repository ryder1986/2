TEMPLATE=lib

SOURCES+=tool.cpp

HEADERS+=tool.h
CONFIG+=c++11
TARGET=json

INCLUDEPATH +=cppjson/include
HEADERS += cppjson/include/json/reader.h cppjson/include/json/writer.h cppjson/include/json/value.h
SOURCES += cppjson/json_reader.cpp cppjson/json_writer.cpp  cppjson/json_value.cpp
