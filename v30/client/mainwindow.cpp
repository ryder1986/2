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
    std::thread td(bind(&MainWindow::recv_rst,this));
    td.detach();

}

MainWindow::~MainWindow()
{
    delete ui;
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
    cmd=App::Operation::GET_CONFIG;
    clt.get_config();
}

void MainWindow::on_pushButton_start_clicked()
{
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
}

void MainWindow::on_pushButton_addcam_clicked()
{
    clt.add_camera(ui->lineEdit_addcam->text().toUtf8().data(),cfg.CameraData.size());
}

void MainWindow::on_pushButton_delcam_clicked()
{
    int index=ui->lineEdit_delcam->text().toInt();
    clt.del_camera(index);
}
