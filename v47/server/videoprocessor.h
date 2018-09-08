#ifndef VIDEOPROCESSOR_H
#define VIDEOPROCESSOR_H


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>


#include "tool.h"
#include "datapacket.h"
using namespace std;
using namespace cv;

namespace VideoProcessorNS{
typedef struct args{
    double scale_ratio;
    int scan_step;
    Rect area;
    int no;
    string ratio;

}arg_t;
}
using namespace VideoProcessorNS;
class VideoProcessor
{

protected:
    //  arg_t arg;
public:
    string alg_rst;
#if 1
    VideoProcessor()
    {

    }
#else
    VideoProcessor(DataPacket pkt):JsonDataDealer(pkt)
    {

    }
#endif
    int get_id()
    {
        return channel_id;
    }
    void set_config(DataPacket pkt)
    {
        //        private_data.scale_ratio=string2f(pkt.get_string("ratio"));
        //        private_data.scan_step=pkt.get_int("step");
        //        vector <DataPacket> area=pkt.get_array_packet("detect_area");
        //        private_data.area=area_2_rect(area);
        //        private_data.area.x=0;
        //        private_data.area.y=0;
        //        private_data.area.width=640;
        //        private_data.area.height=480;
    }



    DataPacket get_config()
    {
        DataPacket pkt;
        //        pkt.set_int("step",private_data.scan_step);
        //        pkt.set_string("ratio",f2string(private_data.scale_ratio));
        return pkt;
    }
    //    virtual  bool process( Mat img)
    //    {
    //        return false;
    //    }
    //    virtual  bool process( int t)
    //    {
    //        return false;
    //    }
    //    virtual bool process(Mat img_src,vector<Rect> &rects)
    //    {

    //    }
    virtual bool process(Mat img_src,JsonPacket &pkt)=0;
    //    {
    //        prt(info,"actual processor needed");
    //    }
    //    virtual bool process(Mat img_src,vector<Rect> &rects,Rect detect_area)
    //    {

    //        return false;
    //    }

    virtual  string get_rst()
    {
        string ba;
        return ba ;
    }

    virtual void init()
    {
    }

    //    DataPacket get_config()
    //    {
    //        DataPacket ret;
    //        encode(ret);
    //        return ret;
    //    }
    Rect area_2_rect(vector<DataPacket> area)
    {
        int x_min=10000;
        int y_min=10000;
        int x_max=0;
        int y_max=0;
        for(DataPacket pkt: area) {
            int x=pkt.get_int("x");
            int y=pkt.get_int("y");
            //              int x= v.toObject()["x"].toInt();
            //            int y= v.toObject()["y"].toInt();
            if(x<x_min)
                x_min=x;
            if(x>x_max)
                x_max=x;
            if(y<y_min)
                y_min=y;
            if(y>y_max)
                y_max=y;
        }
        return Rect(x_min,y_min,x_max-x_min,y_max-y_min);
    }

protected:
    int channel_id;
private:

};




class DummyProcessorOutputData:public JsonData{

public:
    vector<VdPoint> Points;
    int Radii;
    DummyProcessorOutputData()
    {
    }
    DummyProcessorOutputData(JsonPacket str):JsonData(str)
    {
        decode();
    }
    DummyProcessorOutputData(vector<VdPoint> o,int r):Radii(r)
    {
        Points.assign(o.begin(),o.end());
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(Points);
        DECODE_INT_MEM(Radii);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(Points);
        ENCODE_INT_MEM(Radii);
    }
};
class DummyProcessorInputData:public JsonData{

public:
    bool Horizon;
    bool Vertical;
    int Radii;
    DummyProcessorInputData(bool h,bool v,int r):Horizon(h),Vertical(v),Radii(r)
    {
        encode();
    }
    DummyProcessorInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    DummyProcessorInputData()
    {

    }
    void decode()
    {
        DECODE_BOOL_MEM(Horizon);
        DECODE_BOOL_MEM(Vertical);
        DECODE_INT_MEM(Radii);
    }
    void encode()
    {
        ENCODE_BOOL_MEM(Horizon);
        ENCODE_BOOL_MEM(Vertical);
        ENCODE_INT_MEM(Radii);
    }
};


class C4ProcessorOutputData:public JsonData{

public:
    vector <VdRect> Rects;
    C4ProcessorOutputData()
    {
    }
    C4ProcessorOutputData(JsonPacket str):JsonData(str)
    {
        decode();
    }
    C4ProcessorOutputData(vector <VdRect> o):Rects(o)
    {
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(Rects);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(Rects);
    }
};
class C4ProcessorInputData:public JsonData{

public:
    double ratio;
    int scan_step;
    C4ProcessorInputData()
    {
    }
    C4ProcessorInputData(JsonPacket str):JsonData(str)
    {
        decode();
    }
    C4ProcessorInputData(int st,double ra):scan_step(st),ratio(ra)
    {
        encode();
    }
    void decode()
    {
        DECODE_INT_MEM(scan_step);
        DECODE_DOUBLE_MEM(ratio);
    }
    void encode()
    {
        ENCODE_INT_MEM(scan_step);
        ENCODE_DOUBLE_MEM(ratio);
    }
};

