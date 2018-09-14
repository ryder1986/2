#ifndef DETECTREGION_H
#define DETECTREGION_H
#include "jsonpacket.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include "videoprocessor.h"
using namespace std;
using namespace cv;
#define LABLE_PROCESSOR_C4 "C4"
#define LABLE_PROCESSOR_DUMMY "Dummy"

#ifdef WITH_CUDA
#define LABLE_PROCESSOR_PVD "Pvd"
#define LABLE_PROCESSOR_FVD "Fvd"
#define LABLE_PROCESSOR_MVD "Mvd"
#endif
class DetectRegionInputData:public JsonData
{

public:
    string SelectedProcessor;
    vector <VdPoint>ExpectedAreaVers;
    JsonPacket ProcessorData;
    DetectRegionInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    DetectRegionInputData(JsonPacket pdata,string type,vector<VdPoint> vers)
        :ProcessorData(pdata),SelectedProcessor(type),ExpectedAreaVers(vers)
    {
        encode();
    }

    void set_point(VdPoint p,int index)
    {
        ExpectedAreaVers[index-1]=p;
        encode();
    }

    void set_points(vector <VdPoint> p)
    {
        ExpectedAreaVers=p;
        encode();
    }
    void set_processor(string p,JsonPacket pd)
    {
        SelectedProcessor=p;
        ProcessorData=pd;
        encode();
    }
    void operator =(DetectRegionInputData dt)
    {
        config=dt.config;
        decode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(ExpectedAreaVers);
        DECODE_PKT_MEM(ProcessorData);
        DECODE_STRING_MEM(SelectedProcessor);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(ExpectedAreaVers);
        ENCODE_STRING_MEM(SelectedProcessor);
        ENCODE_PKT_MEM(ProcessorData);
    }

};
class ProcessorDataJsonData:public JsonData{
public:
    string SelectedProcessor;
    JsonPacket ProcessorData;
    ProcessorDataJsonData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    ProcessorDataJsonData(string pro,JsonPacket d)
    {
        ProcessorData=d;
        SelectedProcessor=pro;
        encode();
    }
    void decode()
    {
        DECODE_STRING_MEM(SelectedProcessor);
        DECODE_PKT_MEM(ProcessorData);
    }
    void encode()
    {
        ENCODE_STRING_MEM(SelectedProcessor);
        ENCODE_PKT_MEM(ProcessorData);
    }
};
class AreaVersJsonData:public JsonData{
public:
    vector <VdPoint>ExpectedAreaVers;
    AreaVersJsonData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    AreaVersJsonData(vector <VdPoint> vs)
    {
        ExpectedAreaVers.assign(vs.begin(),vs.end());
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(ExpectedAreaVers);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(ExpectedAreaVers);
    }
};
class DetectRegionOutputData:public JsonData
{
public:
    VdRect DetectionRect;
    JsonPacket Result;
    DetectRegionOutputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    DetectRegionOutputData(JsonPacket rst ,VdRect rct)
    {
        DetectionRect=rct;
        Result=rst;
        encode();
    }

    void decode()
    {
        DECODE_PKT_MEM(DetectionRect);
        DECODE_PKT_MEM(Result);
    }

    void encode()
    {
        ENCODE_JSONDATA_MEM(DetectionRect);
        ENCODE_PKT_MEM(Result);
    }

};

class DetectRegion : public VdData<DetectRegionInputData>
{
    int tmp;
    VideoProcessor *p;
    Rect detect_rect;
    mutex lock;
public:
    enum OP{
        CHANGE_RECT,
        CHANGE_PROCESSOR,
        MODIFY_PROCESSOR
    };


    DetectRegion(DetectRegionInputData pkt);

    ~DetectRegion()
    {
        if(p)
            delete p;
        p=NULL;
    }

    JsonPacket work(Mat frame)
    {
        lock.lock();
        JsonPacket rst_r;
        valid_rect(detect_rect,frame.cols,frame.rows);
        if(detect_rect.width%2)detect_rect.width--;
        if(detect_rect.height%2)detect_rect.height--;
        Mat tmp=frame(detect_rect);
        if(p &&detect_rect.x>=0&&detect_rect.x<10000
                &&detect_rect.y>=0&&detect_rect.y<10000
                &&detect_rect.width>0&&detect_rect.width<10000
                &&detect_rect.height>0&&detect_rect.height<10000
                &&frame.cols>0&&frame.rows>0
                ){
            p->process(tmp,rst_r);
        }else{
            prt(info,"err arg");
        }
        //  p->process(frame,rst_r);
        VdRect r(detect_rect.x,detect_rect.y,detect_rect.width,detect_rect.height);
        JsonPacket dct_rct=r.data();
        DetectRegionOutputData rst(rst_r,dct_rct);
        lock.unlock();
        return rst.data();
    }

    void change_detector(string name)
    {

    }

    void change_area( vector <VdPoint>poly_vers)
    {
        private_data.ExpectedAreaVers=poly_vers;
    }

    void modify(RequestPkt pkt);
    bool process(JsonPacket data)
    {

    }
private:
    inline void valid_rect(Rect &area,int max_w,int max_h)
    {
        if((area.x+area.width)>max_w)
            area.width=max_w-area.x;
        if((area.y+area.height)>max_h)
            area.height=max_h-area.y;
    }
    Rect reshape_2_rect(vector <VdPoint> area)
    {
        int x_min=10000;
        int y_min=10000;
        int x_max=0;
        int y_max=0;
        for(VdPoint pkt: area) {
            int x=pkt.x;
            int y=pkt.y;
            if(x<x_min)
                x_min=x;
            if(x>x_max)
                x_max=x;
            if(y<y_min)
                y_min=y;
            if(y>y_max)
                y_max=y;
        }
        x_min=x_min>0?x_min:0;
        y_min=y_min>0?y_min:0;
        x_max=x_max>0?x_max:0;
        y_max=y_max>0?y_max:0;
        return Rect(x_min,y_min,x_max-x_min,y_max-y_min);
    }
};

#endif // DETECTREGION_H
