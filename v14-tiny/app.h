#ifndef APP_H
#define APP_H

#include "server.h"
#include "tool.h"
#include "camera.h"
#include "configmanager.h"
enum AppRequest{
    SET_CONFIG,
    GET_CONFIG,
    ADD_CAMERA,
    DEL_CAMERA,
    MOD_CAMERA,
    CHANGE_NAME
};

class AppData:public JsonData{
public:
    vector <CameraData> cameras;
    int server_port;
    AppData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    AppData(int port,vector<CameraData> d):server_port(port),cameras(d)
    {
        encode();
    }
    AppData()
    {

    }

    void replace_camera(CameraData d,int index)
    {
        if(index>0&&index<=cameras.size()){
             prt(info," cams  size  %d", cameras.size());
            cameras[index-1]=d;
            prt(info,"set new config on cam %d",index-1);
             prt(info," cams new size  %d", cameras.size());
        }else{
            prt(info," cams size  %d,unchange with index %d", cameras.size(),index);
        }

        encode();
    }

    void decode()
    {
        DECODE_INT_MEM(server_port);
        DECODE_OBJ_ARRAY_MEM(cameras);
    }
    void encode()
    {
        ENCODE_INT_MEM(server_port);
        ENCODE_OBJ_ARRAY_MEM(cameras);
    }
};
template <typename T>
class AppEvent:public RequestData<T>
{
public:
    AppEvent(int op,int index,T d):RequestData<T>(op,index,d)
    {

    }
    AppEvent()
    {

    }
};
class AppEventSetConfig:public AppEvent<AppData>{
public:
    AppEventSetConfig(int op,int index,AppData d):AppEvent(op,index,d)
    {

    }
};
class AppEventSetDevName:public AppEvent<string>{
public:
    AppEventSetDevName(int op,int index,string name):AppEvent(op,index,name)
    {

    }
};
class AppEventModifyCamera:public AppEvent<JsonPacket>{
public:
    AppEventModifyCamera(int op,int index,JsonPacket pkt):AppEvent(op,index,pkt)
    {

    }
    AppEventModifyCamera()
    {

    }
};
class CameraSetUrl:public RequestData<string>{
public:
    AppEventModifyCamera app_req;
    CameraSetUrl(AppEventModifyCamera a,int camera_op,int camera_index, string url):RequestData(camera_op,camera_index,url)
    {
        //     app_req=AppEventModifyCamera(app_op,app_index,config);
    }
};
class CameraEvent:public AppEvent<JsonPacket>{
public:
    CameraEvent(int camera_op,int camera_index,int op,int index,JsonPacket pkt):AppEvent(op,index,pkt)
    {

    }
    CameraEvent()
    {

    }
};
// change area rect
//struct change_app_data{
//     int op;
//     int index;
//     struct change_camera_data{
//        int op;//which region
//        int index;
//        struct change_region_data{
//            int op;
//            int index;
//            Rect r;
//        };
//     };
//};
////change camera url
//struct app_req_data{
//     int op;
//     int index;
//     JsonPacket data;
//};
//struct camera_req_data{
//   int op;//which region
//   int index;
//   JsonPacket data;
//};
//struct region_req_data{
//   int op;//which region
//   int index;
//   JsonPacket data;
//};

//class RegionChangeArea
//{
//public:
//    RegionChangeArea(int op,int camera_index,int ,int camera_index,)
//    {

//    }
//};

//class CameraChangeUrlEvent:public RequestData<string>
//{
//public:
//    CameraChangeUrlEvent(int op,int index,string d):RequestData(op,index,d)
//    {

//    }
//};
//class DetectRegionChangeRectEvent:public RequestData<CameraEvent>
//{
//public:
//    DetectRegionChangeRectEvent(int op,int index,string d):RequestData(op,index,d)
//    {

//    }
//};
class AppReq:public JsonData{
public:

    int request;
    int index;
    JsonPacket pri;
    JsonPacket ret;
    AppReq(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    AppReq()
    {

    }

    void decode()
    {
        DECODE_INT_MEM(request);
        DECODE_INT_MEM(index);
        DECODE_OBJ_MEM(pri);
        DECODE_OBJ_MEM(ret);
    }
    void encode()
    {
        ENCODE_INT_MEM(request);
        ENCODE_INT_MEM(index);
        ENCODE_OBJ_MEM(pri);
        ENCODE_OBJ_MEM(ret);
    }
};
class AppReslut:public JsonData{
public:
    int camera_index;
    JsonPacket camera_data;

