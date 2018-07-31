#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "tool.h"
#include "datapacket.h"
using namespace std;
using namespace cv;

namespace VideoProcessorNS{
typedef struct args{
    double scale_ratio;
    int scan_step;
    Rect area;
    int no;
    string ratio;

}arg_t;
}
using namespace VideoProcessorNS;
class VideoProcessor
{

protected:
    //  arg_t arg;
public:
    string alg_rst;
#if 1
    VideoProcessor()
    {

    }
#else
    VideoProcessor(DataPacket pkt):JsonDataDealer(pkt)
    {

    }
#endif
    int get_id()
    {
        return channel_id;
    }
    void set_config(DataPacket pkt)
    {
//        private_data.scale_ratio=string2f(pkt.get_string("ratio"));
//        private_data.scan_step=pkt.get_int("step");
//        vector <DataPacket> area=pkt.get_array_packet("detect_area");
//        private_data.area=area_2_rect(area);
//        private_data.area.x=0;
//        private_data.area.y=0;
//        private_data.area.width=640;
//        private_data.area.height=480;
    }



    DataPacket get_config()
    {
        DataPacket pkt;
//        pkt.set_int("step",private_data.scan_step);
//        pkt.set_string("ratio",f2string(private_data.scale_ratio));
        return pkt;
    }
    virtual  bool process( Mat img)
    {
        return false;
    }
    virtual  bool process( int t)
    {
        return false;
    }
    virtual bool process(Mat img_src,vector<Rect> &rects)
    {

    }

    virtual bool process(Mat img_src,vector<Rect> &rects,Rect detect_area)
    {

        return false;
    }

    virtual  string get_rst()
    {
        string ba;
        return ba ;
    }

    virtual void init()
    {
    }

    //    DataPacket get_config()
    //    {
    //        DataPacket ret;
    //        encode(ret);
    //        return ret;
    //    }
    Rect area_2_rect(vector<DataPacket> area)
    {
        int x_min=10000;
        int y_min=10000;
        int x_max=0;
        int y_max=0;
        for(DataPacket pkt: area) {
            int x=pkt.get_int("x");
            int y=pkt.get_int("y");
            //              int x= v.toObject()["x"].toInt();
            //            int y= v.toObject()["y"].toInt();
            if(x<x_min)
                x_min=x;
            if(x>x_max)
                x_max=x;
            if(y<y_min)
                y_min=y;
            if(y>y_max)
                y_max=y;
        }
        return Rect(x_min,y_min,x_max-x_min,y_max-y_min);
    }

protected:
    int channel_id;
private:

};
#endif // VIDEOPROCESSOR_H
