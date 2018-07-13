#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <QMutex>
#include <QPainter>
#include "camera.h"
#include "videosource.h"
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
    ;
        bool ret=src->get_frame(bgr_frame);
        if(ret){
            cvtColor(bgr_frame,rgb_frame,CV_BGR2RGB);
            img=QImage((const uchar*)(rgb_frame.data),
                       rgb_frame.cols,rgb_frame.rows,
                       QImage::Format_RGB888);
            img.bits();

        }
       // return img;

    }

protected:
    void paintEvent(QPaintEvent *)
    {
        lock.lock();
        QPainter painter(this);
        QBrush blue_brush_trans(QColor(0,222,200,255));
        //        // blue_brush_trans.setStyle(Qt::BrushStyle);
        painter.setBrush(blue_brush_trans);

        QPen pen(blue_brush_trans,200);
        painter.setPen(pen);
        get_img();
        if(!img.isNull()){
            prt(info,"%d %d",img.width(),img.height());
            //  painter.drawImage(QRect(0,0,this->width(),this->height()),img);
           // painter.drawImage(QRect(0,0,960,540),img);
          //  QPoint p(100,100);
           // painter.drawEllipse(p,10+loop++,10);

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

signals:
    void selected(PlayerWidget *w);
    void data_changed();
    void alg_changed(int index);
private:
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
};

#endif // PLAYERWIDGET_H
