#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/video/video.hpp>
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
    //    virtual  bool process( Mat img)
    //    {
    //        return false;
    //    }
    //    virtual  bool process( int t)
    //    {
    //        return false;
    //    }
    //    virtual bool process(Mat img_src,vector<Rect> &rects)
    //    {

    //    }
    virtual bool process(Mat img_src,JsonPacket &pkt)=0;
    //    {
    //        prt(info,"actual processor needed");
    //    }
    //    virtual bool process(Mat img_src,vector<Rect> &rects,Rect detect_area)
    //    {

    //        return false;
    //    }

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




class DummyProcessorOutputData:public JsonData{

public:
    vector<VdPoint> Points;
    int Radii;
    DummyProcessorOutputData()
    {
    }
    DummyProcessorOutputData(JsonPacket str):JsonData(str)
    {
        decode();
    }
    DummyProcessorOutputData(vector<VdPoint> o,int r):Radii(r)
    {
        Points.assign(o.begin(),o.end());
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(Points);
        DECODE_INT_MEM(Radii);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(Points);
        ENCODE_INT_MEM(Radii);
    }
};
class DummyProcessorInputData:public JsonData{

public:
    bool Horizon;
    bool Vertical;
    int Radii;
    DummyProcessorInputData(bool h,bool v,int r):Horizon(h),Vertical(v),Radii(r)
    {
        encode();
    }
    DummyProcessorInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    void decode()
    {
        DECODE_BOOL_MEM(Horizon);
        DECODE_BOOL_MEM(Vertical);
        DECODE_INT_MEM(Radii);
    }
    void encode()
    {
        ENCODE_BOOL_MEM(Horizon);
        ENCODE_BOOL_MEM(Vertical);
        ENCODE_INT_MEM(Radii);
    }
};


class C4ProcessorOutputData:public JsonData{

public:
    vector <VdRect> Rects;
    C4ProcessorOutputData()
    {
    }
    C4ProcessorOutputData(JsonPacket str):JsonData(str)
    {
        decode();
    }
    C4ProcessorOutputData(vector <VdRect> o):Rects(o)
    {
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(Rects);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(Rects);
    }
};
class C4ProcessorInputData:public JsonData{

public:
    double ratio;
    int scan_step;
    C4ProcessorInputData()
    {
    }
    C4ProcessorInputData(JsonPacket str):JsonData(str)
    {
        decode();
    }
    C4ProcessorInputData(int st,double ra):scan_step(st),ratio(ra)
    {
        encode();
    }
    void decode()
    {
        DECODE_INT_MEM(scan_step);
        DECODE_DOUBLE_MEM(ratio);
    }
    void encode()
    {
        ENCODE_INT_MEM(scan_step);
        ENCODE_DOUBLE_MEM(ratio);
    }
};

class PvdProcessorInputData:public JsonData{
public:
    vector <VdPoint> DetectLine;
    PvdProcessorInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(DetectLine);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(DetectLine);
    }
};

class PvdProcessorOutputData:public JsonData{
public:
    vector <ObjectRect> PvdDetectedObjects;
    int PersonFlow1;
    int PersonFlow2;
    int CurrentPersionCount;
    PvdProcessorOutputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    PvdProcessorOutputData(    vector <ObjectRect> objs,
                               int p1,
                               int p2,
                               int cnt)
    {
        PvdDetectedObjects.assign(objs.begin(),objs.end());
        PersonFlow1=p1;
        PersonFlow2=p2;;
        CurrentPersionCount=cnt;
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(PvdDetectedObjects);
        DECODE_INT_MEM(PersonFlow1);
        DECODE_INT_MEM(PersonFlow2);
        DECODE_INT_MEM(CurrentPersionCount);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(PvdDetectedObjects);
        ENCODE_INT_MEM(PersonFlow1);
        ENCODE_INT_MEM(PersonFlow2);
        ENCODE_INT_MEM(CurrentPersionCount);
    }
};


#endif // VIDEOPROCESSOR_H
