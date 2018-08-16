
#include <iostream>
#include "tool.h"
#include "jsonpacket.h"
int main()
{

    vector <JsonPacket> b;
    string tmp("{\"a\":1}");
    b.push_back(JsonPacket(tmp));
    prt(info,"%s",b.front().str().data());
    JsonPacket p(b);
    prt(info,"%s",p.str().data());
    vector <JsonPacket> a=p.to_array();
    prt(info,"%s",a.front().str().data());
    return 0;
}
