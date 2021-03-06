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
#include "videoprocessor.h"
#include <QTimer>
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

    PlayerWidget(CameraInputData data):mn(this)
    {
        connect(&mn,SIGNAL(action_done(int,int)),this,SLOT(handle_menu(int,int)));
        loop=0;
        region_ver_picked=false;
        region_line_picked=false;
        cfg=data;
        frame_rate=0;
        tick_timer=new QTimer();
        connect(tick_timer,SIGNAL(timeout()),this,SLOT(timeout()));

        tick_timer->start(100);
        src=new VideoSource(data.Url);
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(&tmr,SIGNAL(timeout()),this,SLOT(timeout_check()));
        tmr.start(1000);
        connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(right_click(QPoint)));
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

    void set_overlay(JsonPacket cam_out)
    {
        lock.lock();
        output_data=cam_out;
        output_data_fps++;
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
    void draw_detect_area(const vector <VdPoint> points,QPainter &pt,int selected_region)
    {
        if(selected_region)
            pt.setPen(blue_pen2());
        else
            pt.setPen(green_pen2());
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

        pt.setPen(blue_pen2());
        for(int i=0;i<points.size();i++){
            QPoint p_center(points[i].x,points[i].y);
            pt.drawEllipse(p_center,10,10);
        }
    }
    int is_match_region_ver(const vector <VdPoint> points,QPoint p,int distance=20)
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
        bool v1= (((dst.x()<b.x()+10)||(dst.x()<e.x()+10))&&((dst.x()>b.x()-10)||(dst.x()>e.x()-10)));
        bool v2=(  ((dst.y()<b.y()+10)||(dst.y()<e.y()+10))&&((dst.y()>b.y()-10)||(dst.y()>e.y()-10)));
        bool v3= (abs(((dst.x()-e.x())*(dst.y()-b.y()))-((dst.y()-e.y())*(dst.x()-b.x())))<1000);
        if(v1&&v2&&v3)
            return true;
        else
            return false;
    }
    bool is_match_region_line(const vector <VdPoint> line,QPoint p,int distance=20)
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
        return false;

    }
    bool is_match_region_data_ver(const vector <VdPoint> points,QPoint p,int distance=20)
    {
        // is_match_region_ver(points,p);
    }
    QPoint map_point(QPoint p)
    {
        return QPoint(p.x()*img.width()/this->width(),p.y()*img.height()/this->height());
    }
    void draw_process_input(QPainter &pt,string processor,JsonPacket out,int &offset_x,int &offset_y)
    {
        pt.setPen(blue_pen1());

        if(processor==LABLE_PROCESSOR_C4){
        }
        if(processor==LABLE_PROCESSOR_DUMMY){

        }

        if(processor==LABLE_PROCESSOR_PVD){

        }

        if(processor==LABLE_PROCESSOR_FVD){

            FvdProcessorInputData data(out);

#if 0
            for(LaneDataJsonData r: data.LineData)
            {
                QVector<QPoint> ps;
                for(VdPoint v:r.FarArea){ps.push_back(QPoint(v.x+offset_x,v.y+offset_y));}
                pt.drawPolyline(QPolygon(ps));
                ps.clear();
                for(VdPoint v:r.NearArea){ps.push_back(QPoint(v.x+offset_x,v.y+offset_y));}
                pt.drawPolyline(QPolygon(ps));
                ps.clear();
                for(VdPoint v:r.LaneArea){ps.push_back(QPoint(v.x+offset_x,v.y+offset_y));}
                pt.drawPolyline(QPolygon(ps));
            }
#endif
        }
    }

    void draw_process_output(QPainter &pt,string processor,JsonPacket out,int &offset_x,int &offset_y)
    {
        pt.setPen(red_pen1());
        DetectRegionOutputData ro(out);
        int rect_x=ro.DetectionRect.x;
        int rect_y=ro.DetectionRect.y;
        offset_x=rect_x;
        offset_y=rect_y;
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

        if(processor==LABLE_PROCESSOR_FVD){
            FvdProcessorOutputData d(ro.Result);

            for(ObjectRect r:d.FvdDetectedObjects){
                int x=r.x+ro.DetectionRect.x;
                int y=r.y+ro.DetectionRect.y;
                pt.drawRect(QRect(x,y,r.w,r.h));
                pt.drawText(x,y,QString(r.label.data()).append("(").append(QString::number(r.confidence_rate)).append(")"));
            }
            #if 0
            for(LaneOutputJsonData dat: d.LaneOutputData)
            {
                VdPoint s_p=dat.StartQueuePoint;
                VdPoint e_p=dat.EndQueuePoint;
                pt.drawLine(QPoint(s_p.x+rect_x,s_p.y+rect_y),QPoint(e_p.x+rect_x,e_p.y+rect_y));
            }
            #endif
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
        img_painter.drawText(0,img.height(),QString::number(output_data_fps_result));
        cnt=0;
        for(int i=0;i<cfg.DetectRegion.size();i++){
            DetectRegionInputData p=cfg.DetectRegion[i];
            if(output_data.DetectionResult.size()!=cfg.DetectRegion.size())
                break;
            int tmpx,tmpy;

            draw_process_output( img_painter,p.SelectedProcessor, output_data.DetectionResult[i],tmpx,tmpy);
            draw_process_input( img_painter,p.SelectedProcessor, p.ProcessorData,tmpx,tmpy);
            int selected_r=0;
            if(region_ver_picked&&i==selected_region_index-1)
                selected_r=1;
            else
                selected_r=0;
            draw_detect_area(vector<VdPoint>(p.ExpectedAreaVers.begin(),p.ExpectedAreaVers.end()),img_painter,selected_r);
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
    void timeout_check()
    {
        output_data_fps_result=output_data_fps;
        //prt(info,"fps: %d",output_data_fps);
        output_data_fps=0;
    }
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
        region_ver_picked=false;
        mn.set_checkable(false);
    }
    void right_click(QPoint pos)
    {
        mn.show(QCursor::pos());
    }
    void add_region(bool)
    {
        string SelectedProcessor=LABLE_PROCESSOR_DUMMY;
        vector <VdPoint>ExpectedAreaVers;
        ExpectedAreaVers.push_back(VdPoint(0,0));
        ExpectedAreaVers.push_back(VdPoint(640,0));
        ExpectedAreaVers.push_back(VdPoint(640,480));
        ExpectedAreaVers.push_back(VdPoint(0,480));
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
        signal_camera(this,Camera::OP::CHANGE_URL,p);
    }
    FvdProcessorInputData get_fvd_test_data()
    {
        vector <VdPoint> BasicCoil;// standard rect
        BasicCoil.push_back(VdPoint(0,0));
        BasicCoil.push_back(VdPoint(400,0));
        BasicCoil.push_back(VdPoint(400,400));
        BasicCoil.push_back(VdPoint(0,400));
        BaseLineJsonData BaseLine(VdPoint(0,0),VdPoint(50,50),5);// a line can adjust car real length
        int NearPointDistance=20;//distance to camera
        int FarPointDistance=100;
        vector <LaneDataJsonData> LineData; // lane info
        vector <VdPoint> FarArea1; // far rect
        FarArea1.push_back(VdPoint(0,0));
        FarArea1.push_back(VdPoint(100,0));
        FarArea1.push_back(VdPoint(100,100));
        FarArea1.push_back(VdPoint(0,100));
        vector <VdPoint> NearArea1; // near rect
        NearArea1.push_back(VdPoint(0,0+100));
        NearArea1.push_back(VdPoint(100,0+100));
        NearArea1.push_back(VdPoint(100,200));
        NearArea1.push_back(VdPoint(0,0+200));
        vector <VdPoint> LaneArea1; // whole rect
        LaneArea1.push_back(VdPoint(0,0));
        LaneArea1.push_back(VdPoint(100,0));
        LaneArea1.push_back(VdPoint(100,400));
        LaneArea1.push_back(VdPoint(0,400));
        int lane_no=18;
        LaneDataJsonData d1(lane_no,FarArea1,NearArea1,LaneArea1);
        LineData.push_back(d1);
        FvdProcessorInputData d(BasicCoil,BaseLine,NearPointDistance,FarPointDistance,LineData);
        return d;
    }
    PvdProcessorInputData get_pvd_test_data()
    {
        PvdProcessorInputData d(VdPoint(100,200),VdPoint(400,200)); return d;

    }
    DummyProcessorInputData get_dummy_test_data()
    {
        DummyProcessorInputData d(true,false,17);
        return d;
    }
    C4ProcessorInputData get_c4_test_data()
    {
        C4ProcessorInputData d(8,0.7);   return d;
    }
    void set_processor(string processor_label)
    {

        if(selected_region_index<1||selected_region_index>cfg.DetectRegion.size())
            return;

        JsonPacket processor_pkt;
        if(processor_label==LABLE_PROCESSOR_DUMMY){
            processor_pkt=get_dummy_test_data().data();
        }

        if(processor_label==LABLE_PROCESSOR_C4){
            processor_pkt=get_c4_test_data().data();
        }

        if(processor_label==LABLE_PROCESSOR_PVD){
            processor_pkt=get_pvd_test_data().data();
        }

        if(processor_label==LABLE_PROCESSOR_FVD){
            processor_pkt=get_fvd_test_data().data();
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

        set_processor(LABLE_PROCESSOR_DUMMY);
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
        set_processor(LABLE_PROCESSOR_C4);
    }
    void set_region(bool)
    {
        prt(info,"mod region ");
        vector <DetectRegionInputData >detect_regions;
        detect_regions.assign(cfg.DetectRegion.begin(),cfg.DetectRegion.end());
        DetectRegionInputData tmp=detect_regions[selected_region_index-1];
        vector <VdPoint  > vers=tmp.ExpectedAreaVers;
        AreaVersJsonData vs(vers);
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
        if(region_ver_picked){
            if(selected_region_index>0&&selected_point_index>0&&\
                    selected_region_index<=cfg.DetectRegion.size()){
                DetectRegionInputData r=cfg.DetectRegion[selected_region_index-1];
                VdPoint p(p1.x(),p1.y());
                r.set_point(p,selected_point_index);
                cfg.set_region(r.data(),selected_region_index);
            }
            // cfg.encode();
        }

        if(region_line_picked){
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
        vector <DetectRegionInputData >detect_regions;
        detect_regions.assign(cfg.DetectRegion.begin(),cfg.DetectRegion.end());
        for(int i=0;i<detect_regions.size();i++){
            vector <VdPoint> pnts(detect_regions[i].ExpectedAreaVers.begin(),detect_regions[i].ExpectedAreaVers.end());
            int point_index=is_match_region_ver(pnts,map_point(e->pos()));
            if(point_index>0){
                region_ver_picked=true;
                selected_point_index=point_index;
                selected_region_index=i+1;
                mn.set_checkable(true);
                int index=selected_region_index;
                DetectRegionInputData input= cfg.DetectRegion[index-1];
                mn.set_checked_processor(input.SelectedProcessor);
                return;
            }

            bool online=is_match_region_line(pnts,map_point(e->pos()));
            if(online){
                region_line_picked=true;
                ori_point=QPoint(e->pos());
                selected_region_index=i+1;
                return;
            }
        }
        selected_point_index=0;
        selected_region_index=0;
    }
    void mouseReleaseEvent(QMouseEvent *e)
    {
        if(region_ver_picked){
            emit cam_data_change(cfg,this);
            set_region(true);
            region_ver_picked=false;
            mn.set_checkable(false);
        }
        if(region_line_picked){
            emit cam_data_change(cfg,this);
            set_region(true);
            region_line_picked=false;
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

    int loop;
    VideoSource *src;
    bool region_ver_picked;
    bool region_line_picked;
    bool region_data_picked;

    QPoint ori_point;
    QPoint maped_point;

    int selected_region_index;
    int selected_point_index;

    int cnt;
    QTimer *tick_timer;
    int timestamp;
    int screen_state;

    CameraInputData cfg;
    CameraOutputData output_data;
    QTimer tmr;
    int output_data_fps;
    int output_data_fps_result;
};

#endif // PLAYERWIDGET_H
