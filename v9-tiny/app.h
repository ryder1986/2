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
    AppData()
    {

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
class AppReq:public JsonData{
public:
    int request;
    int index;
    DataPacket pri;
    AppReq(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    AppReq()
    {

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
class App:public VdData<AppData>
{
public:
    App(ConfigManager *p);
    void start()
    {
    }
private:
    void process_client_cmd(Session *clt,char *data,int len);
    void client_data_request(Session *clt, char *data, int len);
    void process_camera_data(Camera *clt,const char *data,int len);
    void restart_all()
    {
        stop_cams();
        start_cams();
    }
    void start_cams()
    {
        for(CameraData p:private_data.cameras){
            cms.push_back(new Camera(p,bind(&App::process_camera_data,
                                            this,placeholders::_1,
                                            placeholders::_2,
                                            placeholders::_3)));
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
                                           placeholders::_2,
                                           placeholders::_3));
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
    bool process_request(DataPacket req)
    {

    }

private:
    vector <Session*> *stream_cmd;//clients who connected to our server
    string str_stream;//
    vector <Camera*> cms;
    LocationService lservice;
    ConfigManager *p_cm;
};

#endif // APP_H
