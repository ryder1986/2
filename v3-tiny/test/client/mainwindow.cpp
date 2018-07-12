#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&searcher,SIGNAL(find_ip(QString)),this,SLOT(ip_found(QString)));
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
    clt.get_config();
}
