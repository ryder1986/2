#include <iostream>
#include "tool.h"
#include "configmanager.h"
#include "app.h"
using namespace std;
//LogFile Tool1::log_file1;//open this when need log
int main()
{
    cout<<"Video Detection ";
    prt(info,"Start!!!");
    ConfigManager config;
    App app(&config);
    app.start();
    while(1)
    {
        this_thread::sleep_for(chrono::milliseconds(1));
    }
    return 0;
}

