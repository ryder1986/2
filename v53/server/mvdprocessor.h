#ifndef MVDPROCESSOR_H
#define MVDPROCESSOR_H

#include "videoprocessor.h"
#include "jsonpacket.h"
#include "algorithm.h"
#define  SAVE_VIDEO 
#ifdef SAVE_VIDEO
Mat imgSave;
#endif
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

        p_cfg->pDetectCfg->FvdDetectCfg.uLaneTotalNum = da.LaneData.size();
        for(i = 0; i < da.LaneData.size(); i++)
        {
            p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneNo = da.LaneData[i].LaneNo;
            for(j = 0; j < da.LaneData[i].FarArea.size(); j++)
            {
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].FarArea[j].x = da.LaneData[i].FarArea[j].x;
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].FarArea[j].y = da.LaneData[i].FarArea[j].y;
            }
            for(j = 0; j < da.LaneData[i].NearArea.size(); j++)
            {
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].NearArea[j].x = da.LaneData[i].NearArea[j].x;
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].NearArea[j].y = da.LaneData[i].NearArea[j].y;
            }
            for(j = 0; j < da.LaneData[i].LaneArea.size(); j++)
            {
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneArea[j].x = da.LaneData[i].LaneArea[j].x;
                p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneArea[j].y = da.LaneData[i].LaneArea[j].y;
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

    virtual bool modify_processor(JsonPacket p)
    {
        int i,j;
        MvdProcessorInputData da(p);
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

		p_cfg->pDetectCfg->FvdDetectCfg.uLaneTotalNum = da.LaneData.size();
		for(i = 0; i < da.LaneData.size(); i++)
		{
			p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneNo = da.LaneData[i].LaneNo;
			for(j = 0; j < da.LaneData[i].FarArea.size(); j++)
			{
				p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].FarArea[j].x = da.LaneData[i].FarArea[j].x;
				p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].FarArea[j].y = da.LaneData[i].FarArea[j].y;
			}
			for(j = 0; j < da.LaneData[i].NearArea.size(); j++)
			{
				p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].NearArea[j].x = da.LaneData[i].NearArea[j].x;
				p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].NearArea[j].y = da.LaneData[i].NearArea[j].y;
			}
			for(j = 0; j < da.LaneData[i].LaneArea.size(); j++)
			{
				p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneArea[j].x = da.LaneData[i].LaneArea[j].x;
				p_cfg->pDetectCfg->FvdDetectCfg.EachLaneCfg[i].LaneArea[j].y = da.LaneData[i].LaneArea[j].y;
			}

		}
		RestParams(p_cfg->pCfgs, DetLine, &p_cfg->pDetectCfg->FvdDetectCfg, p_cfg->pParams);//重置参数
        return true;
    }

    bool process(Mat img_src,JsonPacket &pkt)
    {
		img_src.copyTo(imgSave);
        //imshow("1",img_src);
         prt(info,"%d %d",img_src.rows,img_src.cols);
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
#ifdef SAVE_VIDEO
		//检测框
		for( i = 0; i < p_cfg->p_outbuf->FVDoutbuf.uObjNum; i++)
		{
			Rect objRect;
			int c;
			objRect.x = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.x;
			objRect.y = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.y;
			objRect.width = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.width;
			objRect.height = p_cfg->p_outbuf->FVDoutbuf.detObj[i].box.height;
			c = p_cfg->p_outbuf->FVDoutbuf.detObj[i].prob;
			char str[30];
			sprintf(str, "   %d", c);
			char str1[50];
			strcpy(str1, p_cfg->p_outbuf->FVDoutbuf.detObj[i].names);
			strcat(str1, str);
			putText(imgSave, str1, Point(objRect.x,objRect.y - 15),CV_FONT_HERSHEY_SIMPLEX,3,Scalar(0,0,255),1,8);
			rectangle(imgSave, objRect, Scalar(0, 0 ,255), 1, 8, 0 );
		}
		//当前人车数
		char str2[50], str3[50];
		sprintf(str2, "Person:%d     ", CurrentPersionCount);
		sprintf(str3, "Vehicle:%d", CurrentVehicleNumber);
		strcat(str2,str3);
		putText(imgSave, str2, Point(0,50),CV_FONT_HERSHEY_SIMPLEX,3,Scalar(0,0,255),1,8);
		for(i = 0; i < p_cfg->pCfgs->ResultMsg.FvdResultInfo.LaneSum; i++)
		{
			CPoint m_ptend[12];
			m_ptend[0]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].LaneArea[0]; 
			m_ptend[1]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].LaneArea[1];
			m_ptend[2]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].LaneArea[3];  
			m_ptend[3]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].LaneArea[2];
			m_ptend[4]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].FarArea[0];  
			m_ptend[5]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].FarArea[1];
			m_ptend[6]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].FarArea[3];  
			m_ptend[7]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].FarArea[2]; 		
			m_ptend[8]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].NearArea[0];  
			m_ptend[9]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].NearArea[1];
			m_ptend[10]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].NearArea[3];  
			m_ptend[11]= p_cfg->pCfgs->DownDetectCfg.FvdDetectCfg.EachLaneCfg[i].NearArea[2]; 
			line(imgSave, Point(m_ptend[0].x,m_ptend[0].y),Point(m_ptend[2].x,m_ptend[2].y), Scalar(255, 0 ,0), 1, 8, 0 );
			line(imgSave, Point(m_ptend[1].x,m_ptend[1].y),Point(m_ptend[3].x,m_ptend[3].y), Scalar(255, 0 ,0), 1, 8, 0 );
			if(p_cfg->pCfgs->ResultMsg.FvdResultInfo.uEachLaneData[i].calarflag)
			{
				line(imgSave, Point(m_ptend[8].x,m_ptend[8].y),Point(m_ptend[9].x,m_ptend[9].y), Scalar(0, 0 ,255), 1, 8, 0 );
				line(imgSave, Point(m_ptend[10].x,m_ptend[10].y),Point(m_ptend[11].x,m_ptend[11].y), Scalar(0, 0 ,255), 1, 8, 0 );
			}
			else
			{
				line(imgSave, Point(m_ptend[8].x,m_ptend[8].y),Point(m_ptend[9].x,m_ptend[9].y), Scalar(255, 0 ,0), 1, 8, 0 );
				line(imgSave, Point(m_ptend[10].x,m_ptend[10].y),Point(m_ptend[11].x,m_ptend[11].y), Scalar(255, 0 ,0), 1, 8, 0 );
			}
			line(imgSave, Point(p_cfg->pCfgs->ResultMsg.FvdResultInfo.uEachLaneData[i].QueLine[0].x,p_cfg->pCfgs->ResultMsg.FvdResultInfo.uEachLaneData[i].QueLine[0].y),Point(p_cfg->pCfgs->ResultMsg.FvdResultInfo.uEachLaneData[i].QueLine[1].x,p_cfg->pCfgs->ResultMsg.FvdResultInfo.uEachLaneData[i].QueLine[1].y), Scalar(0, 255 ,0), 3, 8, 0 );
			if(p_cfg->pCfgs->IsCarInTail[i])
			{
				line(imgSave, Point(m_ptend[4].x,m_ptend[4].y),Point(m_ptend[5].x,m_ptend[5].y), Scalar(0, 0 ,255), 1, 8, 0);
				line(imgSave, Point(m_ptend[6].x,m_ptend[6].y),Point(m_ptend[7].x,m_ptend[7].y), Scalar(0, 0 ,255), 1, 8, 0);
			}
			else
			{
				line(imgSave, Point(m_ptend[4].x,m_ptend[4].y),Point(m_ptend[5].x,m_ptend[5].y), Scalar(255, 0 ,0), 1, 8, 0);
				line(imgSave, Point(m_ptend[6].x,m_ptend[6].y),Point(m_ptend[7].x,m_ptend[7].y), Scalar(255, 0 ,0), 1, 8, 0);
			}
			char str4[50], str5[50];
			sprintf(str4, "%d ", p_cfg->pCfgs->ResultMsg.FvdResultInfo.uEachLaneData[i].uRegionVehicleNumber);//区域车辆数
			sprintf(str5, "%d ", p_cfg->pCfgs->ResultMsg.FvdResultInfo.uEachLaneData[i].uVehicleFlow);//车流量
			putText(imgSave, str4, Point(i * 80 ,100),CV_FONT_HERSHEY_SIMPLEX,3,Scalar(0,0,255),1,8);
			putText(imgSave, str5, Point(i * 80 ,150),CV_FONT_HERSHEY_SIMPLEX,3,Scalar(0,0,255),1,8);

		}
		namedWindow("detect",CV_WINDOW_NORMAL);
		imshow("detect", imgSave);
		waitKey(1);
#endif
		}
};


#endif // MVDPROCESSOR_H
