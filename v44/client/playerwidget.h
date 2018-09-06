#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <QMutex>
#include <QPainter>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include "camera.h"
#include "videosource.h"
#include "detectregion.h"
#define POLY_VER_NUM 4

class PlayerWidgetMenu:public QObject
{
    Q_OBJECT
public:
    enum CMD_LAYER1{
        CAMERA_ADD_REGION=1,
        CAMERA_DEL_REGION,
        CAMERA_RESET_URL,
        HIDE_MENU
    };
    enum CMD_LAYER2{
        MOD_REGION_PROCESSOR_TO_C4=1,
        MOD_REGION_PROCESSOR_TO_FVD,
        MOD_REGION_PROCESSOR_TO_PVD,
        MOD_REGION_PROCESSOR_TO_DUMMY
    };
    QWidget *wgt;
    QAction add_region;
    QAction del_region;
    QAction reset_url;
    QMenu menu;

    QMenu mod_processor;
    QAction choose_c4;
    QAction choose_fvd;
    QAction choose_pvd;
    QAction choose_dummy;
public:
    PlayerWidgetMenu(QWidget *w):wgt(w),menu(wgt),mod_processor("change processor")
    {
        menu.addMenu(&mod_processor);
        add_region.setText("add_region");
        del_region.setText("del_region");
        reset_url.setText("reset_url");
        menu.addAction(&add_region);
        menu.addAction(&del_region);
        menu.addAction(&reset_url);
        connect(&add_region,SIGNAL(triggered(bool)),this,SLOT(camera_op_add_region(bool)));
        connect(&del_region,SIGNAL(triggered(bool)),this,SLOT(camera_op_del_region(bool)));
        connect(&reset_url,SIGNAL(triggered(bool)),this,SLOT(camera_op_reset_url(bool)));

        choose_c4.setText("c4");
        mod_processor.addAction(&choose_c4);
        choose_fvd.setText("fvd");
        mod_processor.addAction(&choose_fvd);
        choose_pvd.setText("pvd");
        mod_processor.addAction(&choose_pvd);
        choose_dummy.setText("dummy");
        mod_processor.addAction(&choose_dummy);

        connect(&choose_c4,SIGNAL(triggered(bool)),this,SLOT(processor_op_choose_c4(bool)));
        connect(&choose_fvd,SIGNAL(triggered(bool)),this,SLOT(processor_op_choose_fvd(bool)));
        connect(&choose_pvd,SIGNAL(triggered(bool)),this,SLOT(processor_op_choose_pvd(bool)));
        connect(&choose_dummy,SIGNAL(triggered(bool)),this,SLOT(processor_op_choose_dummy(bool)));


        connect(&menu,SIGNAL(aboutToHide()),this,SLOT(hide_menu()));
    }
    void reset()
    {

    }
    void show(QPoint p)
    {
        menu.exec(p);
    }
    void set_checkable(bool ca)
    {
        choose_pvd.setCheckable(ca);
        choose_fvd.setCheckable(ca);
        choose_dummy.setCheckable(ca);
        choose_c4.setCheckable(ca);
//        if(ca){

//        }else{

//        }
    }
    void set_checked_processor(string label)
    {

        choose_pvd.setChecked(false);
        choose_fvd.setChecked(false);
        choose_dummy.setChecked(false);
        choose_c4.setChecked(false);

        if(label==LABLE_PROCESSOR_C4) choose_c4.setChecked(true);
        if(label==LABLE_PROCESSOR_DUMMY) choose_dummy.setChecked(true);
        if(label==LABLE_PROCESSOR_FVD) choose_fvd.setChecked(true);
        if(label==LABLE_PROCESSOR_PVD) choose_pvd.setChecked(true);
      }
public slots:
    void hide_menu()
    {
        emit action_done(HIDE_MENU,0);
    }
    void camera_op_add_region(bool)
    {
        emit action_done(CAMERA_ADD_REGION,0);
    }
    void camera_op_del_region(bool)
    {
        emit action_done(CAMERA_DEL_REGION,0);
    }
    void camera_op_reset_url(bool)
    {
        emit action_done(CAMERA_RESET_URL,0);
    }
    void processor_op_choose_c4(bool)
    {
        emit action_done(0,MOD_REGION_PROCESSOR_TO_C4);
    }
    void processor_op_choose_pvd(bool)
    {
        emit action_done(0,MOD_REGION_PROCESSOR_TO_PVD);
    }
    void processor_op_choose_fvd(bool)
    {
        emit action_done(0,MOD_REGION_PROCESSOR_TO_FVD);
    }
    void processor_op_choose_dummy(bool)
    {
        emit action_done(0,MOD_REGION_PROCESSOR_TO_DUMMY);
    }
signals:
    void action_done(int level1,int level2);
};

