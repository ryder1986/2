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

    }
    void decode()
    {
        GET_INT(x);
        GET_INT(y);
    }
    void encode()
    {
        SET_INT(x);
        SET_INT(y);
    }
};

class PolyVers:public JsonDataArray
{
public:
    vector <VdPoint>poly_vers;
    PolyVers(vector<DataPacket> pkt):JsonDataArray(pkt)
    {

    }
    void decode()
    {
        GET_ARRAY(poly_vers);
    }
    void encode()
    {
        SET_ARRAY(poly_vers);
    }
};
class DetectRegionData:public JsonData
{
public:
    int region_id;
    DetectRegionData(DataPacket pkt):JsonData(pkt)
    {

    }
    void decode()
    {

    }
    void encode()
    {

    }
};

class DetectRegion : public VdData<DetectRegionData>
{
public:
    DetectRegion(DataPacket pkt):VdData(pkt)
    {

    }
    void work()
    {

    }
};

#endif // DETECTREGION_H
