#-------------------------------------------------
#
# Project created by QtCreator 2018-07-12T11:30:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
SRC_PATH=../..
INCLUDEPATH +=$$SRC_PATH

CONFIG +=c++11
DEFINES+=IS_UNIX


SOURCES += $$SRC_PATH/tool.cpp

HEADERS  += $$SRC_PATH/tool.h
