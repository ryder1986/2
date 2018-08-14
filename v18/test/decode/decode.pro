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
INCLUDEPATH+=/root/source/opencv/build/__install/include
#LIBS+= -L/root/source/opencv/__install/lib/\
# -lopencv_core -lopencv_highgui -lopencv_objdetect \
#-lopencv_imgproc -lopencv_ml\
# -lopencv_highgui -lopencv_video  -lopencv_videoio -lopencv_videostab -lpthread
LIBS+= -L/root/source/opencv/build/__install/lib/\
 -lopencv_core -lopencv_highgui -lopencv_objdetect \
-lopencv_imgproc -lopencv_ml\
 -lopencv_highgui -lopencv_video -lopencv_videoio  -lopencv_videostab -lpthread
INCLUDEPATH+= $$SRC_PATH

LIBS+=-L/root/source/ffmpeg-2.8.14/__install/lib -lavcodec -lavformat -lavutil -lswresample