class PvdProcessorInputData:public JsonData{
public:
    vector <VdPoint> DetectLine;
    PvdProcessorInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    PvdProcessorInputData(VdPoint p1,VdPoint p2)
    {
        DetectLine.push_back(p1);
        DetectLine.push_back(p2);
        encode();
    }
    PvdProcessorInputData()
    {

    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(DetectLine);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(DetectLine);
    }
};

class PvdProcessorOutputData:public JsonData{
public:
    vector <ObjectRect> PvdDetectedObjects;
    int PersonFlow1;
    int PersonFlow2;
    int CurrentPersionCount;
    PvdProcessorOutputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    PvdProcessorOutputData(    vector <ObjectRect> objs,
                               int p1,
                               int p2,
                               int cnt)
    {
        PvdDetectedObjects.assign(objs.begin(),objs.end());
        PersonFlow1=p1;
        PersonFlow2=p2;;
        CurrentPersionCount=cnt;
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(PvdDetectedObjects);
        DECODE_INT_MEM(PersonFlow1);
        DECODE_INT_MEM(PersonFlow2);
        DECODE_INT_MEM(CurrentPersionCount);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(PvdDetectedObjects);
        ENCODE_INT_MEM(PersonFlow1);
        ENCODE_INT_MEM(PersonFlow2);
        ENCODE_INT_MEM(CurrentPersionCount);
    }
};


class BaseLineJsonData:public JsonData{
public:
    VdPoint BeginPoint;// start point
    VdPoint EndPoint;// end point
    int Length; // real length
    BaseLineJsonData(VdPoint pt1, VdPoint pt2, int len):BeginPoint(pt1),EndPoint(pt2),Length(len)
    {
        encode();
    }
    BaseLineJsonData(JsonPacket p):JsonData(p)
    {
        decode();
    }
    BaseLineJsonData()
    {

    }
    void decode()
    {
        DECODE_JSONDATA_MEM(BeginPoint);
        DECODE_JSONDATA_MEM(EndPoint);
        DECODE_INT_MEM(Length);
    }
    void encode()
    {
        ENCODE_JSONDATA_MEM(BeginPoint);
        ENCODE_JSONDATA_MEM(EndPoint);
        ENCODE_INT_MEM(Length);
    }
};
class LaneDataJsonData:public JsonData{
public:
    int LaneNo;// lane name index;
    vector <VdPoint> FarArea; // far rect
    vector <VdPoint> NearArea; // near rect
    vector <VdPoint> LaneArea; // whole rect
    LaneDataJsonData(JsonPacket p):JsonData(p)
    {
        decode();
    }
    LaneDataJsonData(int ln, vector <VdPoint> fa,vector <VdPoint> na,vector <VdPoint> la):
        LaneNo(ln),
        FarArea(fa),
        NearArea(na),
        LaneArea(la)
    {
        encode();
    }
    void decode()
    {
        DECODE_INT_MEM(LaneNo);
        DECODE_JSONDATA_ARRAY_MEM(FarArea);
        DECODE_JSONDATA_ARRAY_MEM(NearArea);
        DECODE_JSONDATA_ARRAY_MEM(LaneArea);

    }
    void encode()
    {
        ENCODE_INT_MEM(LaneNo);
        ENCODE_JSONDATA_ARRAY_MEM(FarArea);
        ENCODE_JSONDATA_ARRAY_MEM(NearArea);
        ENCODE_JSONDATA_ARRAY_MEM(LaneArea);
    }
};
class FvdProcessorInputData:public JsonData{
public:
    vector <VdPoint> BasicCoil;// standard rect
    BaseLineJsonData BaseLine;// a line can adjust car real length
    int NearPointDistance;//distance to camera
    int FarPointDistance;
    vector <LaneDataJsonData> LineData; // lane info
FvdProcessorInputData(){}
    FvdProcessorInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    FvdProcessorInputData(  vector <VdPoint> bl,BaseLineJsonData be,int i1, int i2, vector <LaneDataJsonData>  ld):
        BasicCoil(bl), BaseLine(be), NearPointDistance(i1), FarPointDistance(i2), LineData(ld)

