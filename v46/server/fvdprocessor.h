#ifndef FVDPROCESSOR_H
#define FVDPROCESSOR_H

#include "videoprocessor.h"
#include "jsonpacket.h"
#include "algorithm.h"
//class BaseLineJsonData:public JsonData{
//public:
//    VdPoint BeginPoint;// start point
//    VdPoint EndPoint;// end point
//    int Length; // real length
//    BaseLineJsonData(VdPoint pt1, VdPoint pt2, int len):BeginPoint(pt1),EndPoint(pt2),Length(len)
//    {
//        encode();
//    }
//    BaseLineJsonData(JsonPacket p):JsonData(p)
//    {
//        decode();
//    }
//    BaseLineJsonData()
//    {

//    }
//    void decode()
//    {
//        DECODE_JSONDATA_MEM(BeginPoint);
//        DECODE_JSONDATA_MEM(EndPoint);
//        DECODE_INT_MEM(Length);
//    }
//    void encode()
//    {
//        ENCODE_JSONDATA_MEM(BeginPoint);
//        ENCODE_JSONDATA_MEM(EndPoint);
//        ENCODE_INT_MEM(Length);
//    }
//};
//class LaneDataJsonData:public JsonData{
//public:
//    int LaneNo;// lane name index;
//    vector <VdPoint> FarArea; // far rect
//    vector <VdPoint> NearArea; // near rect
//    vector <VdPoint> LaneArea; // whole rect
//    LaneDataJsonData(JsonPacket p):JsonData(p)
//    {
//        decode();
//    }
//    LaneDataJsonData(int ln, vector <VdPoint> fa,vector <VdPoint> na,vector <VdPoint> la):
//        LaneNo(ln),
//        FarArea(fa),
//        NearArea(na),
//        LaneArea(la)
//    {
//        encode();
//    }
//    void decode()
//    {
//        DECODE_INT_MEM(LaneNo);
//        DECODE_JSONDATA_ARRAY_MEM(FarArea);
//        DECODE_JSONDATA_ARRAY_MEM(NearArea);
//        DECODE_JSONDATA_ARRAY_MEM(LaneArea);

//    }
//    void encode()
//    {
//        ENCODE_INT_MEM(LaneNo);
//        ENCODE_JSONDATA_ARRAY_MEM(FarArea);
//        ENCODE_JSONDATA_ARRAY_MEM(NearArea);
//        ENCODE_JSONDATA_ARRAY_MEM(LaneArea);
//    }
//};
//class FvdProcessorInputData:public JsonData{
//public:
//    vector <VdPoint> BasicCoil;// standard rect
//    BaseLineJsonData BaseLine;// a line can adjust car real length
//    int NearPointDistance;//distance to camera
//    int FarPointDistance;
//    vector <LaneDataJsonData> LineData; // lane info

//    FvdProcessorInputData(JsonPacket pkt):JsonData(pkt)
//    {
//        decode();
//    }
//    FvdProcessorInputData(  vector <VdPoint> bl,BaseLineJsonData be,int i1, int i2, vector <LaneDataJsonData>  ld):
//        BasicCoil(bl), BaseLine(be), NearPointDistance(i1), FarPointDistance(i2), LineData(ld)

