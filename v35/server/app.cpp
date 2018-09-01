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
    string valid_buf;
    valid_buf.clear();
    string ret_str;
    bool process_ret;
    while(JsonStr::get_valid_buf(str_stream,valid_buf)) {//Get valid json object, TODO:we only check {} matches, we should check json grammar
        prt(info,"recive object--> %s(%d bytes left)",valid_buf.data(),str_stream.size());
        RequestPkt event(valid_buf);
        ReplyPkt ret_pkt;
        client_tmp_ip=clt->ip();
        process_ret=process_event(event,ret_pkt);
        ret_str=ret_pkt.data().str();
        clt->send(ret_str.data(),ret_str.length());
    }
}

void App::process_camera_data(Camera *camera, string data)
{
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
        prt(info,"process invalid camera index %d, sz %d",idx,cms.size());
        return;
    }
    int fd=Socket::UdpCreateSocket(5000);
    AppOutputData rst(idx+1,JsonPacket(data));
    if(stream_cmd)
        for(Session *ss:*stream_cmd)
        {
            //       prt(info,"send %s",rst.data().str().data());
            Socket::UdpSendData(fd,ss->ip().data(),12349,rst.data().str().data(),rst.data().str().length());
        }
    //    for(DestClient dst:dest_clients){
    //          Socket::UdpSendData(fd,dst.get_ip().data(),12349,rst.data().str().data(),rst.data().str().length());
    //    }
    close(fd);
}

