#ifndef APP_H
#define APP_H

#include "server.h"
#include "tool.h"
#include "camera.h"
#include "configmanager.h"
class AppInputData:public JsonData{
public:
    vector <JsonPacket> CameraData;
    string DeviceName;

    AppInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    AppInputData()
    {

    }
    void modify_camera(JsonPacket d,int index)
    {
        if(index>0&&index<=CameraData.size()){
            prt(info,"camera %d, data change to =##########==>%s",index,d.str().data());
            CameraData[index-1]=d;
        }else{
            prt(info," cams size  %d,unchange with index %d", CameraData.size(),index);
        }
        encode();
    }

    void insert_camera(JsonPacket d,int index)
    {
        if(index>=0&&index<=CameraData.size()){
            prt(info," cams  size  %d", CameraData.size());
            vector <JsonPacket>::iterator it=CameraData.begin();
            CameraData.insert(it+index,d);
            prt(info," cams new size  %d", CameraData.size());
        }else{
            prt(info," cams size  %d,unchange with index %d", CameraData.size(),index);
        }
        encode();
    }

    void delete_camera(int index)
    {
        if(index>0&&index<=CameraData.size()){
            prt(info," cams  size  %d", CameraData.size());
            vector <JsonPacket>::iterator it=CameraData.begin();
            CameraData.erase(it+index-1);
            prt(info," cams new size  %d", CameraData.size());
        }else{
            prt(info," cams size  %d,unchange with index %d", CameraData.size(),index);
        }
        encode();
    }

    void decode()
    {
        DECODE_STRING_MEM(DeviceName);
        DECODE_OBJ_ARRAY_MEM(CameraData);
    }

    void encode()
    {
        ENCODE_STRING_MEM(DeviceName);
        ENCODE_OBJ_ARRAY_MEM(CameraData);
    }
};
class AppOutputData:public JsonData{
public:
    int CameraIndex;
    JsonPacket CameraOutput;
    AppOutputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    AppOutputData(int index,JsonPacket camout):CameraIndex(index),CameraOutput(camout)
    {
        encode();
    }

    void decode()
    {
        DECODE_INT_MEM(CameraIndex);
        DECODE_OBJ_MEM(CameraOutput);
    }
    void encode()
    {
        ENCODE_INT_MEM(CameraIndex);
        ENCODE_OBJ_MEM(CameraOutput);
    }
};
class DestClient{
public:
    DestClient(string i):ip(i)
    {

    }
    string get_ip()
    {
        return ip;
    }

private:
    string ip;
};

class App:public VdData<AppInputData>
{
public:
    enum Operation{
        GET_CONFIG=1,
        SET_CONFIG,
        INSERT_CAMERA,
        MODIFY_CAMERA,
        DELETE_CAMERA,
        OPEN_CAMERA_DATA,
        CLOSE_CAMERA_DATA,
        HEART_PKT,
        REBOOT
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
    }

    void start_cams()
    {
        for(JsonPacket p:private_data.CameraData){
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
            private_data.insert_camera(data,index);
        }
    }

    bool del_camera(int index)//delete who ? 1~size
    {
        if(1<=index&&index<=cms.size()){
            delete cms[index-1];
            vector<Camera*>::iterator it=cms.begin();
            cms.erase(it+index-1);
            private_data.delete_camera(index);
            return true;
        }
        return false;
    }

    bool mod_camera(int index,JsonPacket pkt)//delete who ? 1~size
    {
        bool ret=false;
        if(1<=index&&index<=cms.size()){
            vector<Camera*>::iterator it=cms.begin();
            Camera *c=cms[index-1];
            if(c->modify(pkt)){
                private_data.modify_camera(c->get_data().data(),index);
                ret=true;
            }
        }
        return ret;
    }

    bool process_event(RequestPkt e,ReplyPkt &r)
    {
        bool ret=false;
        prt(info,"get cmd %d",e.Operation);
        switch(e.Operation){
        case App::Operation::GET_CONFIG:
        {
            JsonPacket cfg=p_cm->get_config();//get config
            //prt(info,"cfg %s",cfg.str().data());
            //printf("$$$$$ %s $$$$$\n",cfg.str().data());
            ReplyPkt rp(true,App::Operation::GET_CONFIG,cfg);
            r=rp;
            //prt(info,"reply %s (%d)",r.data().str().data(),r.data().str().size());
            ret=true;
            break;
        }
        case App::Operation::SET_CONFIG:
        {
            p_cm->set_config(e.Argument.str());//get config
            prt(info,"set config with string:\n %s",e.Argument.str().data());
            AppInputData dt(p_cm->get_config());
            private_data=AppInputData(dt);
            restart_all();
            ret=true;
            break;
        }
        case App::Operation::INSERT_CAMERA:
        {
            add_camera(e.Index,e.Argument);
            p_cm->set_config(private_data.data().str());//get config
            ret=true;
            break;
        }
        case App::Operation::MODIFY_CAMERA:
        {
            //printf("#########before  %s",private_data.data().str().data());

            if(mod_camera(e.Index,e.Argument)){
                //printf("#########after  %s",private_data.data().str().data());
                p_cm->set_config(private_data.data().str());
                ret=true;
                ReplyPkt p(true,App::Operation::MODIFY_CAMERA,JsonPacket());
                r=p;
            }
            break;
        }
        case App::Operation::DELETE_CAMERA:
        {
            del_camera(e.Index);
            p_cm->set_config(private_data.data().str());
            ret=true;
            break;
        }
        case App::Operation::OPEN_CAMERA_DATA:
        {
            bool exist=false;
            for(DestClient dst:dest_clients ){
                if(dst.get_ip()==client_tmp_ip)
                    exist=true;
            }
            if(!exist)
                dest_clients.push_back(DestClient(client_tmp_ip));
            ret=true;
            break;
        }
        case App::Operation::CLOSE_CAMERA_DATA:
        {
            bool exist=false;
            vector<DestClient>::iterator  bg= dest_clients.begin();
            for(int i=0;i<dest_clients.size();i++ ){
                DestClient dst=dest_clients[i];
                if(dst.get_ip()==client_tmp_ip)
                    dest_clients.erase(bg+i);
            }
            ret=true;
            break;
        }
        case App::Operation::HEART_PKT:
        {
            ret=true;
            break;
        }
        case App::Operation::REBOOT:
        {
            ret=true;
            break;
        }
        default:
            prt(info,"unknow cmd %d",e.Operation);
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
    vector <DestClient > dest_clients;
    string client_tmp_ip;
};

#endif // APP_H