//    {
//        encode();
//    }
//    void decode()
//    {
//        DECODE_JSONDATA_ARRAY_MEM(BasicCoil);
//        DECODE_JSONDATA_MEM(BaseLine);
//        DECODE_INT_MEM(NearPointDistance);
//        DECODE_INT_MEM(FarPointDistance);
//        DECODE_JSONDATA_ARRAY_MEM(LineData);
//    }
//    void encode()
//    {
//        ENCODE_JSONDATA_ARRAY_MEM(BasicCoil);
//        ENCODE_JSONDATA_MEM(BaseLine);
//        ENCODE_INT_MEM(NearPointDistance);
//        ENCODE_INT_MEM(FarPointDistance);
//        ENCODE_JSONDATA_ARRAY_MEM(LineData);
//    }
//};
//class LaneOutputJsonData:public JsonData{
//public:
//    int LaneNo; // lane name index
//    int QueueLength;// length of queue
//    VdPoint StartQueuePoint;// queue start point
//    VdPoint EndQueuePoint;// queue end point
//    int LaneVehicleNumber;// lane car count now
//    int VehicleFlow;// flow total
//    int VehicleSpeed;// near rect car's speed
//    int NearActualLength;// near rect real size
//    int FarActualLength;// far rect real size
//    LaneOutputJsonData(JsonPacket pkt):JsonData(pkt)
//    {
//        decode();
//    }
//    LaneOutputJsonData(int lo,int qh,VdPoint st,VdPoint et,int lr,int vw,int vd,int nh,int fh):
//        LaneNo(lo),
//        QueueLength(qh),
//        StartQueuePoint(st),
//        EndQueuePoint(et),
//        LaneVehicleNumber(lr),
//        VehicleFlow(vw),
//        VehicleSpeed(vd),
//        NearActualLength(nh),
//        FarActualLength(fh)
//    {
//        encode();
//    }
//    void decode()
//    {
//        DECODE_INT_MEM(LaneNo);
//        DECODE_INT_MEM(LaneNo);
//        DECODE_JSONDATA_MEM(StartQueuePoint);
//        DECODE_JSONDATA_MEM(EndQueuePoint);
//        DECODE_INT_MEM(LaneNo);
//        DECODE_INT_MEM(LaneNo);
//        DECODE_INT_MEM(LaneNo);
//        DECODE_INT_MEM(LaneNo);
//        DECODE_INT_MEM(LaneNo);


//    }
//    void encode()
//    {
//        ENCODE_INT_MEM(LaneNo);
//        ENCODE_INT_MEM(LaneNo);
//        ENCODE_JSONDATA_MEM(StartQueuePoint);
//        ENCODE_JSONDATA_MEM(EndQueuePoint);
//        ENCODE_INT_MEM(LaneNo);
//        ENCODE_INT_MEM(LaneNo);
//        ENCODE_INT_MEM(LaneNo);
//        ENCODE_INT_MEM(LaneNo);
//        ENCODE_INT_MEM(LaneNo);
//    }
//};
//class DegreeJsonData:public JsonData{
//public:
//    int DegreePointsY;
//    int DegreeValue;
//    DegreeJsonData(JsonPacket p):JsonData(p)
//    {
//        decode();
//    }
//    DegreeJsonData(int a,int b):DegreePointsY(a),DegreeValue(b)
//    {
//        encode();
//    }
//    void decode()
//    {
//        DECODE_INT_MEM(DegreePointsY);
//        DECODE_INT_MEM(DegreeValue);
//    }
//    void encode()
//    {
//        ENCODE_INT_MEM(DegreePointsY);
//        ENCODE_INT_MEM(DegreeValue);
//    }
//};
//class FvdProcessorOutputData:public JsonData{
//public:
//    vector <ObjectRect> FvdDetectedObjects;//all rects of car
//    int CurrentVehicleNumber; // cars number count on screen now;
//    int Visibility;// visiable or not
//    int VideoState;// video state
//    vector <LaneOutputJsonData> LaneOutputData;// output
//    vector <DegreeJsonData> DegreeData; // on  lane points

