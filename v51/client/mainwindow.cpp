#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playerwidget.h"
#include <thread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connected=false;
    ui->setupUi(this);
    connect(&searcher,SIGNAL(find_ip(QString)),this,SLOT(ip_found(QString)));
    connect(&clt,SIGNAL(server_msg(QString)),this,SLOT(server_msg(QString)));
    std::thread td(bind(&MainWindow::recv_server_output,this));
    td.detach();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recv_server_output()
{
    int fd= Socket::UdpCreateSocket(12349);
    int ret;
    static  char buf[10000];
    while(true){
        if(!connected)
            continue;
        ret= Socket::RecvDataByUdp(fd,buf,10000);
        //prt(info,"rget udp len %d",ret);
        string str(buf);
        JsonPacket p(str);
      //  prt(info,"recive output %d bytes --> %s",p.str().size(),p.str().data());
        AppOutputData rst(p);

        int cam_index=rst.CameraIndex;
        //    CameraInputData camera_cfg=cfg.CameraData[cam_index];

        thread_lock.lock();
        //prt(info,"recving cam %d",cam_index);
        if(players.size()<cam_index)
        {
            prt(info,"recving cam %d, our sz %d ",cam_index,players.size());
            thread_lock.unlock();
            continue;
        }
        PlayerWidget *w= players[cam_index-1];
        w->set_overlay(rst.CameraOutput);
        thread_lock.unlock();
    }
}

void MainWindow::slot_camera(PlayerWidget *w, int op, JsonPacket data)
{
    //int index= ui->groupBox_video->layout()->indexOf(w);
    int index= ui->gridLayout_video->indexOf(w)+1;
    prt(info,"handle player %d request",index);
    //  thread_lock.lock();
    switch(op){
    case Camera::OP::INSERT_REGION:
    {
        //stop_config();
        RequestPkt pkt(App::Operation::MODIFY_CAMERA,index,RequestPkt(data).data());
        clt.send_cmd(pkt.data());

        clt.get_config();
        break;
    }
    case Camera::OP::DELETE_REGION:
    {
        //stop_config();
        RequestPkt pkt(App::Operation::MODIFY_CAMERA,index,RequestPkt(data).data());
        clt.send_cmd(pkt.data());
        clt.get_config();
        break;
    }
    case Camera::OP::MODIFY_REGION:
    {
        RequestPkt pkt(App::Operation::MODIFY_CAMERA,index,RequestPkt(data).data());
        clt.send_cmd(pkt.data());
        clt.get_config();
        break;
    }
    case Camera::OP::CHANGE_URL:
    {
        JsonPacket p;
        // p.add("Url","rtsp://192.168.1.95:554/av0_1");
        p.add("Url",ui->lineEdit_default_url->text().toStdString());
        RequestPkt pkt_url(Camera::OP::CHANGE_URL,0,p);

        RequestPkt pkt(App::Operation::MODIFY_CAMERA,index,pkt_url.data());
        clt.send_cmd(pkt.data());
        clt.get_config();
        w->reset_url(string(ui->lineEdit_default_url->text().toStdString()));
        break;
    }
    default:break;
    }
    //   thread_lock.unlock();
}

void MainWindow::server_msg(QString msg)
{
    ui->plainTextEdit_recive->setPlainText(msg);//show what we got
    string str(msg.toUtf8());
    ReplyPkt event(str);
    switch(cmd){
    case App::Operation::GET_CONFIG:
    {
        cfg=event.Data;
        ui->lineEdit_getconfig->setText(cfg.data().str().data());
        connected=true;
        break;
    }
    default:break;
    }
}

void MainWindow::on_pushButton_search_clicked()
{
    ui->comboBox_search->clear();
    searcher.search_device();
}

void MainWindow::on_comboBox_search_activated(const QString &arg1)
{
    clt.connect_to_server(arg1);
}

void MainWindow::on_pushButton_send_clicked()
{
    clt.send(ui->plainTextEdit_send->toPlainText().toUtf8());
}

void MainWindow::on_pushButton_recive_clicked()
{
    ui->plainTextEdit_recive->clear();
}

void MainWindow::on_pushButton_getconfig_clicked()
{
    prt(info,"get server config");
    cmd=App::Operation::GET_CONFIG;
    clt.get_config();
}

void MainWindow::on_pushButton_start_clicked()
{
    prt(info,"restart with config");
    stop_config();
    start_config();
}

void MainWindow::on_pushButton_stop_clicked()
{
    stop_config();
}

void MainWindow::on_pushButton_setconfig_clicked()
{
    cmd=App::Operation::SET_CONFIG;
    clt.set_config(ui->lineEdit_setconfig->text());
    clt.get_config();
    stop_config();
}

void MainWindow::on_pushButton_addcam_clicked()
{
    prt(info,"add camera");
    clt.add_camera(ui->lineEdit_addcam->text().toUtf8().data(),cfg.CameraData.size());
    insert_camera(PlayerWidget::make_test_camera_data(ui->lineEdit_addcam->text().toStdString()));
}

void MainWindow::on_pushButton_delcam_clicked()
{
    prt(info,"del camera");
    int index=ui->lineEdit_delcam->text().toInt();
    clt.del_camera(index);
    delete_camera(index);
   // widget_del_camera(index);
}
