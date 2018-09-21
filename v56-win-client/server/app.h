#ifndef APP_H
#define APP_H

//#include "server.h"
#include "tool.h"
#include "camera.h"
#include "configmanager.h"
#include "app_data.h"

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
    //define operation for request pkt
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
    ~App(){}


};

#endif // APP_H
