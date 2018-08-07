TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp

SRC_PATH =../../
HEADERS  += $$SRC_PATH/videosource.h
SOURCES +=$$SRC_PATH/videosource.cpp
HEADERS  += $$SRC_PATH/tool.h
SOURCES +=$$SRC_PATH/tool.cpp

LIBS+= -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_highgui -lopencv_video   -lpthread

INCLUDEPATH+= $$SRC_PATH

LIBS+=-lavcodec -lavformat -lavutil -lswresample
