#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLayout"
#include "playerwidget.h"
#include "camera.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CameraInputData d;
    wgt=new PlayerWidget(d);
    ui->setupUi(this);
    ui->centralWidget->layout()->addWidget(wgt);
}

MainWindow::~MainWindow()
{
    delete ui;
}
