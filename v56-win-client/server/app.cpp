#include "app.h"
#include "configmanager.h"
#include "datapacket.h"
App::App(ConfigManager *p_config_manager):str_stream(""),
    VdData(p_config_manager->get_config()),lservice(),p_cm(p_config_manager),udp_fd(0)
{
}

