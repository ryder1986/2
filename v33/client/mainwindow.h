#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QtNetwork>
#include "tool.h"
#include <QThread>
#include "datapacket.h"
#include "app.h"
class Client : public QObject
{
    QByteArray tmp_msg;
    Q_OBJECT
public:
    char buf[2000];
    Client()
    {
        tmp_msg.clear();
        server_ip.clear();
        tcp_socket=new QTcpSocket();
        in.setDevice(tcp_socket);
        in.setVersion(QDataStream::Qt_1_0);
        connect(tcp_socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
        connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(handle_server_msg()),Qt::DirectConnection);
        connect(tcp_socket,SIGNAL(connected()),this,SLOT(handle_connected()),Qt::DirectConnection);
    }
    ~Client()
    {
        delete tcp_socket;
    }
    void get_config()
    {
        RequestPkt e(App::Operation::GET_CONFIG,0,JsonPacket());
        bool ret= send(e.data().str());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }
    void set_config(QString data)
    {
        string str=data.toStdString().data();
        JsonPacket pkt_tmp(str);
        RequestPkt e(App::Operation::SET_CONFIG,0,pkt_tmp);
        bool ret= send(e.data().str());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }
    void add_camera(string url,int index)
    {
        string SelectedProcessor="c4";

        vector <VdPoint>ExpectedAreaVers;
        ExpectedAreaVers.push_back(VdPoint(0,0));
        ExpectedAreaVers.push_back(VdPoint(640,0));
        ExpectedAreaVers.push_back(VdPoint(640,480));
        ExpectedAreaVers.push_back(VdPoint(0,480));
        JsonPacket ProcessorData;

        // DummyProcessor
        DetectRegionInputData rdata(ProcessorData,SelectedProcessor,ExpectedAreaVers);
        vector<JsonPacket> rs;
        rs.push_back(rdata.data());
        CameraInputData data(rs,url);
        RequestPkt pkt(App::Operation::INSERT_CAMERA,index,data.data());
        bool ret= send(pkt.data().str());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }
    void del_camera(int index)
    {
        RequestPkt pkt(App::Operation::DELETE_CAMERA,index,JsonPacket());
        bool ret= send(pkt.data().str());//talk to server
        if(!ret){
            prt(info,"fail send");
        }

    }
    void send_cmd(JsonPacket pkt)
    {
        //        RequestPkt pkt(App::Operation::MODIFY_CAMERA,index,JsonPacket());
        bool ret= send(pkt.str());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }

#if 0
    void get_config()
    {

        //    int request_length=Pvd::encode_configuration_request(buf);//encoder buffer
        QJsonObject obj;
        obj["type"]=Pvd::GET_CONFIG;
        QJsonDocument doc(obj);

        bool ret= send(doc.toJson());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
        //    return rst.remove(0,Pvd::HEAD_LENGTH);//TODO:get the ret value;
    }
    void set_config(QByteArray cfg)
    {
        QJsonDocument doc_config=QJsonDocument::fromJson(cfg);
        QJsonObject obj;
        obj["type"]=Pvd::SET_CONFIG;
        obj["config"]=doc_config.object();
        QJsonDocument doc(obj);
        bool ret= send(doc.toJson());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }


