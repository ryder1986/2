#ifndef CAMERA_H
#define CAMERA_H
#include "tool.h"
#include "videosource.h"
#include "detectregion.h"
class CameraInputData:public JsonData
{
public:
    string Url;
    vector <JsonPacket >DetectRegion;
    CameraInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    CameraInputData()
    {
    }
    CameraInputData(vector <JsonPacket> regions,string url):DetectRegion(regions),Url(url)
    {
        encode();
    }

    void set_region(JsonPacket data,int index)
    {
        DetectRegion[index-1]=data;
        encode();
    }

    void replace_point()
    {

    }
    void decode()
    {
        DECODE_STRING_MEM(Url);
        DECODE_OBJ_ARRAY_MEM(DetectRegion);
    }
    void encode()
    {
        // detect_regions.clear();
        ENCODE_STRING_MEM(Url);
        ENCODE_OBJ_ARRAY_MEM(DetectRegion);
    }
};
class CameraOutputData:public JsonData
{
public:
    vector<JsonPacket> DetectionResult;
    int Timestamp;
    CameraOutputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    CameraOutputData()
    {
    }
    CameraOutputData(vector <JsonPacket> regions,int ts):DetectionResult(regions),Timestamp(ts)
    {
        encode();
    }

//    void set_region(JsonPacket data,int index)
//    {
//        DetectRegion[index-1]=data;
//        encode();
//    }

//    void replace_point()
//    {

//    }
    void decode()
    {
        DECODE_INT_MEM(Timestamp);
        DECODE_OBJ_ARRAY_MEM(DetectionResult);
    }
    void encode()
    {
        ENCODE_INT_MEM(Timestamp);
        ENCODE_OBJ_ARRAY_MEM(DetectionResult);
    }
};
class Camera:public VdData<CameraInputData>
{
public:
    enum OP{
        CHANGE_URL,
        INSERT_REGION,
        DELETE_REGION,
        MODIFY_REGION
    };
    function <void(Camera *,string)>callback_result;
public:
    Camera(JsonPacket cfg,function <void(Camera *,string)>fc):VdData(cfg),quit(false),callback_result(fc)
    {
        for(JsonPacket p:private_data.DetectRegion){
            drs.push_back(new DetectRegion(p));
        }
        src=new VideoSource(private_data.Url);
        start();
    }
    ~Camera()
    {
        prt(info,"exiting %s",private_data.Url.data());
        quit=true;
        if(work_trd->joinable())
            work_trd->join();
        prt(info,"exiting %s",private_data.Url.data());
        delete work_trd;
        for(DetectRegion *pro:drs)
            delete pro;
        drs.clear();
        prt(info,"exited %s",private_data.Url.data());
        delete src;
    }

    void run_process()
    {
        Mat frame;
        int ts;
        while(!quit){
            this_thread::sleep_for(chrono::milliseconds(10));
            if(src->get_frame(frame,ts)){
#if 0
                for(DetectRegion *r:drs){
                    JsonPacket ret=r->work(frame);
                    callback_result(this,ret.str());
                }
#endif
             vector<   JsonPacket >pkt;
                for(DetectRegion *r:drs){
                    JsonPacket ret=r->work(frame);
                    pkt.push_back(ret);
                    //prt(info,"get a rect ");
                }

                CameraOutputData cod(pkt,ts);
                timestamp=ts;
                callback_result(this,cod.data().str());
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

    void change_source(string url)
    {
        if(src)
            delete src;
        src=new VideoSource(url);
    }

    void modify_detect_region(JsonPacket pkt)
    {
        int index=pkt.get("index").to_int();
    }
    int get_frame_ts()
    {
        return timestamp;
    }
    void modify(JsonPacket jp)
    {
         RequestPkt req(jp);
         switch (req.Operation) {
         case OP::CHANGE_URL:
             break;
         case OP::INSERT_REGION:

             break;
         case OP::DELETE_REGION:

             break;
         case OP::MODIFY_REGION:

             break;
         default:
             break;
         }
    }

private:
    vector<DetectRegion*> drs;
    VideoSource *src;
    bool quit;
    thread *work_trd;
    int timestamp;
};

#endif // CAMERA_H
