#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QTimer>
#include <QMutex>
#include <QPainter>
#include "camera.h"
class PlayerWidget : public QOpenGLWidget
{
    Q_OBJECT

public:

    ~PlayerWidget()
    {
    }

    PlayerWidget(CameraData data)
    {
        cfg=data;
        frame_rate=0;
        QTimer *t=new QTimer();
        connect(t,SIGNAL(timeout()),this,SLOT(timeout()));
        t->start(100);



    }
    void set_image(QImage img1)

    {
        lock.lock();
        img=img1;
        lock.unlock();
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

protected:
    void paintEvent(QPaintEvent *)
    {
        lock.lock();
//        QBrush blue_brush_trans(QColor(0,222,200,255));
//        // blue_brush_trans.setStyle(Qt::BrushStyle);
//        painter.setBrush(blue_brush_trans);

//        QPen pen(blue_brush_trans,200);
//        painter.setPen(p en);

//        // QThread::msleep(2000);
//        //            frame_rate++;
////        QPainter painter(this);
//        if(!img.isNull()){
//            painter.drawImage(QRect(0,0,this->width(),this->height()),img);


//        }
//        QPoint p(100,100);
//         painter.drawEllipse(p,10,10);
        lock.unlock();
    }
    void  initializeGL()
    {

    }

public slots:

    void timeout()
    {
    //    this->update();
        //frame_rate++;
        //     prt(info,"frame rate :%d ",frame_rate);
        frame_rate=0;
    }

signals:
    void selected(PlayerWidget *w);
    void data_changed();
    void alg_changed(int index);
private:
    QImage img;
    QString title;
    QMutex lock;
    int frame_rate;

    QPainter painter;
    QList <QPoint> area_v;
    bool show_info;
    int channel_num;
    int poly_num;
    CameraData cfg;

    //  QList <QPoint> points;
    //    QByteArray ba;
};

#endif // PLAYERWIDGET_H