class PlayerWidget : public QOpenGLWidget
{
    Q_OBJECT
    PlayerWidgetMenu mn;
public:
    enum Operation{
        FULL_SCREEN,
        NORMAL_SCREEN
    };
    enum ClickEvent{
        SHOW_ONE,
        SHOW_ALL
    };
    ~PlayerWidget()
    {
        prt(info,"delete wgt");
        tick_timer->stop();
        delete tick_timer;
        delete src;
    }

    PlayerWidget(CameraInputData data):action_add_region(this),action_del_region(this),menu(this),menu_processor("processor"),mn(this)
    {
        connect(&mn,SIGNAL(action_done(int,int)),this,SLOT(handle_menu(int,int)));
        //rects.clear();
        loop=0;
        ver_picked=false;
        line_picked=false;
        cfg=data;
        frame_rate=0;
        tick_timer=new QTimer();
        connect(tick_timer,SIGNAL(timeout()),this,SLOT(timeout()));

        tick_timer->start(100);
        src=new VideoSource(data.Url);
        //         menu=new QMenu(this);
        //         action_add_channel=new QAction(this);   action_del_channel->setText("del channel")
        //         menu->addAction(action_add_channel);
        //         connect(action_add_channel,SIGNAL(triggered(bool)),this,SLOT(add_channel(bool)));
        //         menu->exec(pos);
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(right_click(QPoint)));
        action_add_region.setText("add region");
        connect(&action_add_region,SIGNAL(triggered(bool)),this,SLOT(add_region(bool)));
        action_del_region.setText("del region");
        connect(&action_del_region,SIGNAL(triggered(bool)),this,SLOT(del_region(bool)));
        //menu_processor.setText("change processor");
        // connect(&menu_processor,SIGNAL(triggered(bool)),this,SLOT(set_region(bool)));
        action_change_url.setText("reset url");
        connect(&action_change_url,SIGNAL(triggered(bool)),this,SLOT(set_url(bool)));

        menu.addAction(&action_add_region);
        menu.addAction(&action_del_region);
        menu.addMenu(&menu_processor);
        processor_c4.setText(LABLE_PROCESSOR_C4);
        processor_dummy.setText(LABLE_PROCESSOR_DUMMY);
        processor_pvd.setText(LABLE_PROCESSOR_PVD);

