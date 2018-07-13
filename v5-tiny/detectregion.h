#ifndef DETECTREGION_H
#define DETECTREGION_H

#include "jsondatadealer.h"
#include "datapacket.h"


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
    VdPoint(DataPacket pkt):JsonData(pkt)
    {
        DECODE_INT_MEM(x);
        DECODE_INT_MEM(y);
    }
};
class DetectRegionData:public JsonData
{

public:
    int region_id;
    string detector_type;
    vector <VdPoint>poly_vers;
    //PolyVers poly_vers;
    DetectRegionData(DataPacket pkt):JsonData(pkt)
    {
        DECODE_INT_MEM(region_id);
        DECODE_OBJ_ARRAY_MEM(poly_vers);
        DECODE_STRING_MEM(detector_type);
    }

};

class DetectRegion : public VdData<DetectRegionData>
{
public:
    DetectRegion(DataPacket pkt):VdData(pkt)
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
};

#endif // DETECTREGION_H
