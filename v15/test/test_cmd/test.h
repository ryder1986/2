#ifndef TEST_H
#define TEST_H

#include "socket.h"
#include "server.h"
#include "app.h"
class TcpClient{
public:
    TcpClient(string ip,int port):quit(false),client_ip(ip),
        client_port(port)
    {
        // skt=fd;
        int ul = 0;
        skt=Socket::CreateTcpClientSock(0,10000);
        int ret=Socket::ConnectTcpClient(skt,ip.data(),port);
        if(ret>0){
            cout<<"connect ok"<<endl;
        }else{
            cout<<"connection fail"<<endl;
        }
        ioctl(skt, FIONBIO, &ul);
        cout<<"new connection"<<endl;
        auto func_recv=bind(&TcpClient::recv,this);
        auto func_test_send=bind(&TcpClient::test_send,this);

        trd=new thread([func_recv](){func_recv();});
        trd_test_send=new thread([func_test_send](){func_test_send();});
    }
    ~TcpClient()
    {
        cout<<"session deleteing "<<ip()<<endl;
        quit=true;
        trd->join();
        delete trd;

    }
    int test_send()
    {


        while(1){
            char buf[200]={"\{op\:\"get_config\"\}"};
            //   prt(info,"sending -> %s\n",buf);
            sprintf(buf,"\{\"op\"\:%d\}",App::OP::GET_CONFIG);
            Socket::SendDataByTcp(skt,buf,strlen(buf));
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }

    int send(const char *buf,int len)
    {
        int ret= Socket::SendDataByTcp(skt,buf,len);
        if(ret){
            cout<<"send  "<<ret<<" bytes"<<endl;
        }else{
            cout<<"send  fail"<<endl;
        }
    }
    int recv()
    {
        while(!quit){
            int ret=Socket::RecvDataByTcp1(skt,buf,BUF_SIZE);
            if(ret){
                cout<<"read  "<<ret<<" bytes"<<endl;
                process_data(this,buf,ret);
            }else{
                cout<<"ret  "<<ret<<endl;
                // break;
                cout<<"socket maybe closed,retry read after 1sec"  <<endl;
                this_thread::sleep_for(chrono::seconds(1));
            }

        }
        end_this(this);
    }
    string ip()
    {
        return client_ip;
    }
    int port()
    {
        return client_port;
    }
private:
    int skt;
    bool quit;
    char buf[BUF_SIZE];
    std::thread *trd;
    std::thread *trd_test_send;
    string client_ip;
    int client_port;
public:
    function <void(TcpClient *)> end_this=[](TcpClient *){ cout<<"we  can quit now"<<endl;};
    function <void(TcpClient *,char *data,int len)> process_data=[](TcpClient *,char *data,int len){ cout<<"process data"<<endl;};

};


class Test
{
    TcpClient clt;
public:
    Test():clt("192.168.1.216",12345)
    {

    }
};

#endif // TEST_H
