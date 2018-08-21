#ifndef DETECTREGION_H
#define DETECTREGION_H


#include "jsonpacket.h"
//#include "pvdmvncprocessor.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;


class DetectRegionData:public JsonData
{

public:
    string SelectedProcessor;
    vector <VdPoint>ExpectedAreaVers;
    JsonPacket ProcessorData;
    DetectRegionData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    DetectRegionData(JsonPacket pdata,string type,vector<VdPoint> vers):ProcessorData(pdata),SelectedProcessor(type),ExpectedAreaVers(vers)
    {
        encode();
    }

    void set_point(VdPoint p,int index)
    {
        ExpectedAreaVers[index-1]=p;
        encode();
    }
    void operator =(DetectRegionData dt)
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
        ENCODE_OBJ_ARRAY_MEM(ExpectedAreaVers);
        ENCODE_STRING_MEM(SelectedProcessor);
        ENCODE_OBJ_MEM(ProcessorData);
    }

};

class RegionRst:public JsonData
{

public:
    JsonPacket reslut_rect;
    JsonPacket detect_rect;
    RegionRst(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    RegionRst(JsonPacket rst_rect ,JsonPacket rct):reslut_rect(rst_rect)
    {
        detect_rect=rct;
        encode();
    }

    void decode()
    {
        DECODE_OBJ_MEM(reslut_rect);
        DECODE_OBJ_MEM(detect_rect);
    }

    void encode()
    {
        ENCODE_OBJ_MEM(reslut_rect);
        ENCODE_OBJ_MEM(detect_rect);
    }

};
#include "videoprocessor.h"
#include "c4processor.h"
class DetectRegion : public VdData<DetectRegionData>
{
    int tmp;
    VideoProcessor *p;
    Rect detect_rect;
public:
    enum OP{
        CHANGE_RECT
    };

    DetectRegion(DetectRegionData pkt):VdData(pkt)
    {
        //  p=new PvdMvncProcessor();
        p=new PvdC4Processor(pkt.data());
        //p=new DummyProcessor();
        detect_rect=reshape_2_rect(private_data.ExpectedAreaVers);
    }

    JsonPacket work(Mat frame)
    {
        JsonPacket rst_r;
        Mat tmp=frame(detect_rect);
        p->process(tmp,rst_r);
        VdRect r(detect_rect.x,detect_rect.y,detect_rect.width,detect_rect.height);
        JsonPacket dct_rct=r.data();
        RegionRst rst(rst_r,dct_rct);
        return rst.config;
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
