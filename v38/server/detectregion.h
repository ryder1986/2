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

    void set_points(vector <VdPoint> p)
    {
        ExpectedAreaVers=p;
        encode();
    }
    void set_processor(string p)
    {
        SelectedProcessor=p;
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
        //   ENCODE_PKT_ARRAY_MEM(obj_2_pkt_array(ExpectedAreaVers));
        ENCODE_JSONDATA_ARRAY_MEM(ExpectedAreaVers);
        ENCODE_STRING_MEM(SelectedProcessor);
        ENCODE_PKT_MEM(ProcessorData);
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
#include "videoprocessor.h"
#include "c4processor.h"
class DetectRegion : public VdData<DetectRegionInputData>
{
    int tmp;
    VideoProcessor *p;
    Rect detect_rect;
    mutex lock;
public:
    enum OP{
        CHANGE_RECT,
        CHANGE_PROCESSOR
    };

    DetectRegion(DetectRegionInputData pkt):VdData(pkt),p(NULL)
    {
        lock.lock();
        int valid=false;
        //  p=new PvdMvncProcessor();
        if(private_data.SelectedProcessor=="C4")
        {    p=new PvdC4Processor(pkt.data());valid=true;}
        if(private_data.SelectedProcessor=="Dummy")
         {   p=new DummyProcessor(JsonPacket());valid=true;}
        if(!valid){
            prt(info,"processor %s error ,exit",private_data.SelectedProcessor.data());
            exit(0);
        }
        detect_rect=reshape_2_rect(private_data.ExpectedAreaVers);

        lock.unlock();
    }

    JsonPacket work(Mat frame)
    {
        lock.lock();
        JsonPacket rst_r;
        valid_rect(detect_rect,frame.cols,frame.rows);
        Mat tmp=frame(detect_rect);
        p->process(tmp,rst_r);
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

    void modify(RequestPkt pkt)
    {
        lock.lock();
        int op=pkt.Operation;
        switch(op){
        case OP::CHANGE_RECT:
        {
            JsonPacket vers=pkt.Argument;
            vector<JsonPacket> vs=vers.get("ExpectedAreaVers").to_array();
            vector<VdPoint> ps;
            for(JsonPacket pp:vs)
            {
                ps.push_back(VdPoint(pp));
            }
            detect_rect=reshape_2_rect(ps);
            private_data.set_points(ps);
            break;
        }
        case OP::CHANGE_PROCESSOR:

            if(p){
                delete p;
                p=NULL;
            }
            string pro=    pkt.Argument.get("SelectedProcessor").to_string();
            if(pro=="C4"){
                p=new PvdC4Processor(JsonPacket());
                private_data.set_processor(pro);
            }
            if(pro=="Dummy"){
                p=new DummyProcessor(JsonPacket());
                private_data.set_processor(pro);
            }
            break;

defalut:break;
        }
        lock.unlock();
    }
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