    {
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(BasicCoil);
        DECODE_JSONDATA_MEM(BaseLine);
        DECODE_INT_MEM(NearPointDistance);
        DECODE_INT_MEM(FarPointDistance);
        DECODE_JSONDATA_ARRAY_MEM(LineData);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(BasicCoil);
        ENCODE_JSONDATA_MEM(BaseLine);
        ENCODE_INT_MEM(NearPointDistance);
        ENCODE_INT_MEM(FarPointDistance);
        ENCODE_JSONDATA_ARRAY_MEM(LineData);
    }
};
class LaneOutputJsonData:public JsonData{
public:
    int LaneNo; // lane name index
    int QueueLength;// length of queue
    VdPoint StartQueuePoint;// queue start point
    VdPoint EndQueuePoint;// queue end point
    int LaneVehicleNumber;// lane car count now
    int VehicleFlow;// flow total
    int VehicleSpeed;// near rect car's speed
    int NearActualLength;// near rect real size
    int FarActualLength;// far rect real size
    LaneOutputJsonData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    LaneOutputJsonData(int lo,int qh,VdPoint st,VdPoint et,int lr,int vw,int vd,int nh,int fh):
        LaneNo(lo),
        QueueLength(qh),
        StartQueuePoint(st),
        EndQueuePoint(et),
        LaneVehicleNumber(lr),
        VehicleFlow(vw),
        VehicleSpeed(vd),
        NearActualLength(nh),
        FarActualLength(fh)
    {
        encode();
    }
    void decode()
    {
        DECODE_INT_MEM(LaneNo);
        DECODE_INT_MEM(LaneNo);
        DECODE_JSONDATA_MEM(StartQueuePoint);
        DECODE_JSONDATA_MEM(EndQueuePoint);
        DECODE_INT_MEM(LaneNo);
        DECODE_INT_MEM(LaneNo);
        DECODE_INT_MEM(LaneNo);
        DECODE_INT_MEM(LaneNo);
        DECODE_INT_MEM(LaneNo);


    }
    void encode()
    {
        ENCODE_INT_MEM(LaneNo);
        ENCODE_INT_MEM(LaneNo);
        ENCODE_JSONDATA_MEM(StartQueuePoint);
        ENCODE_JSONDATA_MEM(EndQueuePoint);
        ENCODE_INT_MEM(LaneNo);
        ENCODE_INT_MEM(LaneNo);
        ENCODE_INT_MEM(LaneNo);
        ENCODE_INT_MEM(LaneNo);
        ENCODE_INT_MEM(LaneNo);
    }
};
class DegreeJsonData:public JsonData{
public:
    int DegreePointsY;
    int DegreeValue;
    DegreeJsonData(JsonPacket p):JsonData(p)
    {
        decode();
    }
    DegreeJsonData(int a,int b):DegreePointsY(a),DegreeValue(b)
    {
        encode();
    }
    void decode()
    {
        DECODE_INT_MEM(DegreePointsY);
        DECODE_INT_MEM(DegreeValue);
    }
    void encode()
    {
        ENCODE_INT_MEM(DegreePointsY);
        ENCODE_INT_MEM(DegreeValue);
    }
};
class FvdProcessorOutputData:public JsonData{
public:
    vector <ObjectRect> FvdDetectedObjects;//all rects of car
    int CurrentVehicleNumber; // cars number count on screen now;
    int Visibility;// visiable or not
    int VideoState;// video state
    vector <LaneOutputJsonData> LaneOutputData;// output
    vector <DegreeJsonData> DegreeData; // on  lane points

    FvdProcessorOutputData(JsonPacket p):JsonData(p)
    {
        decode();
    }
    FvdProcessorOutputData(vector <ObjectRect> fs, int cr, int vy, int ve,  vector <LaneOutputJsonData> la,  vector <DegreeJsonData> da):
        FvdDetectedObjects(fs),
        CurrentVehicleNumber(cr),
        Visibility(vy),
        VideoState(ve),
        LaneOutputData(la),
        DegreeData(da)
    {
        encode();
    }
    void decode()
    {
        DECODE_JSONDATA_ARRAY_MEM(FvdDetectedObjects);
        DECODE_INT_MEM(CurrentVehicleNumber);
        DECODE_INT_MEM(Visibility);
        DECODE_INT_MEM(VideoState);
        DECODE_JSONDATA_ARRAY_MEM(LaneOutputData);
        DECODE_JSONDATA_ARRAY_MEM(DegreeData);
    }
    void encode()
    {
        ENCODE_JSONDATA_ARRAY_MEM(FvdDetectedObjects);
        ENCODE_INT_MEM(CurrentVehicleNumber);
        ENCODE_INT_MEM(Visibility);
        ENCODE_INT_MEM(VideoState);
        ENCODE_JSONDATA_ARRAY_MEM(LaneOutputData);
        ENCODE_JSONDATA_ARRAY_MEM(DegreeData);
    }
};
#endif // VIDEOPROCESSOR_H
