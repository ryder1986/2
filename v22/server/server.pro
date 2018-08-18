CONFIG += console c++11
DEFINES+=IS_UNIX
CONFIG -= app_bundle
CONFIG -= qt
TEMPLATE = app

install_files1.files+=res/
install_files1.path=$$OUT_PWD/
INSTALLS+=install_files1

#HEADERS += configmanager.h tool.h app.h server.h camera.h videosource.h \
#    detectregion.h socket.h
#SOURCES += main.cpp  configmanager.cpp tool.cpp app.cpp server.cpp camera.cpp videosource.cpp \
#    detectregion.cpp socket.cpp
HEADERS += cppjson/include/json/reader.h cppjson/include/json/writer.h cppjson/include/json/value.h
HEADERS +=  tool.h socket.h

SOURCES += cppjson/json_reader.cpp cppjson/json_writer.cpp  cppjson/json_value.cpp
SOURCES +=  tool.cpp socket.cpp
#LIBS+=-L/root/build/2/build-libjson-Unnamed-Debug -ljson
#LIBS+=-L/root/build/2/build-libsocket-Unnamed-Debug -lsocket
#LIBS+=-L/root/build/2/build-libtool-Unnamed-Debug -ltool

HEADERS +=   c4common.h       c4processor.h videoprocessor.h rtsp.h
SOURCES +=   c4common.cpp   c4processor.cpp videoprocessor.cpp
SOURCES +=track/Ctracker.cpp track/HungarianAlg.cpp  track/Kalman.cpp
HEADERS += track/defines.h track/HungarianAlg.h track/Kalman.h track/Ctracker.h

HEADERS += configmanager.h  app.h server.h camera.h videosource.h detectregion.h
SOURCES += main.cpp  configmanager.cpp  app.cpp server.cpp camera.cpp videosource.cpp  detectregion.cpp
INCLUDEPATH +=cppjson/include


LIBS+= -L/root/opencv249/build/__install/lib -lopencv_core -lopencv_highgui -lopencv_objdetect \
-lopencv_imgproc -lopencv_ml -lopencv_highgui -lopencv_video      -lpthread

HEADERS+=jsonpacket.h

QMAKE_LFLAGS+=-rdynamic
QMAKE_CXXFLAGS +=-g


#HEADERS+=pvdmvncprocessor.h
#SOURCES+=pvdmvncprocessor.cpp
#INCLUDEPATH+=/usr/include/python3.5/
#LIBS+=-L/usr/lib/python3.5/config-3.5m-x86_64-linux-gnu/ -lpython3.5

INCLUDEPATH+=/usr/include/python2.7
LIBS+=  -lpython2.7
QMAKE_CXXFLAGS+=-w

LIBS+=-lavcodec  -lavutil -lswresample
LIBS+=-L/root/source/ffmpeg-2.8.14/__install/lib/ -lavformat
