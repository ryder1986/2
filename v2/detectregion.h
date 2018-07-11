#ifndef DETECTREGION_H
#define DETECTREGION_H

#include "jsondatadealer.h"
#include "datapacket.h"
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

class PolyVers:public JsonData
{
public:
    vector <VdPoint>poly_vers;
    PolyVers(DataPacket pkt):JsonData(pkt)
    {
        auto tm1p=config.get_array_packet("poly_vers");
        DECODE_OBJ_ARRAY_MEM(poly_vers);
    }

    PolyVers()
    {

    }
};
class DetectRegionData:public JsonData
{

public:
    int region_id;
    string detector_type;
    PolyVers poly_vers;
    DetectRegionData(DataPacket pkt):JsonData(pkt)
    {
        DECODE_OBJ_MEM(poly_vers);
        DECODE_INT_MEM(region_id);
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

    }
    void work()
    {

    }
};

#endif // DETECTREGION_H
