﻿#ifndef APP_H
#define APP_H

#include "server.h"
#include "tool.h"
#include "camera.h"
#include "configmanager.h"
class AppInputData:public TitledJsonData{
public:
    vector <JsonPacket> CameraData;
    string DeviceName;

    AppInputData(JsonPacket pkt):TitledJsonData(pkt,"DeviceConfig")
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
        DECODE_PKT_ARRAY_MEM(CameraData);
    }

    void encode()
    {
        ENCODE_STRING_MEM(DeviceName);
        ENCODE_PKT_ARRAY_MEM(CameraData);
    }
};
//class AppInputData:public JsonData{

//public:
//    DeviceConfigT DeviceConfig;
//    AppInputData()
//    {

//    }
//    AppInputData(JsonPacket pkt):JsonData(pkt)
//    {
//        decode();
//    }
//    void encode()
//    {
//        ENCODE_JSONDATA_MEM(DeviceConfig);
//    }
//    void decode()
//    {
//        DECODE_JSONDATA_MEM(DeviceConfig);
//    }
//};
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
        DECODE_PKT_MEM(CameraOutput);
    }
    void encode()
    {
        ENCODE_INT_MEM(CameraIndex);
        ENCODE_PKT_MEM(CameraOutput);
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
    ~App();

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

    bool add_camera(int index,JsonPacket data)//after who ?  0~size
    {
        bool ret=false;
        if(0<=index&&index<=cms.size()){
            Camera *c=new Camera(data,bind(&App::process_camera_data,
                                           this,placeholders::_1,
                                           placeholders::_2));
            vector<Camera*>::iterator it=cms.begin();
            cms.insert(it+index,c);
            private_data.insert_camera(data,index);
            ret=true;
        }
        return ret;
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
        prt(info,"handle cmd type %d",e.Operation);
        switch(e.Operation){
        case App::Operation::GET_CONFIG:
        {
            JsonPacket cfg=p_cm->get_config();//get config
            ReplyPkt rp(true,App::Operation::GET_CONFIG,cfg);
            r=rp;
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
            ReplyPkt p(ret,App::Operation::SET_CONFIG,JsonPacket());
            r=p;
            break;
        }
        case App::Operation::INSERT_CAMERA:
        {
            if( add_camera(e.Index,e.Argument)){
                p_cm->set_config(private_data.data().str());//get config
                ret=true;
            }
            ReplyPkt p(ret,App::Operation::MODIFY_CAMERA,JsonPacket());
            r=p;
            break;
        }
        case App::Operation::MODIFY_CAMERA:
        {
            if(mod_camera(e.Index,e.Argument)){
                p_cm->set_config(private_data.data().str());
                ret=true;
            }
            ReplyPkt p(ret,App::Operation::MODIFY_CAMERA,JsonPacket());
            r=p;
            break;
        }
        case App::Operation::DELETE_CAMERA:
        {
            ret=false;
            if(del_camera(e.Index)){
                p_cm->set_config(private_data.data().str());
                ret=true;
            }
            ReplyPkt p(ret,App::Operation::DELETE_CAMERA,JsonPacket());
            r=p;
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
            ReplyPkt p(ret,App::Operation::OPEN_CAMERA_DATA,JsonPacket());
            r=p;
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
            ReplyPkt p(ret,App::Operation::CLOSE_CAMERA_DATA,JsonPacket());
            r=p;
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
    int udp_fd;
};

#endif // APP_H
