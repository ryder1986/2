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

class VdPoint:public JsonData
{
public:
    int x;
    int y;
    VdPoint(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    VdPoint(int x,int y):x(x),y(y)
    {
        encode();
    }
    VdPoint()
    {

    }
    void decode()
    {
        DECODE_INT_MEM(x);
        DECODE_INT_MEM(y);
    }
    void encode()
    {
        ENCODE_INT_MEM(x);
        ENCODE_INT_MEM(y);
    }
};
class DetectRegionData:public JsonData
{

public:
    int region_id;
    string detector_type;
    vector <VdPoint>poly_vers;
    DetectRegionData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    void set_point(VdPoint p,int index)
    {
        poly_vers[index-1]=p;
        encode();
    }

    void decode()
    {
        DECODE_INT_MEM(region_id);
        DECODE_OBJ_ARRAY_MEM(poly_vers);
        DECODE_STRING_MEM(detector_type);
    }
    void encode()
    {
        ENCODE_INT_MEM(region_id);
        ENCODE_OBJ_ARRAY_MEM(poly_vers);
        ENCODE_STRING_MEM(detector_type);
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
        // p=new PvdC4Processor(pkt.data());
        p=new DummyProcessor();
        for(VdPoint p:private_data.poly_vers)
        {
            prt(info,"(%d,%d) ",p.x,p.y);
        }
        detect_rect=reshape_2_rect(private_data.poly_vers);
    }
    JsonPacket work(Mat frame)
    {
        JsonPacket d;
        vector<Rect> rects1;
        Rect detect_area1;
        Mat tmp=frame(detect_rect);
        p->process(tmp,rects1,detect_area1);
        for(Rect r:rects1){

        }
        Rect r1=rects1[0];
      //  prt(info,"-----------> %d",r1.x);
        d.add("x",r1.x);
        d.add("y",r1.y);
        d.add("w",r1.width);
        d.add("h",r1.height);
        //        d.add("x",1+tmp++%200);
        //        d.add("y",1+tmp++%200);
        //        d.add("w",1+tmp++%200);
        //        d.add("h",1+tmp++%200);
        return d;
    }
    void change_detector(string name)
    {

    }
    void change_area( vector <VdPoint>poly_vers)
    {
        private_data.poly_vers=poly_vers;
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
