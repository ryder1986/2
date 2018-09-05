#ifndef PVDPROCESSOR_H
#define PVDPROCESSOR_H

#include "videoprocessor.h"
#include "jsonpacket.h"
#include "algorithm.h"
class PvdProcessorInputData:public JsonData{
public:
    vector <VdPoint> DetectLine;
    PvdProcessorInputData(JsonPacket pkt):JsonData(pkt)
    {
        decode();
    }
    void decode()
    {
        DECODE_OBJ_ARRAY_MEM(DetectLine);
    }
    void encode()
    {
        ENCODE_OBJ_ARRAY_MEM_G(DetectLine);
    }
};

class PvdProcessorOutputData:public JsonData{
public:
    vector <ObjectRect> PvdDetectedObjects;
    int PersonFlow1;
    int PersonFlow2;
    int CurrentPersionCount;
    PvdProcessorOutputData()
    {

    }
    void decode()
    {
        DECODE_OBJ_ARRAY_MEM(PvdDetectedObjects);
        DECODE_INT_MEM(PersonFlow1);
        DECODE_INT_MEM(PersonFlow2);
        DECODE_INT_MEM(CurrentPersionCount);
     }
    void encode()
    {
        ENCODE_OBJ_ARRAY_MEM_G(PvdDetectedObjects);
        ENCODE_INT_MEM(PersonFlow1);
        ENCODE_INT_MEM(PersonFlow2);
        ENCODE_INT_MEM(CurrentPersionCount);
    }
};
class PvdProcessor : public VideoProcessor
{
	typedef struct args{
		double scale_ratio;
		int scan_step;
		cv::Rect area;
		int no;
	}arg_t;
	arg_t arg;
	m_args *p_cfg;
public:
    PvdProcessor(JsonPacket pkt)
    {
		PvdProcessorInputData da(pkt);
		CPoint DetLine[2];
		
		DetLine[0].x = da.DetectLine[0].x;
		DetLine[0].y = da.DetectLine[0].y;
		DetLine[1].x = da.DetectLine[1].x;
		DetLine[1].y = da.DetectLine[1].y;		
		alg_mem_malloc(p_cfg);
		PvdArithInit(p_cfg->pCfgs, DetLine);
    }

    ~PvdProcessor()
    {
		alg_mem_free(p_cfg);
    }
    bool process(Mat img_src,JsonPacket &pkt)
    {
		int i = 0;
		int x = 0, y = 0, w = 0, h = 0, c;
		string names;
		IplImage* img = &IplImage(img_src);
		PvdArithProc(img, p_cfg->pCfgs, p_cfg->p_outbuf)
		PvdProcessorOutputData out;
		out.PersonFlow1 = p_cfg->p_outbuf->PVDoutbuf.uPersonSum[0];
		out.PersonFlow2 = p_cfg->p_outbuf->PVDoutbuf.uPersonSum[1];
		out.CurrentPersionCount = p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum;
		 vector <ObjectRect> PvdDetectedObjects;
		for( i = 0; i < p_cfg->p_outbuf->PVDoutbuf.uPersonTotalSum; i++) 
		{
			x = p_cfg->pCfgs->detPerson.box.x;
			y = p_cfg->pCfgs->detPerson.box.y;
			w = p_cfg->pCfgs->detPerson.box.width;
			h = p_cfg->pCfgs->detPerson.box.height;
			c = p_cfg->pCfgs->detPerson.prob;
			strcpy(names, p_cfg->pCfgs->detPerson.names);
			ObjectRect  obj = ObjectRect(x, y, w, h, names, c);
			out.PvdDetectedObjects.push_back(obj)
		}

		pkt=out.data();
    }
};

#endif // PVDPROCESSOR_H
