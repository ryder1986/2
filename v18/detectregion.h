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
    DetectRegionData(int id,string type,vector<VdPoint> vers):region_id(id),detector_type(type),poly_vers(vers)
    {
        encode();
    }

    void set_point(VdPoint p,int index)
    {
        poly_vers[index-1]=p;
        encode();
    }
    void operator =(DetectRegionData dt)
    {
        config=dt.config;
        decode();
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
class VdRect:public JsonData
{

public:
    int x;
    int y;
    int w;
    int h;
    VdRect(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    VdRect(int x1,int y1,int w1,int h1):x(x1),y(y1),w(w1),h(h1)
    {
        encode();
    }

    void decode()
    {
        DECODE_INT_MEM(x);
        DECODE_INT_MEM(y);
        DECODE_INT_MEM(w);
        DECODE_INT_MEM(h);

    }
    void encode()
    {
        ENCODE_INT_MEM(x);
        ENCODE_INT_MEM(y);
        ENCODE_INT_MEM(w);
        ENCODE_INT_MEM(h);
    }

};
class RegionRst:public JsonData
{

public:

    vector <VdRect>rects;
    RegionRst(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    RegionRst(vector <VdRect>rcts )
    {
        for(VdRect v:rcts){
            rects.push_back(v);
        }
        encode();
    }
    void decode()
    {

        DECODE_OBJ_ARRAY_MEM(rects);
    }
    void encode()
    {
        ENCODE_OBJ_ARRAY_MEM(rects);
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
        detect_rect=reshape_2_rect(private_data.poly_vers);
    }
    JsonPacket work(Mat frame)
    {
        JsonPacket d;
        vector<Rect> rects1;
        Rect detect_area1;
        Mat tmp=frame(detect_rect);
        p->process(tmp,rects1,detect_area1);
        vector <VdRect> rcs;
        for(Rect r:rects1){
            rcs.push_back(VdRect(r.x+detect_rect.x,r.y+detect_rect.y,r.width,r.height));
        }
        RegionRst rst(rcs);
        return rst.config;
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
