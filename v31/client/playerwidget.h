#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <QMutex>
#include <QPainter>
#include <QMouseEvent>
#include "camera.h"
#include "videosource.h"
#define POLY_VER_NUM 4
class PlayerWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    ~PlayerWidget()
    {
        prt(info,"delete wgt");
        tick_timer->stop();
        delete tick_timer;
        delete src;
    }

    PlayerWidget(CameraInputData data)
    {
        rects.clear();
        loop=0;
        ver_picked=false;
        cfg=data;
        frame_rate=0;
        tick_timer=new QTimer();
        connect(tick_timer,SIGNAL(timeout()),this,SLOT(timeout()));
        tick_timer->start(100);
        src=new VideoSource(data.Url);
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
        rects.assign(rs.begin(),rs.end());
        timestamp=ts;
        lock.unlock();
    }
    void set_overlay(JsonPacket cam_out)
    {
        lock.lock();
    //    prt(info,"get cam rst %s ##### cfg %s",cam_out.str().data(),cfg.data().str().data());
        CameraOutputData  out=cam_out;

   //       prt(info,"sz %d",out.DetectionResult.size());
        for(int i=0;i<out.DetectionResult.size();i++){
            DetectRegionInputData d=  cfg.DetectRegion[i];
            DetectRegionOutputData  o= out.DetectionResult[i];
   //         prt(info,"processor %s",d.SelectedProcessor.data());
            if(d.SelectedProcessor=="c4"){
                C4ProcessorOutputData c4o=o.Result;
                //rects.assign(c4o.Rects.begin(),c4o.Rects.end());
             //   rects.clear();
                for(VdRect v:c4o.Rects){
                    QRect r(v.x+o.DetectionRect.x,v.y+o.DetectionRect.y,v.w,v.h);
                    rects.push_back(r);
                }
                QRect rrr=rects.at(rects.size()-1);
         //          prt(info,"process c4 %d results (%d,%d,%d,%d) ",c4o.Rects.size(),rrr.x(),rrr.y(),rrr.width(),rrr.height());

            }
            if(d.SelectedProcessor=="dummy"){

                DummyProcessorOutputData dummyo=o.Result;
                //rects.assign(c4o.Rects.begin(),c4o.Rects.end());
              //  rects.clear();
                for(ObjectRect objectrect:dummyo.DetectedObjects){
                    QRect rct(objectrect.x+o.DetectionRect.x,objectrect.y+o.DetectionRect.y,objectrect.w,objectrect.h);
                    rects.push_back(rct);
                }
               // prt(info,"get %d dummy rect ",rects.size())
            //        prt(info,"process dummy %d results ",dummyo.DetectedObjects.size());

            }
            if(d.SelectedProcessor=="pvd"){}
            if(d.SelectedProcessor=="fvd"){}


        }
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
    }
    int match_point(const vector <VdPoint> points,QPoint p,int distance=20)
    {
        for(int i=0;i<points.size();i++){
            if(abs(points[i].x-p.x())<distance&&(abs(points[i].y-p.y()))<distance){
                return (i+1);
            }
        }
        return 0;

    }
    QPoint map_point(QPoint p)
    {
        return QPoint(p.x()*img.width()/this->width(),p.y()*img.height()/this->height());
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
        for(QRect r:rects){
            img_painter.drawRect(r);
        }
        rects.clear();
        img_painter.setPen(red_pen1());
        cnt=0;
        // prt(info,"start draw-> %s",cfg.data().str().data());
        for(DetectRegionInputData p:cfg.DetectRegion){
            // prt(info,"p-> %s",p.data().str().data());
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

    void timeout()
    {
        this->update();
    }
    void mouseMoveEvent(QMouseEvent *e)
    {
        QPoint p1=map_point(e->pos());

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
    }
    void mousePressEvent(QMouseEvent *e)
    {


        vector <DetectRegionInputData >detect_regions;
        detect_regions.assign(cfg.DetectRegion.begin(),cfg.DetectRegion.end());
        ;
        for(int i=0;i<detect_regions.size();i++){
            vector <VdPoint> pnts(detect_regions[i].ExpectedAreaVers.begin(),detect_regions[i].ExpectedAreaVers.end());
            int point_index=match_point(pnts,map_point(e->pos()));
            if(point_index>0){
                ver_picked=true;
                selected_point_index=point_index;
                selected_region_index=i+1;
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
            ver_picked=false;
        }
    }
private:
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
    void cam_data_change(CameraInputData ,QWidget *w);
    void reshape_region(int region_index ,QRect rct,QWidget *w);
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
    QPoint maped_point;
    int selected_region_index;
    int selected_point_index;
    int cnt;
    vector <QRect> rects;
    QTimer *tick_timer;
    int timestamp;
};

#endif // PLAYERWIDGET_H
