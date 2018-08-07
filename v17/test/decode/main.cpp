#include <stdio.h>
#include "tool.h"
#include "videosource.h"
int main(void)
{
    prt(info,"Hello World!\n");
    PdVideoCapture cap("rtsp://192.168.1.95:554/av0_1");

    Mat frm;
    while(1){
        this_thread::sleep_for(chrono::milliseconds(10));
        cap.read(frm);
    }
     cap.release();
    return 0;
}

