#include "app.h"
#include "configmanager.h"
#include "datapacket.h"

App::App(ConfigManager *p_config_manager):str_stream(""),
    VdData(p_config_manager->get_config()),lservice()
{
    p_cm=p_config_manager;
    static Tcpserver server_cmd(stream_cmd,
                            private_data.server_port,
                            bind(&App::process_client_cmd,
                                 this,placeholders::_1,
                                 placeholders::_2,
                                 placeholders::_3
                                 )
                            );
    start_cams();
}
//deal with clients command
void App::process_client_cmd(Session *clt, char *data, int len)
{
    str_stream.append(string(data,len));
    prt(info,"string is %s",str_stream.data());
    //get_config();
#if 1
    string valid_buf;
    valid_buf.clear();

    while(JsonStr::get_valid_buf(str_stream,valid_buf)) {//Get valid json object, TODO:we only check {} matches, we should check json grammar
        prt(info,"process string   %s",valid_buf.data());
        prt(info,"left string   %s",str_stream.data());
        DataPacket data(valid_buf);
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
    }
#endif
}

void App::process_camera_data(Camera *clt, const char *data, int len)
{
    int fd=Socket::UdpCreateSocket(5000);
    Socket::UdpSendData(fd,"192.168.1.216",12346,data,len);
    close(fd);
}

