CONFIG += console c++11
DEFINES+=IS_UNIX
CONFIG -= app_bundle
CONFIG -= qt
TEMPLATE = app

install_files1.files+=res/
install_files1.path=$$OUT_PWD/
INSTALLS+=install_files1

HEADERS += configmanager.h tool.h app.h server.h camera.h videosource.h \
    detectregion.h socket.h
SOURCES += main.cpp  configmanager.cpp tool.cpp app.cpp server.cpp camera.cpp videosource.cpp \
    detectregion.cpp socket.cpp

INCLUDEPATH +=cppjson/include
HEADERS += cppjson/include/json/reader.h cppjson/include/json/writer.h cppjson/include/json/value.h
SOURCES += cppjson/json_reader.cpp cppjson/json_writer.cpp  cppjson/json_value.cpp


LIBS+= -lopencv_core -lopencv_highgui -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_highgui -lopencv_video   -lpthread

HEADERS+=jsonpacket.h