        connect(&processor_dummy,SIGNAL(triggered(bool)),this,SLOT(set_processor_dummy(bool)));
        connect(&processor_pvd,SIGNAL(triggered(bool)),this,SLOT(set_processor_pvd(bool)));
        connect(&processor_c4,SIGNAL(triggered(bool)),this,SLOT(set_processor_c4(bool)));
        menu_processor.addAction(&processor_c4);
        menu_processor.addAction(&processor_dummy);
        menu_processor.addAction(&processor_pvd);
        menu.addAction(&action_change_url);
        connect(&menu,SIGNAL(aboutToHide()),this,SLOT(hide_menu()));
    }
    void set_title(QString t)
    {
        lock.lock();
        title=t;
        lock.unlock();
    }

    void set_show(bool flg)
    {
        show_info=flg;
    }

    void set_overlay(vector<QRect> rs,int ts)
    {
        lock.lock();
        //rects.assign(rs.begin(),rs.end());
        timestamp=ts;
        lock.unlock();
    }
    void set_overlay(JsonPacket cam_out)
    {
        lock.lock();
        //    prt(info,"get cam rst %s ##### cfg %s",cam_out.str().data(),cfg.data().str().data());

        output_data=cam_out;
        CameraOutputData  out=cam_out;

        //        if(out.DetectionResult.size()!=cfg.DetectRegion.size()){
        //            lock.unlock();
        //            prt(info,"cfg dont match: output size %d , now size %d",out.DetectionResult.size(),cfg.DetectRegion.size());
        //            return;
        //        }
        //        //       prt(info,"sz %d",out.DetectionResult.size());
        //        for(int i=0;i<out.DetectionResult.size();i++){
        //            DetectRegionInputData d=  cfg.DetectRegion[i];
        //            DetectRegionOutputData  o= out.DetectionResult[i];
        //            //         prt(info,"processor %s",d.SelectedProcessor.data());
        //            if(d.SelectedProcessor==LABLE_PROCESSOR_C4){
        //                C4ProcessorOutputData c4o=o.Result;
        //                //rects.assign(c4o.Rects.begin(),c4o.Rects.end());
        //                //   rects.clear();
        //                for(VdRect v:c4o.Rects){
        //                    QRect r(v.x+o.DetectionRect.x,v.y+o.DetectionRect.y,v.w,v.h);
        //                    rects.push_back(r);
        //                }
        //                // QRect rrr=rects.at(rects.size()-1);
        //                //  prt(info,"process c4 %d results (%d,%d,%d,%d) ",c4o.Rects.size(),rrr.x(),rrr.y(),rrr.width(),rrr.height());

        //            }
        //            if(d.SelectedProcessor==LABLE_PROCESSOR_DUMMY){
        //                DummyProcessorOutputData dummyo=o.Result;

        //                for(VdPoint v:dummyo.Points){
        //                    QRect rct(objectrect.x+o.DetectionRect.x,objectrect.y+o.DetectionRect.y,objectrect.w,objectrect.h);
        //                    rects.push_back(rct);
        //                }
        //            }
        //            if(d.SelectedProcessor=="Pvd"){}
        //            if(d.SelectedProcessor=="Fvd"){}
        //        }
        //      rects.assign(rs.begin(),rs.end());
        //      timestamp=ts;
        lock.unlock();
    }
    bool  get_img()
    {
        Mat rgb_frame;
        Mat bgr_frame;
        bool ret=src->get_frame(bgr_frame);
        if(ret){
            cvtColor(bgr_frame,rgb_frame,CV_BGR2RGB);
            img=QImage((const uchar*)(rgb_frame.data),
                       rgb_frame.cols,rgb_frame.rows,
                       QImage::Format_RGB888);
            img.bits();
        }
        return ret;
    }
    void draw_points(const vector <VdPoint> points,QPainter &pt)
    {

        if(points.size()<1)
            return;
        for(int i=1;i<points.size();i++){
            QPoint p1(   QPoint(points[i-1].x,points[i-1].y));
            QPoint p2( QPoint(points[i].x,points[i].y));
            pt.drawLine(p1,p2);
        }

        QPoint p1(QPoint(points.front().x,points.front().y));
        QPoint p2(QPoint(points.back().x,points.back().y));
        pt.drawLine(p1,p2);


        pt.setPen(red_pen2());
        for(int i=0;i<points.size();i++){
            QPoint p_center(points[i].x,points[i].y);
            pt.drawEllipse(p_center,10,10);
        }
    }
    int match_point_on_ver(const vector <VdPoint> points,QPoint p,int distance=20)
    {
        for(int i=0;i<points.size();i++){
            if(abs(points[i].x-p.x())<distance&&(abs(points[i].y-p.y()))<distance){
                return (i+1);
            }
        }
        return 0;

    }
    inline bool p_on_l(QPoint b,QPoint e, QPoint dst)
    {
        //  return true;

        bool v1= (((dst.x()<b.x()+10)||(dst.x()<e.x()+10))&&((dst.x()>b.x()-10)||(dst.x()>e.x()-10)));
        bool v2=(  ((dst.y()<b.y()+10)||(dst.y()<e.y()+10))&&((dst.y()>b.y()-10)||(dst.y()>e.y()-10)));
        bool v3= (abs(((dst.x()-e.x())*(dst.y()-b.y()))-((dst.y()-e.y())*(dst.x()-b.x())))<1000);
        //         if ( (((dst.x()<b.x())||(dst.x()<e.x()))&&((dst.x()>b.x())||(dst.x()>e.x())))&&
        //              (  ((dst.y()<b.y())||(dst.y()<e.y()))&&((dst.y()>b.y())||(dst.y()>e.y())))&&
        //                (abs(((dst.x()-e.x())*(dst.y()-b.y()))-((dst.y()-e.y())*(dst.x()-b.x())))<100))

        // if(v1&&v2&&v3)
        if(v1&&v2&&v3)
            return true;
        else
            return false;
    }
    bool match_point_on_line(const vector <VdPoint> line,QPoint p,int distance=20)
    {
        vector<QPoint> pns;
        for(VdPoint p:line){
            pns.push_back(QPoint(p.x,p.y));

        }

        for(int i=1;i<pns.size();i++){
            if(p_on_l(pns[i-1],pns[i],p)){
                return true;
            }
        }
        if(p_on_l(pns[0],pns[line.size()-1],p)){
            return true;
        }
        //        for(int i=0;i<points.size();i++){
        //            if(abs(points[i].x-p.x())<distance&&(abs(points[i].y-p.y()))<distance){
        //                return (i+1);
        //            }
        //        }
        return false;

    }
    QPoint map_point(QPoint p)
    {
        return QPoint(p.x()*img.width()/this->width(),p.y()*img.height()/this->height());
    }
    void draw_processor(QPainter &pt,string processor,JsonPacket out)
    {
        DetectRegionOutputData ro(out);
        if(processor==LABLE_PROCESSOR_C4){
            C4ProcessorOutputData d(ro.Result);
            for(VdRect r:d.Rects){
                pt.drawRect(QRect(r.x+ro.DetectionRect.x,r.y+ro.DetectionRect.y,r.w,r.h));
            }
        }
        if(processor==LABLE_PROCESSOR_DUMMY){
            DummyProcessorOutputData d(ro.Result);
            for(VdPoint p:d.Points){
                pt.drawEllipse(QPoint(p.x+ro.DetectionRect.x,p.y+ro.DetectionRect.y),d.Radii,d.Radii);
            }
        }

        if(processor==LABLE_PROCESSOR_PVD){
            PvdProcessorOutputData d(ro.Result);
            for(ObjectRect r:d.PvdDetectedObjects){
                pt.drawRect(QRect(r.x+ro.DetectionRect.x,r.y+ro.DetectionRect.y,r.w,r.h));
            }
        }

    }
