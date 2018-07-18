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
class change_region:public RequestData <VdPoint>{
public:
    change_region(){}
};
class DetectRegion : public VdData<DetectRegionData>
{
public:

    DetectRegion(JsonPacket pkt):VdData(pkt)
    {

    }
    DetectRegion(DetectRegionData pkt):VdData(pkt)
    {
        for(VdPoint p:private_data.poly_vers)
        {
            prt(info,"(%d,%d) ",p.x,p.y);
        }
    }
    void work(Mat frame)
    {

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
};

#endif // DETECTREGION_H
