#ifndef CAMERA_H
#define CAMERA_H
#include "tool.h"
#include "videosource.h"
#include "datapacket.h"
#include "jsondatadealer.h"
#include "detectregion.h"
class CameraData:public JsonData
{
public:
    string url;
    vector <DetectRegionData >detect_regions;
    CameraData(DataPacket pkt):JsonData(pkt)
    {
        DECODE_STRING_MEM(url);
        DECODE_OBJ_ARRAY_MEM(detect_regions);
    }
    CameraData()
    {

    }
};

class Camera:public VdData<CameraData>
{
    function <void(Camera *,const char *,int)>callback_result;
public:
    Camera(DataPacket cfg,function <void(Camera *,const char *,int)>fc):VdData(cfg),quit(false),callback_result(fc)
    {

        //    set_config(cfg);
        for(DetectRegionData p:private_data.detect_regions){

            drs.push_back(new DetectRegion(p));
            //  pros.push_back(new PvdC4Processor(p));
            //        pros.push_back(new PvdMvncProcessor(p.get_pkt("pvd_c4")));
            // pros.push_back(new PvdHogProcessor(p.get_pkt("pvd_c4")));
        }
        src=new VideoSource(private_data.url);
        start();
    }
    Camera(CameraData cfg,function <void(Camera *,const char *,int)>fc):VdData(cfg),quit(false),callback_result(fc)
    {

        //    set_config(cfg);
        for(DetectRegionData p:private_data.detect_regions){
               drs.push_back(new DetectRegion(p));
            // if(GET_STRING_VALUE_FROM_PKT(selected_alg,p)=="pvd_c4")
            //pros.push_back(new PvdC4Processor(p.get_pkt("pvd_c4")));
            //  pros.push_back(new PvdC4Processor(p));
            //        pros.push_back(new PvdMvncProcessor(p.get_pkt("pvd_c4")));
            // pros.push_back(new PvdHogProcessor(p.get_pkt("pvd_c4")));
        }
        src=new VideoSource(private_data.url);
        start();
    }
    ~Camera()
    {
        for(DetectRegion *pro:drs)
            delete pro;
        drs.clear();
    }

    void run_process()
    {
        Mat frame;
        while(!quit){
            this_thread::sleep_for(chrono::milliseconds(10));
            if(src->get_frame(frame)&&frame.cols>0&&frame.rows>0){
              //  prt(info,"get a frame ");
            }
        }
    }

    void start()
    {
        //   _start(bind(&TestProcess::run_process,this));
        //  _start(bind(&TestProcess::run_process,this,placeholders::_1),99);
        _start_async(bind(&Camera::run_process,this));
        prt(info,"start done ~~~~~~~~~~~~~~~");
    }

    void stop()
    {
        quit=true;
    }

private:
    vector<DetectRegion*> drs;
    VideoSource *src;
    bool quit;
};

#endif // CAMERA_H