protected:
    void paintEvent(QPaintEvent *)
    {
        lock.lock();
        QPainter this_painter(this);
        if(!get_img()){
            lock.unlock();
            return;
        }
        QPainter img_painter(&img);
        img_painter.setPen(blue_pen1());
        //        for(QRect r:rects){
        //            img_painter.drawRect(r);
        //        }
        //rects.clear();
        img_painter.setPen(red_pen1());
        cnt=0;
        for(int i=0;i<cfg.DetectRegion.size();i++){
            DetectRegionInputData p=cfg.DetectRegion[i];
            if(output_data.DetectionResult.size()!=cfg.DetectRegion.size())
                break;
            draw_processor( img_painter,p.SelectedProcessor, output_data.DetectionResult[i]);
            if(ver_picked&&i==selected_region_index-1)
                img_painter.setPen(blue_pen2());
            else
                img_painter.setPen(green_pen2());
            draw_points(vector<VdPoint>(p.ExpectedAreaVers.begin(),p.ExpectedAreaVers.end()),img_painter);
        }

        if(!img.isNull()){
            this_painter.drawImage(QRect(0,0,this->width(),this->height()),img);
        }
        lock.unlock();
    }
    void  initializeGL()
    {

    }

public slots:
    void handle_menu(int level1 ,int level2)
    {
        if(level1){
            switch(level1){
            case PlayerWidgetMenu::CAMERA_ADD_REGION:
                add_region(true);
            case PlayerWidgetMenu::CAMERA_DEL_REGION:
                del_region(true);
            case PlayerWidgetMenu::CAMERA_RESET_URL:
                set_url(true);
            case PlayerWidgetMenu::HIDE_MENU:
                hide_menu();
                //add_region(true);
                break;
            default:break;
            }
            return;
        }
        if(level2){
            switch(level2){
            case PlayerWidgetMenu::MOD_REGION_PROCESSOR_TO_C4:
                set_processor(LABLE_PROCESSOR_C4);
                break;
            case PlayerWidgetMenu::MOD_REGION_PROCESSOR_TO_FVD:
                set_processor(LABLE_PROCESSOR_FVD);
                break;
            case PlayerWidgetMenu::MOD_REGION_PROCESSOR_TO_PVD:
                set_processor(LABLE_PROCESSOR_PVD);
                break;
            case PlayerWidgetMenu::MOD_REGION_PROCESSOR_TO_DUMMY:
                set_processor(LABLE_PROCESSOR_DUMMY);
                break;
            default:break;
            }
            return;
        }
    }
    void hide_menu()
    {
        //prt(info,"hide menu");
        ver_picked=false;
        //        processor_dummy.setChecked(false);
        //        processor_c4.setChecked(false);
        processor_c4.setCheckable(false);
        processor_c4.setChecked(false);
        processor_dummy.setCheckable(false);
        processor_dummy.setChecked(false);
        processor_pvd.setCheckable(false);
        processor_pvd.setChecked(false);

        mn.set_checkable(false);
    }
    void right_click(QPoint pos)
    {
        //prt(info,"right click at %d %d",pos.x(),pos.y());
        //prt(info,"pos at %d %d",this->x(),this->y());
        //     menu.exec(QCursor::pos());
        mn.show(QCursor::pos());

    }
    void add_region(bool)
    {
        string SelectedProcessor=LABLE_PROCESSOR_DUMMY;
        //string SelectedProcessor="C4";
        vector <VdPoint>ExpectedAreaVers;
        ExpectedAreaVers.push_back(VdPoint(0,0));
        ExpectedAreaVers.push_back(VdPoint(640,0));
        ExpectedAreaVers.push_back(VdPoint(640,480));
        ExpectedAreaVers.push_back(VdPoint(0,480));
        //        C4ProcessorInputData c4d(6,"0.6");
        //        JsonPacket ProcessorData=c4d.data();

        DummyProcessorInputData dp(true,false,15);


        DetectRegionInputData rd(dp.data(),SelectedProcessor,ExpectedAreaVers);
        RequestPkt pkt(Camera::OP::INSERT_REGION,cfg.DetectRegion.size(),rd.data());
        signal_camera(this,Camera::OP::INSERT_REGION,pkt.data());
        prt(info,"add region");
    }
    void del_region(bool)
    {
        prt(info,"del region ");
        RequestPkt pkt(Camera::OP::DELETE_REGION,selected_region_index,JsonPacket());
        signal_camera(this,Camera::OP::DELETE_REGION,pkt.data());
    }
    void set_url(bool)
    {
        JsonPacket p;
        p.add("Url","rtsp://192.168.1.95:554/av0_1");
        RequestPkt pkt(Camera::OP::CHANGE_URL,0,p);
        signal_camera(this,Camera::OP::CHANGE_URL,pkt.data());
    }
    void set_processor(string processor_label)
    {

        if(selected_region_index<1||selected_region_index>cfg.DetectRegion.size())
            return;

        JsonPacket processor_pkt;
        if(processor_label==LABLE_PROCESSOR_DUMMY){
            DummyProcessorInputData did(true,false,17);
            processor_pkt=did.data();

        }

        if(processor_label==LABLE_PROCESSOR_C4){
            C4ProcessorInputData did(8,0.7);
            processor_pkt=did.data();
        }

        if(processor_label==LABLE_PROCESSOR_PVD){
            PvdProcessorInputData did(VdPoint(100,200),VdPoint(400,200));
            processor_pkt=did.data();
        }

        ProcessorDataJsonData pd(processor_label,processor_pkt);

        RequestPkt req(DetectRegion::OP::CHANGE_PROCESSOR,0,pd.data());
        RequestPkt pkt(Camera::OP::MODIFY_REGION,selected_region_index,req.data());
        signal_camera(this,Camera::OP::MODIFY_REGION,pkt.data());
        //////////
        DetectRegionInputData di= cfg.DetectRegion[selected_region_index-1];
        di.set_processor(processor_label,processor_pkt);
        cfg.set_region(di.data(),selected_region_index);

    }
    void set_processor_dummy(bool checked)
    {
        if(selected_region_index<1||selected_region_index>cfg.DetectRegion.size())
            return;
#if 1
        set_processor(LABLE_PROCESSOR_DUMMY);
#else

        prt(info,"checked %d",checked);
        DummyProcessorInputData did(true,false,17);
        ProcessorDataJsonData pd(LABLE_PROCESSOR_DUMMY,did.data());

        RequestPkt req(DetectRegion::OP::CHANGE_PROCESSOR,0,pd.data());
        RequestPkt pkt(Camera::OP::MODIFY_REGION,selected_region_index,req.data());
        DetectRegionInputData di= cfg.DetectRegion[selected_region_index-1];
        di.set_processor(LABLE_PROCESSOR_DUMMY,did.data());
        cfg.set_region(di.data(),selected_region_index);
        signal_camera(this,Camera::OP::MODIFY_REGION,pkt.data());
#endif
    }



    void set_processor_pvd(bool checked)
    {
        if(selected_region_index<1||selected_region_index>cfg.DetectRegion.size())
            return;

        set_processor(LABLE_PROCESSOR_PVD);
    }

    void set_processor_c4(bool checked)
    {
        if(selected_region_index<1||selected_region_index>cfg.DetectRegion.size())
            return;
#if 1
        set_processor(LABLE_PROCESSOR_C4);
#else
        prt(info,"checked %d",checked);
        C4ProcessorInputData did(8,0.7);
        ProcessorDataJsonData pd(LABLE_PROCESSOR_C4,did.data());

        RequestPkt req(DetectRegion::OP::CHANGE_PROCESSOR,0,pd.data());
        RequestPkt pkt(Camera::OP::MODIFY_REGION,selected_region_index,req.data());
        DetectRegionInputData di= cfg.DetectRegion[selected_region_index-1];
        di.set_processor(LABLE_PROCESSOR_C4,did.data());
        cfg.set_region(di.data(),selected_region_index);
        signal_camera(this,Camera::OP::MODIFY_REGION,pkt.data());
#endif

    }
    void set_region(bool)
    {
        prt(info,"mod region ");
        vector <DetectRegionInputData >detect_regions;
        detect_regions.assign(cfg.DetectRegion.begin(),cfg.DetectRegion.end());
        DetectRegionInputData tmp=detect_regions[selected_region_index-1];
        vector <VdPoint  > vers=tmp.ExpectedAreaVers;
        AreaVersJsonData vs(vers);

        //        vector <JsonPacket  > vers_pkt;
        //        JsonPacket p;
        //        for(int i=0;i<vers.size();i++){
        //            vers_pkt.push_back(vers[i].data());
        //        }
        //        p.add("ExpectedAreaVers",vers_pkt);
        RequestPkt r_pkt(DetectRegion::OP::CHANGE_RECT,0,vs.data());
        RequestPkt pkt(Camera::OP::MODIFY_REGION,selected_region_index,r_pkt.data());
        signal_camera(this,Camera::OP::MODIFY_REGION,pkt.data());
    }
    void timeout()
    {
        this->update();
    }
    void mouseMoveEvent(QMouseEvent *e)
    {
        QPoint p1=map_point(e->pos());
        //  QPoint p1=map_point(QCursor::pos());

        if(ver_picked){
            //     prt(info,"seting %d, picked %d , index1:%d ,index2:%d,size %d",e->pos().x(),ver_picked,\
            selected_region_index,selected_point_index,cfg.DetectRegion.size());
            //  prt(info,"drag (region %d,point %d )to (%d,%d)",\
            selected_region_index,selected_point_index,e->pos().x(),e->pos().y());
            if(selected_region_index>0&&selected_point_index>0&&\
                    selected_region_index<=cfg.DetectRegion.size()){
                DetectRegionInputData r=cfg.DetectRegion[selected_region_index-1];
                VdPoint p(p1.x(),p1.y());
                r.set_point(p,selected_point_index);
                //    prt(info,"before:%s",cfg.data().str().data());
                cfg.set_region(r.data(),selected_region_index);
                //               prt(info,"after:%s",cfg.data().str().data());
            }
            // cfg.encode();
        }

        if(line_picked){
            DetectRegionInputData r=cfg.DetectRegion[selected_region_index-1];
            vector <VdPoint> ps;
            QPoint end_p= map_point(e->pos());
            QPoint ori_p= map_point(ori_point);
            for(VdPoint p:r.ExpectedAreaVers){
                ps.push_back(VdPoint(p.x+(end_p.x()-ori_p.x()),p.y+(end_p.y()-ori_p.y())));
            }
            r.set_points(ps);
            cfg.set_region(r.data(),selected_region_index);
            ori_point=e->pos();
            //prt(info,"line move (%d, %d) to (%d, %d)",ori_point.x(),ori_point.y(),e->pos().x(),e->pos().y());
        }
    }
    void mousePressEvent(QMouseEvent *e)
    {
        //   prt(info,"press");

        vector <DetectRegionInputData >detect_regions;
        detect_regions.assign(cfg.DetectRegion.begin(),cfg.DetectRegion.end());
        for(int i=0;i<detect_regions.size();i++){
            vector <VdPoint> pnts(detect_regions[i].ExpectedAreaVers.begin(),detect_regions[i].ExpectedAreaVers.end());
            int point_index=match_point_on_ver(pnts,map_point(e->pos()));
            if(point_index>0){
                ver_picked=true;
                selected_point_index=point_index;
                selected_region_index=i+1;

                processor_c4.setCheckable(true);
                processor_c4.setChecked(false);
                processor_dummy.setCheckable(true);
                processor_dummy.setChecked(false);
                processor_pvd.setCheckable(true);
                processor_pvd.setChecked(false);

                mn.set_checkable(true);
                int index=selected_region_index;
                DetectRegionInputData input= cfg.DetectRegion[index-1];

                if(input.SelectedProcessor==LABLE_PROCESSOR_C4)
                    processor_c4.setChecked(true);
                else
                    processor_c4.setChecked(false);

                if(input.SelectedProcessor==LABLE_PROCESSOR_DUMMY)
                    processor_dummy.setChecked(true);
                else
                    processor_dummy.setChecked(false);

                if(input.SelectedProcessor==LABLE_PROCESSOR_PVD)
                    processor_pvd.setChecked(true);
                else
                    processor_pvd.setChecked(false);


                   //if(input.SelectedProcessor==LABLE_PROCESSOR_C4)
                       mn.set_checked_processor(input.SelectedProcessor);


                return;
            }

            bool online=match_point_on_line(pnts,map_point(e->pos()));
            if(online){
                line_picked=true;
                ori_point=QPoint(e->pos());
                selected_region_index=i+1;



                //                int index=selected_region_index;
                //                DetectRegionInputData input= cfg.DetectRegion[index-1];
                //                if(input.SelectedProcessor=="C4")
                //                    processor_c4.setChecked(true);
                //                else
                //                    processor_c4.setChecked(false);
                //                if(input.SelectedProcessor=="Dummy")
                //                    processor_dummy.setChecked(true);
                //                else
                //                    processor_dummy.setChecked(false);

                return;
            }
        }
        selected_point_index=0;
        selected_region_index=0;
    }
    void mouseReleaseEvent(QMouseEvent *e)
    {
        if(ver_picked){
            emit cam_data_change(cfg,this);
            set_region(true);
            ver_picked=false;

            processor_c4.setCheckable(false);
            processor_c4.setChecked(false);
            processor_dummy.setCheckable(false);
            processor_dummy.setChecked(false);
            processor_pvd.setCheckable(false);
            processor_pvd.setChecked(false);

            mn.set_checkable(false);
        }
        if(line_picked){
            emit cam_data_change(cfg,this);
            set_region(true);
            line_picked=false;
        }
    }
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        if(++double_click_flag%2)
            emit click_event(this,ClickEvent::SHOW_ONE);
        else
            emit click_event(this,ClickEvent::SHOW_ALL);
    }
