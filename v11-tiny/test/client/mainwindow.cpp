#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "playerwidget.h"
#include <thread>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget *w=new QWidget(this);
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
    //clt.get_config();
    clt.send(ui->plainTextEdit_send->toPlainText().toUtf8());
    //string str("app_op:get_config");
    // clt.send("{\"app_op\"\:\"get config\"\"}");
    //  clt.send(str.data());
}

void MainWindow::on_pushButton_recive_clicked()
{
    ui->plainTextEdit_recive->clear();
}



void MainWindow::on_pushButton_getconfig_clicked()
{
//    PlayerWidget *w=new PlayerWidget(cfg.cameras[0]);
//    ui->groupBox_video->layout()->addWidget(w);
 //   clt.send("{\"app_op\"\:\"get config\"\"}");
    clt.get_config();
}

void MainWindow::on_pushButton_start_clicked()
{
    start_config();
}

void MainWindow::on_pushButton_stop_clicked()
{
    stop_config();
}

void MainWindow::on_pushButton_setconfig_clicked()
{
    clt.set_config(ui->lineEdit_setconfig->text());
}
