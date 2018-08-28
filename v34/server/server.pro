CONFIG += console c++11
DEFINES+=IS_UNIX
CONFIG -= app_bundle
CONFIG -= qt
TEMPLATE = app
#FFMPEG_PATH=/root/source/ffmpeg2814/__install
#CV_PATH=/root/source/opencv2491/__install
install_files1.files+=res/
install_files1.path=$$OUT_PWD/
INSTALLS+=install_files1
HEADERS += cppjson/include/json/reader.h cppjson/include/json/writer.h cppjson/include/json/value.h \
    fvdprocessor.h \
    pvdprocessor.h
HEADERS +=  tool.h socket.h
SOURCES += cppjson/json_reader.cpp cppjson/json_writer.cpp  cppjson/json_value.cpp \
    fvdprocessor.cpp \
    pvdprocessor.cpp
SOURCES +=tool.cpp socket.cpp
HEADERS +=c4common.h c4processor.h videoprocessor.h rtsp.h
SOURCES +=c4common.cpp c4processor.cpp videoprocessor.cpp
HEADERS += configmanager.h  app.h server.h camera.h videosource.h detectregion.h
SOURCES += main.cpp  configmanager.cpp  app.cpp server.cpp camera.cpp videosource.cpp  detectregion.cpp
INCLUDEPATH +=cppjson/include
HEADERS+=jsonpacket.h
QMAKE_LFLAGS+=-rdynamic
QMAKE_CXXFLAGS +=-g
INCLUDEPATH+=/usr/include/python2.7
LIBS+=-lpython2.7
QMAKE_CXXFLAGS+=-w
#LIBS+=-lavcodec  -lavutil -lswresample
#LIBS+= -L/root/source/opencv-3.2.0/build/__install/lib -lopencv_core -lopencv_highgui -lopencv_objdetect \
#-lopencv_imgproc -lopencv_ml -lopencv_highgui -lopencv_video -lopencv_videostab  -lopencv_videoio -lpthread  -lX11
#LIBS+=-lavformat
INCLUDEPATH+=$$FFMPEG_PATH/include
INCLUDEPATH+=$$CV_PATH/include
##LIBS+= -L/root/source/opencv-3.2.0/build/__install/lib
LIBS+=-lopencv_core -lopencv_highgui -lopencv_objdetect \
-lopencv_imgproc -lopencv_ml -lopencv_highgui -lopencv_video -lopencv_videostab  -lopencv_videoio -lpthread
LIBS+=-lavformat -lavcodec  -lavutil -lswresample
