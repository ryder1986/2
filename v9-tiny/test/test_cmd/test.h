#ifndef TEST_H
#define TEST_H

#include "socket.h"
class Test
{
    TcpClient clt;
public:
    Test():clt("192.168.1.216",12345)
    {

    }
};

#endif // TEST_H
