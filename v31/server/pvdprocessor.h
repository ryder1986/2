#ifndef PVDPROCESSOR_H
#define PVDPROCESSOR_H

#include "videoprocessor.h"
#include "jsonpacket.h"
class PvdProcessorInputData:public JsonData{
public:
    vector <VdPoint> DetectLine;
    PvdProcessorInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    void decode()
    {
        DECODE_OBJ_ARRAY_MEM(DetectLine);
    }
    void encode()
    {
        ENCODE_OBJ_ARRAY_MEM_G(DetectLine);
    }
};

class PvdProcessorOutputData:public JsonData{
public:
    vector <ObjectRect> PvdDetectedObjects;
    int PersonFlow1;
    int PersonFlow2;
    int CurrentPersionCount;
    PvdProcessorOutputData()
    {

    }
    void decode()
    {
        DECODE_OBJ_ARRAY_MEM(PvdDetectedObjects);
        DECODE_INT_MEM(PersonFlow1);
        DECODE_INT_MEM(PersonFlow2);
        DECODE_INT_MEM(CurrentPersionCount);
     }
    void encode()
    {
        ENCODE_OBJ_ARRAY_MEM_G(PvdDetectedObjects);
        ENCODE_INT_MEM(PersonFlow1);
        ENCODE_INT_MEM(PersonFlow2);
        ENCODE_INT_MEM(CurrentPersionCount);
    }
};
class PvdProcessor : public VideoProcessor
{
public:
    PvdProcessor()
    {

    }

    ~PvdProcessor()
    {

    }
    bool process(Mat img_src,JsonPacket &pkt)
    {

    }
};

#endif // PVDPROCESSOR_H
