#ifndef FVDPROCESSOR_H
#define FVDPROCESSOR_H

#include "videoprocessor.h"
#include "jsonpacket.h"
class FvdProcessor : public VideoProcessor
{
public:
    FvdProcessor(){}
    bool process(Mat img_src,JsonPacket &pkt)
    {

    }
};

#endif // FVDPROCESSOR_H