//    FvdProcessorOutputData(JsonPacket p):JsonData(p)
//    {
//        decode();
//    }
//    FvdProcessorOutputData(vector <ObjectRect> fs, int cr, int vy, int ve,  vector <LaneOutputJsonData> la,  vector <DegreeJsonData> da):
//        FvdDetectedObjects(fs),
//        CurrentVehicleNumber(cr),
//        Visibility(vy),
//        VideoState(ve),
//        LaneOutputData(la),
//        DegreeData(da)
//    {
//        encode();
//    }
//    void decode()
//    {
//        DECODE_JSONDATA_ARRAY_MEM(FvdDetectedObjects);
//        DECODE_INT_MEM(CurrentVehicleNumber);
//        DECODE_INT_MEM(Visibility);
//        DECODE_INT_MEM(VideoState);
//        DECODE_JSONDATA_ARRAY_MEM(LaneOutputData);
//        DECODE_JSONDATA_ARRAY_MEM(DegreeData);
//    }
//    void encode()
//    {
//        ENCODE_JSONDATA_ARRAY_MEM(FvdDetectedObjects);
//        ENCODE_INT_MEM(CurrentVehicleNumber);
//        ENCODE_INT_MEM(Visibility);
//        ENCODE_INT_MEM(VideoState);
//        ENCODE_JSONDATA_ARRAY_MEM(LaneOutputData);
//        ENCODE_JSONDATA_ARRAY_MEM(DegreeData);
//    }
//};
class FvdProcessor : public VideoProcessor
{
    m_args *p_cfg;
public:
    FvdProcessor(JsonPacket pkt)
    {
        int i = 0, j = 0;

        p_cfg = alg_mem_malloc();
        FvdProcessorInputData da(pkt);

        for(i = 0; i < da.BasicCoil.size(); i++)
        {
            p_cfg->pDetectCfg->FvdDetectCfg.BasicCoil[i].x = da.BasicCoil[i].x;
            p_cfg->pDetectCfg->FvdDetectCfg.BasicCoil[i].y = da.BasicCoil[i].y;
        }

        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[0].x = da.BaseLine.BeginPoint.x;
        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[0].y = da.BaseLine.BeginPoint.y;
        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[1].x = da.BaseLine.EndPoint.x;
        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[1].y = da.BaseLine.EndPoint.y;
        p_cfg->pDetectCfg->FvdDetectCfg.base_length = da.BaseLine.Length;

        p_cfg->pDetectCfg->FvdDetectCfg.near_point_length = da.NearPointDistance;
        p_cfg->pDetectCfg->FvdDetectCfg.far_point_length = da.FarPointDistance;

        p_cfg->pDetectCfg->FvdDetectCfg.uLaneTotalNum = da.LineData.size();
        for(i = 0; i < da.LineData.size(); i++)
        {
            p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneNo = da.LineData[i].LaneNo;
            for(j = 0; j < da.LineData[i].FarArea.size(); j++)
            {
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].FarArea[j].x = da.LineData[i].FarArea[j].x;
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].FarArea[j].y = da.LineData[i].FarArea[j].y;
            }
            for(j = 0; j < da.LineData[i].NearArea.size(); j++)
            {
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].NearArea[j].x = da.LineData[i].NearArea[j].x;
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].NearArea[j].y = da.LineData[i].NearArea[j].y;
            }
            for(j = 0; j < da.LineData[i].LaneArea.size(); j++)
            {
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneArea[j].x = da.LineData[i].LaneArea[j].x;
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneArea[j].y = da.LineData[i].LaneArea[j].y;
            }

        }

        FvdArithInit(&p_cfg->pDetectCfg->FvdDetectCfg, p_cfg->pCfgs, p_cfg->pParams);
    }
    ~FvdProcessor()
    {
        alg_mem_free(p_cfg);
    }

    bool process(Mat img_src,JsonPacket &pkt)
    {
        int i = 0;
        int x = 0, y = 0, w = 0, h = 0, c;
        string names;
        IplImage img = IplImage(img_src);
        FvdArithProc(&img, &p_cfg->p_outbuf->FVDoutbuf, p_cfg->pCfgs, p_cfg->pParams);
        vector <ObjectRect> FvdDetectedObjects;
        for( i = 0; i <p_cfg->p_outbuf->FVDoutbuf.uObjNum; i++)
        {
            x = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.x;
            y = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.y;
            w = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.width;
            h = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.height;
            c = p_cfg->p_outbuf->FVDoutbuf.detObj[i].prob;
            char names_tmp[50];
            strcpy(names_tmp, p_cfg->p_outbuf->FVDoutbuf.detObj[i].names);
            names=string(names_tmp);
            ObjectRect  obj = ObjectRect(x, y, w, h, names, c);
            FvdDetectedObjects.push_back(obj);
        }
        int CurrentVehicleNumber = p_cfg->p_outbuf->FVDoutbuf.uObjNum;
        int Visibility = p_cfg->p_outbuf->FVDoutbuf.Visbility;
        int VideoState = p_cfg->p_outbuf->FVDoutbuf.VideoException;

        vector <LaneOutputJsonData> LaneOutputData;
         //   for( i = 0; i < 1; i++)
        for( i = 0;  i <p_cfg->p_outbuf->FVDoutbuf.uLaneNum; i++)
         {
            int laneNo, queLen, vehiNum, flow, speed;
            VdPoint pt1, pt2;
            laneNo = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].LaneNo;
            queLen = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uVehicleQueueLength;
            vehiNum = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uRegionVehicleNumber;
            flow = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uVehicleFlow;
            speed = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uVehicleSpeed;
            pt1.x = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[0].x;
            pt1.y = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[0].y;
            pt2.x = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[1].x;
            pt2.y = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[1].y;
            LaneOutputJsonData detLaneData = LaneOutputJsonData(laneNo, queLen, pt1, pt2, vehiNum, flow, speed
                                                                ,p_cfg->p_outbuf->FVDoutbuf.uActualDetectLength[i],
                                                                p_cfg->p_outbuf->FVDoutbuf.uActualTailLength[i]  );
            LaneOutputData.push_back(detLaneData);
        }
        vector <DegreeJsonData> DegreeData; // on  lane points
        for( i = 0; i < 20; i++)
        {
            DegreeJsonData d(p_cfg->p_outbuf->FVDoutbuf.uDegreePoint[i][0],p_cfg->p_outbuf->FVDoutbuf.uDegreePoint[i][1]);
            DegreeData.push_back(d);

        }
        //        for( i = 0; i < p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum; i++)
        //        {
        //            int len1, len2;
        //            len1 = p_cfg->p_outbuf->FVDoutbuf.uActualDetectLength[i];
        //            len2 = p_cfg->p_outbuf->FVDoutbuf.uActualTailLength[i];
        //            out.NearActualLength.push_back(len1);
        //            out.FarActualLength.push_back(len2);
        //        }


        //        vector <ObjectRect> FvdDetectedObjects;//all rects of car
        //        int CurrentVehicleNumber; // cars number count on screen now;
        //        int Visibility;// visiable or not
        //        int VideoState;// video state
        //     vector <LaneOutputJsonData> LaneOutputData;// output

        FvdProcessorOutputData out(FvdDetectedObjects,CurrentVehicleNumber,Visibility,VideoState,LaneOutputData,DegreeData);
        pkt=out.data();
    }
};

