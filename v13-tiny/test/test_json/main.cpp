#include <iostream>
#include <tool.h>
#include "jsonpacket.h"
using namespace std;
class PointData:public JsonData{

public:
    PointData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    PointData( int x1,int y1):x(x1),y(y1)
    {
        encode();
    }
    PointData()
    {
    }
    void encode()
    {
        ENCODE_INT_MEM(x);
        ENCODE_INT_MEM(y);
    }
    void decode()
    {
        DECODE_INT_MEM(x);
        DECODE_INT_MEM(y);
    }
public:
    int x;
    int y;
};
class TestData:public JsonData{
public:
    TestData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }

    TestData(string s, vector<PointData> pnt):str(s),points(pnt)
    {
        encode();
    }
    TestData()
    {

    }

    void encode()
    {
        ENCODE_STRING_MEM(str);
        ENCODE_OBJ_ARRAY_MEM(points);
    }
    void decode()
    {
        DECODE_STRING_MEM(str);
        DECODE_OBJ_ARRAY_MEM(points);
    }
public:
    string str;
    vector<PointData> points;
};

int main()
{
       string json_str("\{\"str\"\:\"name\"\,\"point\"\:\{\"x\"\:5\,\"y\"\:6\}\}");


    JsonPacket test_pkt(json_str);
    cout <<test_pkt.data().data()<< endl;
    /*    string str("\{\"root\"\:1}");
    string ar("\[{\"a\"\:1}\,\{\"b\"\:2\}\]");
    JsonPacket array(ar);
    JsonPacket jp(str);
    JsonPacket jp1;
    jp1.add("ss",jp);
    jp1.add("aa",array);
    prt(info,"%s",jp1.data().data())*/;

    //   string json_str("\{\"str\"\:\"name\"\,\"point\"\:\{\"x\"\:5\,\"y\"\:6\}\}");
    //JsonPacket pkt(json_str);
    //  /     prt(info,"%s",json_str.data());


    //    TestData d=pkt;
    //   prt(info,"%d,%d",d.point.x,d.point.y);




    PointData p2(13,15);
    PointData p1(17,18);
    vector<PointData>  ps;
    ps.push_back(p1);
    ps.push_back(p2);
     string ss("test");

    TestData d(ss,ps);
//    for(auto tmp: d.points){
//           prt(info,"%s",tmp.data().data().data());
//    }

    prt(info,"%s",d.data().data().data());


    cout << "Bye  World!" << endl;

    while(1);
    return 0;
}

