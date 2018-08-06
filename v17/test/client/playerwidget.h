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
        //   delete src;
    }

    PlayerWidget(CameraData data)
    {
        rects.clear();
        loop=0;
        ver_picked=false;
        cfg=data;
        frame_rate=0;
        tick_timer=new QTimer();
        connect(tick_timer,SIGNAL(timeout()),this,SLOT(timeout()));
        tick_timer->start(100);
        src=new VideoSource(data.url);
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
    void set_object_rect(QRect r)
    {
        lock.lock();
        rects.append(r);
        lock.unlock();
    }

    void  get_img()
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
        get_img();
        QPainter img_painter(&img);
        img_painter.setPen(blue_pen1());

        //        QPoint p(100,100);
        //        img_painter.drawEllipse(p,10+loop++,10);

        for(QRect r:rects){
            img_painter.drawRect(r);
        }
        rects.clear();
        img_painter.setPen(red_pen1());
        cnt=0;
        for(DetectRegionData p:cfg.detect_regions){
            draw_points(p.poly_vers,img_painter);
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
        //frame_rate++;
        //     prt(info,"frame rate :%d ",frame_rate);
        //frame_rate=0;
    }
    void mouseMoveEvent(QMouseEvent *e)
    {
        QPoint p1=map_point(e->pos());
   prt(info,"seting %d, picked %d , index1:%d ,index2:%d,size %d",e->pos().x(),ver_picked,\
       selected_region_index,selected_point_index,cfg.detect_regions.size());
        if(ver_picked){
          //  prt(info,"drag (region %d,point %d )to (%d,%d)",selected_region_index,selected_point_index,e->pos().x(),e->pos().y());
            if(selected_region_index>0&&selected_point_index>0&&\
                    selected_region_index<=cfg.detect_regions.size()){
                DetectRegionData r=cfg.detect_regions[selected_region_index-1];
                VdPoint p(p1.x(),p1.y());
                r.set_point(p,selected_point_index);

                prt(info,"set %d",r.poly_vers[0].x);

                cfg.set_region(r,selected_region_index);
                //                cfg.detect_regions[selected_region_index-1].poly_vers[selected_point_index-1].x=p1.x();
                //                cfg.detect_regions[selected_region_index-1].poly_vers[selected_point_index-1].y=p1.y();

            }
           // cfg.encode();
        }
    }
    void mousePressEvent(QMouseEvent *e)
    {


        vector <DetectRegionData >detect_regions=cfg.detect_regions;
        for(int i=0;i<detect_regions.size();i++){
            vector <VdPoint> pnts= detect_regions[i].poly_vers;
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

        //        if(e->pos(),cfg
        //        ver_picked=true;
    }
    void mouseReleaseEvent(QMouseEvent *e)
    {
        if(ver_picked){
            prt(info,"drag %d",cfg.detect_regions[0].poly_vers[0].x);

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
    //    inline bool close_enough(QPoint from,QPoint to,int distance=5)
    //    {
    //        if(abs(from.x()-to.x())<distance&&abs(from.y()-to.y())<distance)
    //            return true;
    //        else
    //            return false;
    //    }

signals:
    void cam_data_change(CameraData ,QWidget *w);
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
    //  QPainter painter;
    QList <QPoint> area_v;
    bool show_info;
    int channel_num;
    int poly_num;
    CameraData cfg;
    int loop;
    VideoSource *src;
    bool ver_picked;
    //   vector <vector<QPoint>>detect_regions;
    //QPoint vers[][POLY_VER_NUM];
    QPoint maped_point;
    int selected_region_index;
    int selected_point_index;
    int cnt;
    QList <QRect> rects;
    QTimer *tick_timer;
};

#endif // PLAYERWIDGET_H
