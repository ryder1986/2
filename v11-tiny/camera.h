#ifndef CAMERA_H
#define CAMERA_H
#include "tool.h"
#include "videosource.h"
#include "detectregion.h"

class CameraReq:public JsonData
{
public:
    CameraReq(){}
};
class CameraData:public JsonData
{
public:

    string url;
    vector <DetectRegionData >detect_regions;
    CameraData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    CameraData()
    {

    }

    void decode()
    {
        DECODE_STRING_MEM(url);
        DECODE_OBJ_ARRAY_MEM(detect_regions);
    }
    void encode()
    {
        ENCODE_STRING_MEM(url);
        ENCODE_OBJ_ARRAY_MEM(detect_regions);
    }
};

class Camera:public VdData<CameraData>
{
public:
    enum OP{
        ADD_REGION,
        DEL_REGION,
        MOD_REGION,
        CHANGE_SRC_URL
    };
    function <void(Camera *,string)>callback_result;
public:
    Camera(JsonPacket cfg,function <void(Camera *,string)>fc):VdData(cfg),quit(false),callback_result(fc)
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
    Camera(CameraData cfg,function <void(Camera *,string)>fc):VdData(cfg),quit(false),callback_result(fc)
    {
//        quit=true;
//        if(work_trd->joinable())
//            work_trd->join();
//        delete work_trd;

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

        prt(info,"exiting %s",private_data.url.data());
        quit=true;
        if(work_trd->joinable())
            work_trd->join();
            prt(info,"exiting %s",private_data.url.data());
        delete work_trd;
        for(DetectRegion *pro:drs)
            delete pro;
        drs.clear();
            prt(info,"exited %s",private_data.url.data());
        delete src;
    }

    void run_process()
    {
        Mat frame;
        while(!quit){
            this_thread::sleep_for(chrono::milliseconds(10));
            if(src->get_frame(frame)){
                //  prt(info,"get a frame ");
                for(DetectRegion *r:drs){
                    JsonPacket ret=r->work(frame);
                    callback_result(this,ret.data());
                }
            }
        }
    }

    void start()
    {
        //   _start(bind(&TestProcess::run_process,this));
        //  _start(bind(&TestProcess::run_process,this,placeholders::_1),99);
        //_start_async(bind(&Camera::run_process,this));

        work_trd=new thread(bind(&Camera::run_process,this));

        prt(info,"start done ~~~~~~~~~~~~~~~");
    }

//    void stop()
//    {
//        quit=true;
//    }

    void change_source(string url)
    {
        if(src)
            delete src;
        src=new VideoSource(url);
    }
    void modify_detect_region(JsonPacket pkt)
    {
        int index=pkt.get("index").to_int();
     //   drs[index-1]->modify(pkt.get("data"));
    }


private:
    vector<DetectRegion*> drs;
    VideoSource *src;
    bool quit;
    thread *work_trd;
};

#endif // CAMERA_H