//class FvdProcessor : public VideoProcessor
//{
//    m_args *p_cfg;
//public:
//    FvdProcessor(JsonPacket pkt)
//    {
//        int i = 0, j = 0;
//        //�����ڴ�
//        p_cfg = alg_mem_malloc();
//        PvdProcessorInputData da(pkt);
//        //�궨��Ȧ
//        for(i = 0; i < da.BasicCoil.size(); i++)
//        {
//            p_cfg->pDetectCfg->FvdDetectCfg.BasicCoil[i].x = da.BasicCoil[i].x;
//            p_cfg->pDetectCfg->FvdDetectCfg.BasicCoil[i].y = da.BasicCoil[i].y;
//        }
//        //��׼��
//        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[0].x = da.BaseLine.BeginPoint.x;
//        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[0].y = da.BaseLine.BeginPoint.y;
//        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[1].x = da.BaseLine.EndPoint.x;
//        p_cfg->pDetectCfg->FvdDetectCfg.BaseLine[1].y = da.BaseLine.EndPoint.y;
//        p_cfg->pDetectCfg->FvdDetectCfg.base_length = da.BaseLine.Length;
//        //
//        p_cfg->pDetectCfg->FvdDetectCfg.near_point_length = da.NearPointDistance;
//        p_cfg->pDetectCfg->FvdDetectCfg.far_point_length = da.FarPointDistance;
//        //������Ȧ
//        p_cfg->pDetectCfg->FvdDetectCfg.uLaneTotalNum = da.LineData.size();
//        for(i = 0; i < da.LineData.size(); i++)
//        {
//            p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg.LaneNo = da.LineData.LaneNo;
//            for(j = 0; j < da.LineData.FarArea.size(); j++)
//            {
//                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg.FarArea[j].x = da.LineData.FarArea[j].x;
//                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg.FarArea[j].y = da.LineData.FarArea[j].y;
//            }
//            for(j = 0; j < da.LineData.NearArea.size(); j++)
//            {
//                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg.NearArea[j].x = da.LineData.NearArea[j].x;
//                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg.NearArea[j].y = da.LineData.NearArea[j].y;
//            }
//            for(j = 0; j < da.LineData.LaneArea.size(); j++)
//            {
//                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg.LaneArea[j].x = da.LineData.LaneArea[j].x;
//                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg.LaneArea[j].y = da.LineData.LaneArea[j].y;
//            }