    AppReslut(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    AppReslut(int index,JsonPacket data):camera_index(index),camera_data(data)
    {
        encode();
    }

    void decode()
    {
        DECODE_INT_MEM(camera_index);
        DECODE_OBJ_MEM(camera_data);
    }
    void encode()
    {
        ENCODE_INT_MEM(camera_index);
        ENCODE_OBJ_MEM(camera_data);
    }
};
class App:public VdData<AppData>
{
public:
    enum OP{
        ADD_CAMERA,
        DEL_CAMERA,
        MOD_CAMERA,
        GET_CONFIG,
        SET_CONFIG
    };

    App(ConfigManager *p);
    void start()
    {
    }
private:
    void process_client_cmd(Session *clt,char *data,int len);
    void client_data_request(Session *clt, char *data, int len);
    void process_camera_data(Camera *clt,string);
    void restart_all()
    {
        stop_cams();
        start_cams();

//        VideoSource *p1=new VideoSource("rtsp://192.168.1.216:8554/test1");
//        this_thread::sleep_for(chrono::seconds(1));
//           prt(info,"src deleteing..");
//        delete p1;
//               prt(info,"src deleted");

//               VideoSource *p2=new VideoSource("rtsp://192.168.1.216:8554/test1");
//               this_thread::sleep_for(chrono::seconds(1));
//               delete p2;
//                      prt(info,"src deleted");


//                      VideoSource *p3=new VideoSource("rtsp://192.168.1.216:8554/test1");
//                      this_thread::sleep_for(chrono::seconds(1));
//                      delete p3;
//                             prt(info,"src deleted");




//        prt(info,"1");
//        stop_cams();
//         prt(info,"1");
//      //  start_cams();
//         prt(info,"1");
    }
    void start_cams()
    {
        for(CameraData p:private_data.cameras){
            cms.push_back(new Camera(p,bind(&App::process_camera_data,
                                            this,placeholders::_1,
                                            placeholders::_2)));
        }
    }
    void stop_cams()
    {
        for(Camera *c:cms){
            delete c;
        }
        cms.clear();
    }
    void add_camera(int index,JsonPacket data)//after who ?  0~size
    {
        if(0<=index&&index<=cms.size()){
            Camera *c=new Camera(data,bind(&App::process_camera_data,
                                           this,placeholders::_1,
                                           placeholders::_2));
            vector<Camera*>::iterator it=cms.begin();
            cms.insert(it+index,c);
            //  cms.insert(cms::iterator+index);
        }
    }
    void del_camera(int index)//delete who ? 1~size
    {
        if(1<=index&&index<=cms.size()){
            delete cms[index-1];
            vector<Camera*>::iterator it=cms.begin();
            cms.erase(it+index-1);
        }
    }
    void mod_camera(int index,JsonPacket pkt)//delete who ? 1~size
    {
        if(1<=index&&index<=cms.size()){
            //cms[index-1].modify_camera(pkt);
        }
    }
    bool process_request(AppReq &req)
    {
        switch (req.request) {
        case AppRequest::SET_CONFIG:
        {
            AppData data=req.data();
            p_cm->set_config(data.data().str());
            private_data=data;
            restart_all();
        }
            break;
        case AppRequest::GET_CONFIG:
            req.ret=private_data.config;


            break;
        case AppRequest::ADD_CAMERA:
            //            CameraData data=req.data();
            //            int index=req.index;
            //add_camera(index,data);
            break;
        case AppRequest::MOD_CAMERA:
            //            JsonPacket data=req.data();
            //            int index=req.index;
            //            modi
            break;
        default:
            break;
        }
    }
    bool process_event(VdEvent &e)
    {
        bool ret=false;
        switch(e.op){
        case App::OP::GET_CONFIG:
        {
            prt(info,"get cmd %d",e.op);
            JsonPacket cfg=p_cm->get_config();//get config
            VdEvent e1(e.op,e.index,e.arg,cfg);
            prt(info,"####$$$$$$$$$$$$$$$$$$###sending----> %s",e1.ret.str().data());
            e=e1;
            ret=true;
            break;
        }
        case App::OP::SET_CONFIG:
        {
            prt(info,"get cmd %d",e.op);
            p_cm->set_config(e.arg.str());//get config
            prt(info,"#######recving----> %s",e.arg.str().data());

            AppData dt(p_cm->get_config());
            this->private_data=AppData(dt);
            restart_all();
            ret=true;
            break;
        }
        default:
            prt(info,"unknow cmd %d",e.op);
            break;
        }
        return ret;
    }

private:
    vector <Session*> *stream_cmd;//clients who connected to our server
    string str_stream;//
    vector <Camera*> cms;
    LocationService lservice;
    ConfigManager *p_cm;
};

#endif // APP_H
