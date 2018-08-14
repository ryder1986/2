#include <stdio.h>
#include "tool.h"
#include "videosource.h"
int main(void)
{
    //  prt(info,"Hello World!\n");
    //   PdVideoCapture cap("rtsp://192.168.1.95:554/av0_1");
    // PdVideoCapture cap("rtsp://192.168.1.18:554/av0_1");
    //  PdVideoCapture cap("rtsp://192.168.1.219:8554/live/test1");
    //  PdVideoCapture cap("rtsp://192.168.1.216:8554/test1");

    PdVideoCapture cap("rtsp://192.168.1.18/1/h264minor");

    //  VideoCapture cap("rtsp://192.168.1.18/1/h264minor");
    // VideoCapture cap("/root/test.264");


    Mat frm;
    while(1){
        this_thread::sleep_for(chrono::milliseconds(1000));
        cap.read(frm);

        prt(info,"%d",cap.get(CV_CAP_PROP_POS_FRAMES));
        prt(info,"%d",cap.get(CV_CAP_PROP_FRAME_COUNT));
        prt(info,"%d",cap.get(CV_CAP_PROP_POS_MSEC));

    }
    cap.release();

    //    Mat frm1;  PdVideoCapture cap1("rtsp://192.168.1.95:554/av0_1");
    //    while(1){


    //    this_thread::sleep_for(chrono::milliseconds(10));
    //    cap1.read(frm1);

    //    }

    //        cap1.release();
    //    PdVideoCapture cap2("rtsp://192.168.1.95:554/av0_1");
    //    Mat frm2;
    //    this_thread::sleep_for(chrono::milliseconds(10));
    //    cap2.read(frm2);
    //    cap2.release();
    //Mat frm3;
    //VideoSource src("rtsp://192.168.1.95:554/av0_1");

    //while(1){

    //src.get_frame(frm3);
    //}

    return 0;
}