    void set_alg(QByteArray cfg , int index)
    {
        QJsonDocument doc_config=QJsonDocument::fromJson(cfg);
        QJsonObject obj;
        obj["type"]=Pvd::MOD_CAMERA_ALG;
        obj["channel"]=doc_config.array();
        obj["cam_index"]=index;
        QJsonDocument doc(obj);
        bool ret= send(doc.toJson());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }
    void focus_camera(int cam_index)
    {
        //    int request_length=Pvd::encode_configuration_request(buf);//encoder buffer
        QJsonObject obj;
        obj["type"]=Pvd::CAM_OUTPUT_OPEN;
        obj["cam_index"]=cam_index;
        QJsonDocument doc(obj);

        //   bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        bool ret= send(doc.toJson());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }

    void disfocus_camera(int cam_index)
    {
        //    int request_length=Pvd::encode_configuration_request(buf);//encoder buffer
        QJsonObject obj;
        obj["type"]=Pvd::CAM_OUTPUT_CLOSE;
        obj["cam_index"]=cam_index;
        QJsonDocument doc(obj);

        //  bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        bool ret= send(doc.toJson());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }

    void add_camera(QString url,int index)
    {
        QJsonObject obj_cam;
        obj_cam["url"]=url;
        add_camera(obj_cam,index);
    }

    void add_camera(QJsonObject obj_cam,int index)
    {
        QJsonObject obj;
        obj["type"]=Pvd::INSERT_CAMERA;
        obj["cam_index"]=index;
        obj["camera"]=obj_cam;
        QJsonDocument doc(obj);
        int len=doc.toJson().length();
        //  bool ret= send(doc.toJson().data(),len);//talk to server
        bool ret= send(doc.toJson());//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }
    void send_msg(QByteArray ba)
    {
        // bool ret= send(ba.data(),ba.length());//talk to server
        bool ret= send(ba);//talk to server
        if(!ret){
            prt(info,"fail send");
        }
    }

    //    void add_camera(QByteArray cam_cfg,QString url)
    //    {

    //    }

    void del_camera(int index)
    {
        QJsonObject obj;
        obj["type"]=Pvd::DELETE_CAMERA;
        obj["cam_index"]=index;
        QJsonDocument doc(obj);

        // bool ret= send(doc.toJson().data(),doc.toJson().length());//talk to server
        bool ret= send(doc.toJson());//talk to server
        if(!ret){
            prt(info,"fail send");
        }

    }
    void mod_camera(QByteArray new_camera_config,int index)
    {

    }
#endif
    int count_begin_symbol(QByteArray ba)
    {
        char *tmp=ba.data();
        int sz=ba.size();
        int ret=0;
        int i;
        for( i=0;i<sz;i++){
            if(tmp[i]=='{'){
                ret++;
            }
        }
        return ret;
    }
    int count_end_symbol(QByteArray ba)
    {
        char *tmp=ba.data();
        int sz=ba.size();
        int ret=0;
        int i;
        for( i=0;i<sz;i++){
            if(tmp[i]=='}'){
                ret++;
            }
        }
    }
    void find_pos(QByteArray ba,int &endpos,int &left)
    {

    }
    bool try_get_obj_buf(QByteArray src,QByteArray &dst)
    {
        int ret=false;
        int stack=0;
        char *p_tmp=src.data();
        bool flg=false;
        //    bool flg_real_end=false;
        //char *p_start=src.data();
        dst.clear();
        dst.append(src);
        int i;
        if(count_begin_symbol(src)>0){
            for(i=0;i<src.size();i++){
                if(p_tmp[i]=='{')
                {
                    stack++;
                    flg=true;
                }
                if(p_tmp[i]=='}')
                    stack--;


                if(stack==0&&flg)
                {

                    break;
                }

            }
            if(i<src.size()){
                ret=true;
                if(src[i+1]=='\n')
                    dst.truncate(i+2);
                else
                    dst.truncate(i+i);
            }
        }
        return ret;
    }

    //dst:a sting which contain a compelete json object
    //src:a slice ofstream buffer
    //tmp_msg:last slice of buffer(maybe begining of json string)
    bool get_valid_buf(QByteArray &src,QByteArray &dst)
    {
        if(try_get_obj_buf(src,dst)){
            src.remove(0,dst.size());
            return true;
        }
        return false;

    }

public slots:
    void handle_connected()
    {
        prt(info,"connected");
        emit connect_done();
    }


    void handle_server_msg()
    {

#if 0
        ret_ba=tcp_socket->readAll();
        QByteArray valid_buf;
        valid_buf.clear();
        tmp_msg.append(ret_ba);
        while(get_valid_buf(tmp_msg,valid_buf)) {
            DataPacket pkt(string(valid_buf.data()));
            prt(info,"get %d bytes ",valid_buf.size());
            if(valid_buf.size()>0)
                need_read=true;
            int op=pkt.get_int("type");
            emit get_ret(pkt.data().data());
            switch(op)
            {
            case Pvd::GET_CONFIG:
            {
                emit signal_get_config_done(true,DataPacket(pkt.get_value("config")).data());
            }
                break;
            case Pvd::NEED_UPDATE:
                need_update_config();
                break;
            default:break;
            }
        }
#else
        tmp_msg.clear();
        ret_ba=tcp_socket->readAll();
        QByteArray valid_buf;
        valid_buf.clear();
        tmp_msg.append(ret_ba);
        while(get_valid_buf(tmp_msg,valid_buf)) {
            DataPacket pkt(string(valid_buf.data()));
            prt(info,"get %d bytes ** %s ** ",valid_buf.size(),valid_buf.data());
            if(valid_buf.size()>0)
                need_read=true;
            prt(info,"left  %d bytes ** %s ** ",tmp_msg.size(),tmp_msg.data());

            emit server_msg(pkt.data().data());
        }

#endif
    }


    void connect_to_server(QString ip)
    {
        if(ip.size()){
            //  prt(info,"state %d ",tcp_socket->state());
            if(tcp_socket->state()==QAbstractSocket::ConnectedState)
                tcp_socket->disconnectFromHost();
            //     prt(info,"new ip %s connect (%d)",server_ip.toStdString().data(),tcp_socket->state());
            if(ip==server_ip){
                prt(info,"reconnecting %s",server_ip.toStdString().data());
                tcp_socket->connectToHost(server_ip,12345);
            }else{
                prt(info,"connecting %s",ip.toStdString().data());
                server_ip=ip;
                tcp_socket->connectToHost(server_ip,12345);
            }

        }else{
        }
    }
    void  displayError(QAbstractSocket::SocketError socketError)
    {
        prt(info,"err when connecting to server");
        switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            qDebug()<<"1";
            break;
        case QAbstractSocket::ConnectionRefusedError:
            qDebug()<<"1";
            break;
        default:
            qDebug()<<"1";
        }
    }


signals:
    void signal_get_config_done(bool,string);
    void need_update_config();
    void connect_done();
    void get_ret(QByteArray);
    void send_done(QByteArray);
    void server_msg(QString);
public:
    bool send(const QByteArray ba)
    {
        emit send_done(ba);
        bool ret=false;
        int write_bytes=0;
        int len=ba.length();
        write_bytes=tcp_socket->write(ba.data(),ba.length());
        bool flush_ret=tcp_socket->flush();//TODO,not work for flush
        if(flush_ret){
            prt(info,"flush ok");
        }else{
            prt(info,"flush err");
        }

        if(write_bytes!=len){
            prt(info,"send %d bytes in state %d , %d bytes left",write_bytes,tcp_socket->state(),len-write_bytes);
        }else{
            ret=true;
        }
        return ret;
    }
    bool send(const string ba)
    {
        emit send_done(QByteArray(ba.data()));
        bool ret=false;
        int write_bytes=0;
        int len=ba.length();
        write_bytes=tcp_socket->write(ba.data(),ba.length());
        bool flush_ret=tcp_socket->flush();//TODO,not work for flush
        if(flush_ret){
            prt(info,"send ok");
        }else{
            prt(info,"send err");
        }

        if(write_bytes!=len){
            prt(info,"send %d bytes in state %d , %d bytes left",write_bytes,tcp_socket->state(),len-write_bytes);
        }else{
            ret=true;
        }
        return ret;
    }
private:
    QString server_ip;
    QTcpSocket *tcp_socket;
    QDataStream in;
    QByteArray ret_ba;
    bool need_read;
};

class ServerReplyCheckRouting : public QObject
{
    Q_OBJECT

public slots:
    void check_reply(    QUdpSocket *udp_skt_find_server) {
        QString str;
        str.clear();
        int try_times=1000;
        while(try_times--){
            if(udp_skt_find_server->hasPendingDatagrams()){
                datagram.resize((udp_skt_find_server->pendingDatagramSize()));
                udp_skt_find_server->readDatagram(datagram.data(),datagram.size());
                prt(info,"get server info : %s",datagram.data());
                server_ip.clear();
                server_ip.append(datagram.split(',')[0]);
                prt(info,"ip : %s",server_ip.toStdString().data());
                ip_list.append(server_ip);
                emit resultReady(server_ip);
            }else{
                //      prt(info,"searching");
            }
            QThread::msleep(10);
        }
    }

signals:
    void resultReady(  QString result);
private:
    //  QUdpSocket *udp_skt_find_server;

    QByteArray datagram;
    QString server_ip;
    QStringList ip_list;
};

class ServerInfoSearcher : public QObject{
    Q_OBJECT
    QThread check_thread;
    ServerReplyCheckRouting *p_checker;

public:
    ServerInfoSearcher()
    {

        udp_skt_find_server=new QUdpSocket(this);
        udp_skt_find_server->bind(12347,QUdpSocket::ShareAddress);
        //     connect(udp_skt_find_server,SIGNAL(readyRead()),this,SLOT(get_reply()),Qt::QueuedConnection);

        //   connect();

        p_checker=new ServerReplyCheckRouting;
        p_checker->moveToThread(&check_thread);
        connect(&check_thread,&QThread::finished,p_checker,&QObject::deleteLater);
        connect(this,SIGNAL(begin_search(QUdpSocket*)),p_checker,SLOT(check_reply(QUdpSocket*)),Qt::QueuedConnection);
        connect(p_checker,SIGNAL(resultReady(QString)),this,SLOT(ip_found(QString)),Qt::QueuedConnection);
    }
    ~ServerInfoSearcher()
    {
        check_thread.quit();
        check_thread.wait();
    }
    void broadcast_info()
    {
        QByteArray b;
        b.append("pedestrian");
        udp_skt_find_server->writeDatagram(b.data(), b.size(),
                                           QHostAddress::Broadcast, 12348);
        prt(info,"finding server ...");

    }
    void search()
    {

        check_thread.start();
        emit begin_search(udp_skt_find_server);
    }

    void search_device()
    {
        ip_list.clear();
        broadcast_info();
        search();
        //   p_find_server_thread=new std::thread(find_server);
        //   QThread::msleep(3000);

    }
    QStringList search_rst()
    {
        return ip_list;
    }
    static void find_server()
    {
        prt(info," find server thread");
        int times=10;
        while(times--){

        }
    }
signals:
    void begin_search( QUdpSocket *udp_skt_find_server);
    void find_ip(QString ip);

public slots:
    void ip_found(QString ip)
    {
        qDebug()<<ip;
        // ip_list.append(ip);
        emit find_ip(ip);
    }
private :
    QUdpSocket *udp_skt_find_server;

    QByteArray datagram;
    QString server_ip;
    QStringList ip_list;
};

#include "ui_mainwindow.h"
#include     "playerwidget.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
    mutex thread_lock;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void start_config()
    {
        thread_lock.lock();
        for(CameraInputData d:cfg.CameraData)
        {
            ui->comboBox_cameras->addItem(d.Url.data());
            PlayerWidget *player=new PlayerWidget(d);
            players.push_back(player);
            ui->groupBox_video->layout()->addWidget(player);
            connect(player,SIGNAL(cam_data_change(CameraInputData,QWidget*)),\
                    this,SLOT(generate_current_config(CameraInputData,QWidget*)));

            connect(player,SIGNAL(signal_camera(PlayerWidget*,int,JsonPacket)),\
                    this,SLOT(slot_camera(PlayerWidget*,int,JsonPacket)));
            connect(player,SIGNAL(signal_region(PlayerWidget*,int,int,JsonPacket)),\
                    this,SLOT(slot_region(PlayerWidget*,int,int,JsonPacket)));

        }
        prt(info,"%s",cfg.data().str().data());
        printf("$$$$$ %s $$$$$\n",cfg.data().str().data());
        thread_lock.unlock();
    }
    void stop_config()
    {
        thread_lock.lock();
        ui->comboBox_cameras->clear();
        for(PlayerWidget *w:players){
            ui->groupBox_video->layout()->removeWidget(w);
            w->hide();
            delete w;
        }
        players.clear();
        thread_lock.unlock();
    }

    void recv_rst()
    {
        int fd= Socket::UdpCreateSocket(12349);
        int ret;
        static  char buf[1000];
        while(true){
            if(!connected)
                continue;
            ret= Socket::RecvDataByUdp(fd,buf,1000);
            string str(buf);
            JsonPacket p(str);
            //prt(info,"recving %s",p.str().data());
            AppOutputData rst(p);
            //prt(info,"recving %s",rst.data().str().data());
            int cam_index=rst.CameraIndex;
            //    CameraInputData camera_cfg=cfg.CameraData[cam_index];

            thread_lock.lock();
            //prt(info,"recving cam %d",cam_index);
            if(players.size()<cam_index)
            {
                thread_lock.unlock();
                continue;
            }
            PlayerWidget *w= players[cam_index-1];
            w->set_overlay(rst.CameraOutput);
            thread_lock.unlock();
        }
    }
private slots:
    void slot_camera(PlayerWidget *w,int op,JsonPacket data)
    {
        int index= ui->groupBox_video->layout()->indexOf(w);
        prt(info,"get sig from player %d",index);
       // thread_lock.lock();
        stop_config();
        switch(op){
        case Camera::OP::INSERT_REGION:
        {
            RequestPkt pkt(App::Operation::MODIFY_CAMERA,index,RequestPkt(data).data());
            clt.send_cmd(pkt.data());
            break;
        }
        default:break;
        }
       // thread_lock.unlock();
    }
    void slot_region(PlayerWidget *w,int region_index,int op,JsonPacket data)
    {
        int index= ui->groupBox_video->layout()->indexOf(w);
        prt(info,"get sig from player %d",index);

    }
    void generate_current_config(CameraInputData d,QWidget* w)
    {
        //   int index= ui->gridLayout_video->indexOf(w);
        int index= ui->groupBox_video->layout()->indexOf(w);
        prt(info,"wgt index %d",index);
        cfg.modify_camera(d.data(),index);
        //  ui->lineEdit_setconfig->setText(cfg.data().str().data());
        // ui->lineEdit_setconfig->clear();
        ui->lineEdit_setconfig->setText(cfg.data().str().data());
        //prt(info,"%d",d.detect_regions[0].poly_vers[0].x);
    }

    void ip_found(QString ip)
    {
        ui->comboBox_search->addItem(ip);
    }
    void server_msg(QString msg)
    {
        ui->plainTextEdit_recive->setPlainText(msg);//show what we got
        string str(msg.toUtf8());
        //JsonPacket pkt(str);
        ReplyPkt event(str);
        //  int op=pkt.get("op").to_int();
        prt(info,"str :",str.data());
        prt(info,"cmd :%d",cmd);
        switch(cmd){
        case App::Operation::GET_CONFIG:
        {
            //cfg=pkt.get("ret");
            cfg=event.Ret;
            prt(info,"get config :%s",cfg.data().str().data());
            ui->lineEdit_getconfig->setText(cfg.data().str().data());
            prt(info,"stopping");
            stop_config();
            prt(info,"starting");
            start_config();
            prt(info,"start done");
            connected=true;
            break;
        }
        default:break;
        }
    }
    void on_pushButton_search_clicked();

    void on_comboBox_search_activated(const QString &arg1);

    void on_pushButton_send_clicked();

    void on_pushButton_recive_clicked();


    void on_pushButton_getconfig_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_stop_clicked();


    void on_pushButton_setconfig_clicked();

    void on_pushButton_addcam_clicked();

    void on_pushButton_delcam_clicked();

private:
    Ui::MainWindow *ui;
    ServerInfoSearcher searcher;
    Client clt;
    AppInputData cfg;
    vector <PlayerWidget *> players;
    int cmd;
    bool connected;
};

#endif // MAINWINDOW_H