//        }
//        vector <VdPoint> LaneArea;
//        FvdArithInit(&p_cfg->pDetectCfg->FvdDetectCfg, p_cfg->pCfgs, p_cfg->pParams);//��ʼ���㷨����
//    }
//    ~FvdProcessor()
//    {
//        alg_mem_free(p_cfg);
//    }
//    bool process(Mat img_src,JsonPacket &pkt)
//    {
//        int i = 0;
//        int x = 0, y = 0, w = 0, h = 0, c;
//        string names;
//        IplImage* img = &IplImage(img_src);
//        FvdArithProc(img, &p_cfg->p_outbuf.FVDoutbuf, p_cfg->pCfgs, p_cfg->pParams);

//        FvdProcessorOutputData out;
//        //����������
//        vector <ObjectRect> FvdDetectedObjects;
//        for( i = 0; i < p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum; i++)
//        {
//            x = p_cfg->p_outbuf.FVDoutbuf.detObj.box.x;
//            y = p_cfg->p_outbuf.FVDoutbuf.detObj.box.y;
//            w = p_cfg->p_outbuf.FVDoutbuf.detObj.box.width;
//            h = p_cfg->p_outbuf.FVDoutbuf.detObj.box.height;
//            c = p_cfg->p_outbuf.FVDoutbuf.detObj.prob;
//            strcpy(names, p_cfg->p_outbuf.FVDoutbuf.detObj->names);
//            ObjectRect  obj = ObjectRect(x, y, w, h, names, c);
//            out.FvdDetectedObjects.push_back(obj)
//        }
//        out.CurrentVehicleNumber = p_cfg->p_outbuf.FVDoutbuf.uObjNum;//��ǰ����
//        out.Visibility = p_cfg->p_outbuf.FVDoutbuf.Visbility;//�ܼ���
//        out.VideoState = p_cfg->p_outbuf.FVDoutbuf.VideoException;//��Ƶ�쳣

//        //����������Ϣ
//        vector <LaneOutput> LaneOutputData;
//        for( i = 0; i < p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum; i++)
//        {
//            int laneNo, queLen, vehiNum, flow, speed;
//            VdPoint pt1, pt2;
//            laneNo = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].LaneNo;
//            queLen = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].uVehicleQueueLength;
//            vehiNum = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].uRegionVehicleNumber;
//            flow = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].uVehicleFlow;
//            speed = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].uVehicleSpeed;
//            pt1.x = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].QueLine[0].x;
//            pt1.y = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].QueLine[0].y;
//            pt2.x = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].QueLine[1].x;
//            pt2.y = p_cfg->p_outbuf.FVDoutbuf.uEachLaneData[i].QueLine[1].y;
//            LaneOutput detLaneData = LaneOutput(laneNo, queLen, pt1, pt2, vehiNum, flow, speed);
//            out.LaneOutputData.push_back(detLaneData);
//        }
//        for( i = 0; i < 20; i++) //�̶���
//        {
//            out.DegreePointsY.push_back(p_cfg->p_outbuf.FVDoutbuf.uDegreePoint[i][0]);
//            out.DegreeValue.push_back(p_cfg->p_outbuf.FVDoutbuf.uDegreePoint[i][1]);
//        }
//        for( i = 0; i < p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum; i++) //��Ȧʵ�ʳ���
//        {
//            int len1, len2;
//            len1 = p_cfg->p_outbuf.FVDoutbuf.uActualDetectLength[i];
//            len2 = p_cfg->p_outbuf.FVDoutbuf.uActualTailLength[i];
//            out.NearActualLength.push_back(len1);
//            out.FarActualLength.push_back(len2);
//        }
//        pkt=out.data();
//    }
//};

#endif // FVDPROCESSOR_H
