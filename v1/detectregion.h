#ifndef DETECTREGION_H
#define DETECTREGION_H

#include "jsondatadealer.h"
#include "datapacket.h"
class DetectRegionData:public JsonData
{
public:
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
