#include "detectregion.h"

#include "c4processor.h"
#ifdef WITH_CUDA
#include "pvdprocessor.h"
#include "fvdprocessor.h"
#include "mvdprocessor.h"
#endif
DetectRegion::DetectRegion(DetectRegionInputData pkt):VdData(pkt),p(NULL)
{
    lock.lock();
    int valid=false;
    //  p=new PvdMvncProcessor();
    if(private_data.SelectedProcessor==LABLE_PROCESSOR_C4)
    {    p=new PvdC4Processor(pkt.data());valid=true;}
    if(private_data.SelectedProcessor==LABLE_PROCESSOR_DUMMY)
    {   p=new DummyProcessor(private_data.ProcessorData);valid=true;}

#ifdef WITH_CUDA
    if(private_data.SelectedProcessor==LABLE_PROCESSOR_PVD)
    {   p=new PvdProcessor(private_data.ProcessorData);valid=true;}
    if(private_data.SelectedProcessor==LABLE_PROCESSOR_FVD)
    {   p=new FvdProcessor(private_data.ProcessorData);valid=true;}
    if(private_data.SelectedProcessor==LABLE_PROCESSOR_MVD)
    {   p=new MvdProcessor(private_data.ProcessorData);valid=true;}
#endif
    if(!valid){
        prt(info,"processor %s error ,exit",private_data.SelectedProcessor.data());
        //  exit(0);
    }
    detect_rect=reshape_2_rect(private_data.ExpectedAreaVers);

    lock.unlock();
}

void DetectRegion::modify(RequestPkt pkt)
{
    lock.lock();
    int op=pkt.Operation;
    switch(op){
    case OP::CHANGE_RECT:
    {
        AreaVersJsonData vs(pkt.Argument);
        detect_rect=reshape_2_rect(vs.ExpectedAreaVers);
        private_data.set_points(vs.ExpectedAreaVers);
        break;
    }
    case OP::CHANGE_PROCESSOR:
    {
        if(p){
            delete p;
            p=NULL;
        }
        ProcessorDataJsonData sp(pkt.Argument);
        string pro=sp.SelectedProcessor;
        //string pro=    pkt.Argument.get("SelectedProcessor").to_string();
        if(pro==LABLE_PROCESSOR_C4){
            p=new PvdC4Processor(sp.ProcessorData);
            private_data.set_processor(pro,sp.ProcessorData);
        }
        if(pro==LABLE_PROCESSOR_DUMMY){
            p=new DummyProcessor(sp.ProcessorData);
            private_data.set_processor(pro,sp.ProcessorData);
        }
#ifdef WITH_CUDA
        if(pro==LABLE_PROCESSOR_PVD)
        {
            p=new PvdProcessor(sp.ProcessorData);
            private_data.set_processor(pro,sp.ProcessorData);
        }
        if(pro==LABLE_PROCESSOR_FVD)
        {
            p=new FvdProcessor(sp.ProcessorData);
            private_data.set_processor(pro,sp.ProcessorData);
        }
        if(pro==LABLE_PROCESSOR_MVD)
        {
            p=new MvdProcessor(sp.ProcessorData);
            private_data.set_processor(pro,sp.ProcessorData);
        }

#endif
        break;
    }
    case OP::MODIFY_PROCESSOR:
    {

        p-> modify_processor(pkt.Argument);
        private_data.set_processor_data(pkt.Argument);
        break;
    }

defalut:break;
    }
    lock.unlock();
}
