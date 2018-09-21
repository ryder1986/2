#include "mainwindow.h"
#include <QApplication>
#include "videosource.h"
int main(int argc, char *argv[])
{
   // VideoSource src("rtsp://192.168.1.95:554/av0_1");
   // VideoSource src("Z:\\test.264");
   // VideoSource src("Z:\\test.png");
//    VideoSource src("rtsp:\\192.168.1.95:554\av0_1");
//      cv::Mat frame;
//    int ts;

//    while(1){
//           bool ret=src.get_frame(frame,ts);
//    if(ret){
//        printf("ok");
//        cv::imshow("111",frame);
//        cv::waitKey();
//       // cv::imwrite("Z:\\test1.png",frame);
//    }else{
//        printf("err");

//    }
//    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
