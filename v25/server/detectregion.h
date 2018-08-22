#ifndef DETECTREGION_H
#define DETECTREGION_H
#include "jsonpacket.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
using namespace std;
using namespace cv;
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
    void operator =(DetectRegionInputData dt)
    {
        config=dt.config;
        decode();
    }
    void decode()
    {
        DECODE_OBJ_ARRAY_MEM(ExpectedAreaVers);
        DECODE_OBJ_MEM(ProcessorData);
        DECODE_STRING_MEM(SelectedProcessor);
    }
    void encode()
    {
        ENCODE_OBJ_ARRAY_MEM(obj_2_pkt_array(ExpectedAreaVers));
        ENCODE_STRING_MEM(SelectedProcessor);
        ENCODE_OBJ_MEM(ProcessorData);
    }

};

class DetectRegionOutputData:public JsonData
{

public:
    VdRect DetectionRect;
    JsonPacket Result;
    DetectRegionOutputData(string pkt):JsonData(pkt)
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
        DECODE_OBJ_MEM(DetectionRect);
        DECODE_OBJ_MEM(Result);
    }

    void encode()
    {
        ENCODE_OBJ_MEM(DetectionRect.data());
        ENCODE_OBJ_MEM(Result);
    }

};
#include "videoprocessor.h"
#include "c4processor.h"
class DetectRegion : public VdData<DetectRegionInputData>
{
    int tmp;
    VideoProcessor *p;
    Rect detect_rect;
public:
    enum OP{
        CHANGE_RECT
    };

    DetectRegion(DetectRegionInputData pkt):VdData(pkt)
    {
        //  p=new PvdMvncProcessor();
        if(private_data.SelectedProcessor=="c4")
            p=new PvdC4Processor(pkt.data());
        if(private_data.SelectedProcessor=="dummy")
            p=new DummyProcessor(JsonPacket());
        detect_rect=reshape_2_rect(private_data.ExpectedAreaVers);
    }

    JsonPacket work(Mat frame)
    {
        JsonPacket rst_r;
        Mat tmp=frame(detect_rect);
        p->process(tmp,rst_r);
        VdRect r(detect_rect.x,detect_rect.y,detect_rect.width,detect_rect.height);
        JsonPacket dct_rct=r.data();
        DetectRegionOutputData rst(rst_r,dct_rct);
        return rst.data();
    }

    void change_detector(string name)
    {

    }

    void change_area( vector <VdPoint>poly_vers)
    {
        private_data.ExpectedAreaVers=poly_vers;
    }

    void modify()
    {

    }
    bool process(JsonPacket data)
    {

    }
private:
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
        return Rect(x_min,y_min,x_max-x_min,y_max-y_min);
    }
};

#endif // DETECTREGION_H
