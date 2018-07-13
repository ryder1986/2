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
        delete src;
    }

    PlayerWidget(CameraData data)
    {
        loop=0;
        ver_picked=false;
        cfg=data;
        frame_rate=0;
        QTimer *t=new QTimer();
        connect(t,SIGNAL(timeout()),this,SLOT(timeout()));
        t->start(100);
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

        QPoint p1(   QPoint(points.front().x,points.front().y));
        QPoint p2( QPoint(points.back().x,points.back().y));
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
        QPainter painter(this);
        QBrush blue_brush_trans(QColor(0,222,200,255));
        // blue_brush_trans.setStyle(Qt::BrushStyle);
        painter.setBrush(blue_brush_trans);

        QPen pen(blue_brush_trans,200);
        painter.setPen(pen);
        get_img();
        //   img;
        QPainter img_painter(&img);
        QPoint p(100,100);
        img_painter.drawEllipse(p,10+loop++,10);
        // cfg.detect_regions
        //img_painter.drawPolyline();
        cnt=0;
        for(DetectRegionData p:cfg.detect_regions){

            draw_points(p.poly_vers,img_painter);
            //            for(VdPoint point:p.poly_vers){

            //                vers[cnt++]=QPoint(point.x,point.y);
            //            }
            //  pros.push_back(new PvdC4Processor(p));
            //        pros.push_back(new PvdMvncProcessor(p.get_pkt("pvd_c4")));
            // pros.push_back(new PvdHogProcessor(p.get_pkt("pvd_c4")));
        }
        // img_painter.drawPolygon(vers,cnt);
        if(!img.isNull()){
            //        prt(info,"%d %d",img.width(),img.height());
            painter.drawImage(QRect(0,0,this->width(),this->height()),img);
        }
        //        QPoint p(100,100);
        //        painter.drawEllipse(p,10+loop++,10);
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

        if(ver_picked){
            prt(info,"drag (region %d,point %d )to (%d,%d)",selected_region_index,selected_point_index,e->pos().x(),e->pos().y());
            if(selected_region_index>0&&selected_point_index>0){
                cfg.detect_regions[selected_region_index-1].poly_vers[selected_point_index-1].x=p1.x();
                cfg.detect_regions[selected_region_index-1].poly_vers[selected_point_index-1].y=p1.y();
            }
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

        ver_picked=false;
    }
private:
    //    inline bool close_enough(QPoint from,QPoint to,int distance=5)
    //    {
    //        if(abs(from.x()-to.x())<distance&&abs(from.y()-to.y())<distance)
    //            return true;
    //        else
    //            return false;
    //    }

signals:
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
};

#endif // PLAYERWIDGET_H