private:
    int double_click_flag;
    QPen blue_pen1()
    {
        return QPen (QBrush (QColor(0,0,222)),1);
    }

    QPen blue_pen2()
    {
        return QPen (QBrush (QColor(0,0,222)),5);
    }
    QPen red_pen1()
    {
        return QPen (QBrush (QColor(255,0,0)),1);
    }
    QPen red_pen2()
    {
        return QPen (QBrush (QColor(255,0,0)),5);
    }
    QPen green_pen1()
    {
        return QPen (QBrush (QColor(0,255,0)),1);
    }
    QPen green_pen2()
    {
        return QPen (QBrush (QColor(0,255,0)),5);
    }
signals:
    void click_event(PlayerWidget *w,int);
    void cam_data_change(CameraInputData ,QWidget *w);
    void signal_camera(PlayerWidget *w,int op,JsonPacket data);
    void signal_region(PlayerWidget *w,int region_index,int op,JsonPacket data);
    void add_region(int region_index ,DetectRegionInputData rct,QWidget *w);
    void del_region(int region_index ,QWidget *w);
    void set_region(int region_index ,QWidget *w);
    void mod_region(int region_index ,JsonPacket mod_data,QWidget *w);
    void selected(PlayerWidget *w);
    void data_changed();
    void alg_changed(int index);

private:
    int pic_w;
    int pic_h;
    QString title;
    QMutex lock;
    int frame_rate;
    QImage img;
    QList <QPoint> area_v;
    bool show_info;
    int channel_num;
    int poly_num;
    CameraInputData cfg;
    // CameraInputData
    int loop;
    VideoSource *src;
    bool ver_picked;
    bool line_picked;

    QPoint maped_point;
    int selected_region_index;
    int selected_point_index;
    QPoint ori_point;
    int cnt;
    //vector <QRect> rects;
    QTimer *tick_timer;
    int timestamp;

    QMenu menu;
    QAction action_add_region;
    QAction action_del_region;
    QMenu menu_processor;
    QAction action_change_url;
    QAction processor_c4;
    QAction processor_pvd;
    QAction processor_dummy;
    vector <QAction> actions;
    int screen_state;

    CameraOutputData output_data;
};

#endif // PLAYERWIDGET_H
