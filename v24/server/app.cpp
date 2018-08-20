#include "app.h"
#include "configmanager.h"
#include "datapacket.h"
App::App(ConfigManager *p_config_manager):str_stream(""),
    VdData(p_config_manager->get_config()),lservice(),p_cm(p_config_manager)
{
    stream_cmd=NULL;
    restart_all();
    static Tcpserver server_cmd(stream_cmd,
                                12345,
                                bind(&App::process_client_cmd,
                                     this,placeholders::_1,
                                     placeholders::_2,
                                     placeholders::_3
                                     )
                                );

}
//deal with clients command
void App::process_client_cmd(Session *clt, char *data, int len)
{
    str_stream.append(string(data,len));
    prt(debug,"string is %s",str_stream.data());
#if 1
    string valid_buf;
    valid_buf.clear();

    while(JsonStr::get_valid_buf(str_stream,valid_buf)) {//Get valid json object, TODO:we only check {} matches, we should check json grammar
        prt(info,"process string %s\n left string %s",valid_buf.data(),str_stream.data());
        RequestPkt event(valid_buf);
        ReplyPkt ret_pkt;
        process_event(event,ret_pkt);
#if 0

        string cmd=data.get_string("cmd");
        if(cmd=="set config"){
            p_cm->set_config(data.get_string("data"));
            restart_all();
        }
        if(cmd=="get config"){
            DataPacket cfg=  p_cm->get_config();
            DataPacket cfg_root;
            cfg_root.set_pkt("config",cfg);
            cfg_root.set_string("cmd",cmd);
            clt->send(cfg_root.data().data(),cfg_root.data().length());
        }
        if(cmd=="delete camera"){
            int index=data.get_int("index");
            del_camera(index);
        }
        if(cmd=="add camera"){
            int index=data.get_int("index");
            DataPacket cam_data=data.get_pkt("data");
            add_camera(index,cam_data);
        }

#else
        string ret=ret_pkt.config.str();
        clt->send(ret.data(),ret.length());

#endif
    }
#endif
}

void App::process_camera_data(Camera *camera, string data)
{
    int ts=camera->get_frame_ts();
    vector<Camera *>::iterator itr;
    int idx=0;
    itr=cms.begin();
    for( idx=0;idx<cms.size();idx++){
        if(*(idx+itr)==camera)
            break;
    }
    if(idx<cms.size()){
        //prt(info,"process camera %d",idx+1);
    }else{
        prt(info,"process invalid camera index");
        return;
    }
    int fd=Socket::UdpCreateSocket(5000);
    AppReslut rst(idx+1,ts,JsonPacket(data));
    //   prt(info,"sending %s",rst.data().str().data());
    if(stream_cmd)
        for(Session *ss:*stream_cmd)
        {
     //       prt(info,"send %s",rst.data().str().data());
            Socket::UdpSendData(fd,ss->ip().data(),12349,rst.data().str().data(),rst.data().str().length());
        }
    close(fd);
}

