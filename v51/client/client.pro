#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T11:30:37
#
#-------------------------------------------------
#greaterThan(QT_MAJOR_VERSION, 4) QT += widgets
#QT       += core  network

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG+=WITH_CUDA
WITH_CUDA{
    DEFINES+=WITH_CUDA
}

QT += widgets network
TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    playerwidget.cpp

HEADERS  += mainwindow.h \
    playerwidget.h
FORMS    += mainwindow.ui

CONFIG +=c++11
DEFINES+=IS_UNIX

SRC_PATH =../server
HEADERS  += $$SRC_PATH/tool.h
INCLUDEPATH +=$$SRC_PATH/cppjson/include
INCLUDEPATH +=$$SRC_PATH/

HEADERS +=$$SRC_PATH/cppjson/include/json/reader.h $$SRC_PATH/cppjson/include/json/writer.h $$SRC_PATH/cppjson/include/json/value.h

SOURCES += $$SRC_PATH/tool.cpp
SOURCES += $$SRC_PATH/cppjson/json_reader.cpp $$SRC_PATH/cppjson/json_writer.cpp  $$SRC_PATH/cppjson/json_value.cpp
SOURCES += $$SRC_PATH/videosource.cpp

LIBS+= -L/root/source/opencv-3.2.0/build/__install/lib -lopencv_core -lopencv_highgui -lopencv_objdetect \
-lopencv_imgproc -lopencv_ml -lopencv_highgui -lopencv_video -lopencv_videostab  -lopencv_videoio -lpthread  -lX11
LIBS+=-lavformat -lavcodec  -lavutil -lswresample

