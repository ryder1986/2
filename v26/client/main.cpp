#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    vector <int> aaa;
    aaa.push_back(1);
//    for(int t:aaa){
//        qDebug()<<t<<endl;
//    }
    return a.exec();
}
