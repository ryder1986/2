#ifndef MVDPROCESSOR_H
#define MVDPROCESSOR_H

#include "videoprocessor.h"
#include "jsonpacket.h"
#include "algorithm.h"

class MvdProcessor : public VideoProcessor
{
    m_args *p_cfg;
public:
    MvdProcessor(JsonPacket pkt)
    {
        int i = 0, j = 0;

        p_cfg = alg_mem_malloc();
        MvdProcessorInputData da(pkt);
		
		//pvd
		CPoint DetLine[2];
		DetLine[0].x = da.DetectLine[0].x;
		DetLine[0].y = da.DetectLine[0].y;
		DetLine[1].x = da.DetectLine[1].x;
		DetLine[1].y = da.DetectLine[1].y;	

		//fvd
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
		ArithInit(p_cfg->pCfgs, DetLine, &p_cfg->pDetectCfg->FvdDetectCfg, p_cfg->pParams);
    }
    ~MvdProcessor()
    {
        prt(info,"############free start");
        alg_mem_free(p_cfg);
        prt(info,"############free done");
    }

    bool process(Mat img_src,JsonPacket &pkt)
    {
        int i = 0;
        int x = 0, y = 0, w = 0, h = 0, c;
        string names;
        IplImage img = IplImage(img_src);
        ArithProc(&img, p_cfg->p_outbuf, p_cfg->pCfgs, p_cfg->pParams);
		
		//pvd
		int PersonFlow1 = p_cfg->p_outbuf->PVDoutbuf.uPersonSum[0];
		int PersonFlow2 = p_cfg->p_outbuf->PVDoutbuf.uPersonSum[1];
		int CurrentPersionCount = p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum;
		//fvd
        vector <ObjectRect> MvdDetectedObjects;
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
            MvdDetectedObjects.push_back(obj);
        }
        int CurrentVehicleNumber = p_cfg->p_outbuf->FVDoutbuf.uObjNum - p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum;
        int Visibility = p_cfg->p_outbuf->FVDoutbuf.Visbility;
        int VideoState = p_cfg->p_outbuf->FVDoutbuf.VideoException;

        vector <LaneOutputJsonData> LaneOutputData;
        for( i = 0;  i <p_cfg->p_outbuf->FVDoutbuf.uLaneNum; i++)
         {
            int laneNo, queLen, vehiNum, flow, speed;
            laneNo = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].LaneNo;
            queLen = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uVehicleQueueLength;
            vehiNum = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uRegionVehicleNumber;
            flow = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uVehicleFlow;
            speed = p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].uVehicleSpeed;
            VdPoint pt1( p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[0].x,
                    p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[0].y);
            VdPoint pt2(p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[1].x,
                p_cfg->p_outbuf->FVDoutbuf.uEachLaneData[i].QueLine[1].y );

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

        MvdProcessorOutputData out(MvdDetectedObjects,
                                   CurrentVehicleNumber,
                                   Visibility,
                                   VideoState,
                                   LaneOutputData,
                                   DegreeData,
                                   PersonFlow1,
                                   PersonFlow2,
                                   CurrentPersionCount);
        pkt=out.data();
    }
};


#endif // MVDPROCESSOR_H
