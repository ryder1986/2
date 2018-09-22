/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_text;
    QGridLayout *gridLayout;
    QPushButton *pushButton_getconfig;
    QComboBox *comboBox_cameras;
    QLineEdit *lineEdit_getconfig;
    QPlainTextEdit *plainTextEdit_recive;
    QPushButton *pushButton_send;
    QComboBox *comboBox_search;
    QPushButton *pushButton_setconfig;
    QPushButton *pushButton_recive;
    QPlainTextEdit *plainTextEdit_send;
    QLineEdit *lineEdit_addcam;
    QPushButton *pushButton_delcam;
    QPushButton *pushButton_search;
    QPushButton *pushButton_addcam;
    QLineEdit *lineEdit_delcam;
    QLineEdit *lineEdit_default_url;
    QLineEdit *lineEdit_setconfig;
    QLabel *labe_default_url;
    QPushButton *pushButton_connect;
    QLineEdit *lineEdit_fixedip;
    QGroupBox *groupBox_video;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_stop;
    QWidget *widget_video;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_video;
    QPushButton *pushButton_start;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(796, 730);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox_text = new QGroupBox(centralWidget);
        groupBox_text->setObjectName(QStringLiteral("groupBox_text"));
        groupBox_text->setMaximumSize(QSize(400, 16777215));
        gridLayout = new QGridLayout(groupBox_text);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton_getconfig = new QPushButton(groupBox_text);
        pushButton_getconfig->setObjectName(QStringLiteral("pushButton_getconfig"));

        gridLayout->addWidget(pushButton_getconfig, 5, 1, 1, 1);

        comboBox_cameras = new QComboBox(groupBox_text);
        comboBox_cameras->setObjectName(QStringLiteral("comboBox_cameras"));

        gridLayout->addWidget(comboBox_cameras, 2, 0, 1, 2);

        lineEdit_getconfig = new QLineEdit(groupBox_text);
        lineEdit_getconfig->setObjectName(QStringLiteral("lineEdit_getconfig"));

        gridLayout->addWidget(lineEdit_getconfig, 5, 0, 1, 1);

        plainTextEdit_recive = new QPlainTextEdit(groupBox_text);
        plainTextEdit_recive->setObjectName(QStringLiteral("plainTextEdit_recive"));

        gridLayout->addWidget(plainTextEdit_recive, 4, 0, 1, 1);

        pushButton_send = new QPushButton(groupBox_text);
        pushButton_send->setObjectName(QStringLiteral("pushButton_send"));

        gridLayout->addWidget(pushButton_send, 3, 1, 1, 1);

        comboBox_search = new QComboBox(groupBox_text);
        comboBox_search->setObjectName(QStringLiteral("comboBox_search"));

        gridLayout->addWidget(comboBox_search, 0, 0, 1, 1);

        pushButton_setconfig = new QPushButton(groupBox_text);
        pushButton_setconfig->setObjectName(QStringLiteral("pushButton_setconfig"));

        gridLayout->addWidget(pushButton_setconfig, 6, 1, 1, 1);

        pushButton_recive = new QPushButton(groupBox_text);
        pushButton_recive->setObjectName(QStringLiteral("pushButton_recive"));

        gridLayout->addWidget(pushButton_recive, 4, 1, 1, 1);

        plainTextEdit_send = new QPlainTextEdit(groupBox_text);
        plainTextEdit_send->setObjectName(QStringLiteral("plainTextEdit_send"));

        gridLayout->addWidget(plainTextEdit_send, 3, 0, 1, 1);

        lineEdit_addcam = new QLineEdit(groupBox_text);
        lineEdit_addcam->setObjectName(QStringLiteral("lineEdit_addcam"));

        gridLayout->addWidget(lineEdit_addcam, 7, 0, 1, 1);

        pushButton_delcam = new QPushButton(groupBox_text);
        pushButton_delcam->setObjectName(QStringLiteral("pushButton_delcam"));

        gridLayout->addWidget(pushButton_delcam, 9, 1, 1, 1);

        pushButton_search = new QPushButton(groupBox_text);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));

        gridLayout->addWidget(pushButton_search, 0, 1, 1, 1);

        pushButton_addcam = new QPushButton(groupBox_text);
        pushButton_addcam->setObjectName(QStringLiteral("pushButton_addcam"));

        gridLayout->addWidget(pushButton_addcam, 7, 1, 1, 1);

        lineEdit_delcam = new QLineEdit(groupBox_text);
        lineEdit_delcam->setObjectName(QStringLiteral("lineEdit_delcam"));

        gridLayout->addWidget(lineEdit_delcam, 9, 0, 1, 1);

        lineEdit_default_url = new QLineEdit(groupBox_text);
        lineEdit_default_url->setObjectName(QStringLiteral("lineEdit_default_url"));

        gridLayout->addWidget(lineEdit_default_url, 12, 0, 1, 1);

        lineEdit_setconfig = new QLineEdit(groupBox_text);
        lineEdit_setconfig->setObjectName(QStringLiteral("lineEdit_setconfig"));

        gridLayout->addWidget(lineEdit_setconfig, 6, 0, 1, 1);

        labe_default_url = new QLabel(groupBox_text);
        labe_default_url->setObjectName(QStringLiteral("labe_default_url"));
        labe_default_url->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(labe_default_url, 12, 1, 1, 1);

        pushButton_connect = new QPushButton(groupBox_text);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));

        gridLayout->addWidget(pushButton_connect, 1, 1, 1, 1);

        lineEdit_fixedip = new QLineEdit(groupBox_text);
        lineEdit_fixedip->setObjectName(QStringLiteral("lineEdit_fixedip"));

        gridLayout->addWidget(lineEdit_fixedip, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_text, 0, 0, 1, 1);

        groupBox_video = new QGroupBox(centralWidget);
        groupBox_video->setObjectName(QStringLiteral("groupBox_video"));
        gridLayout_2 = new QGridLayout(groupBox_video);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_stop = new QPushButton(groupBox_video);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));

        gridLayout_2->addWidget(pushButton_stop, 2, 0, 1, 1);

        widget_video = new QWidget(groupBox_video);
        widget_video->setObjectName(QStringLiteral("widget_video"));
        verticalLayout = new QVBoxLayout(widget_video);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_video = new QGridLayout();
        gridLayout_video->setSpacing(6);
        gridLayout_video->setObjectName(QStringLiteral("gridLayout_video"));

        verticalLayout->addLayout(gridLayout_video);


        gridLayout_2->addWidget(widget_video, 0, 0, 1, 1);

        pushButton_start = new QPushButton(groupBox_video);
        pushButton_start->setObjectName(QStringLiteral("pushButton_start"));

        gridLayout_2->addWidget(pushButton_start, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_video, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 796, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox_text->setTitle(QApplication::translate("MainWindow", "text_box", Q_NULLPTR));
        pushButton_getconfig->setText(QApplication::translate("MainWindow", "get config", Q_NULLPTR));
        pushButton_send->setText(QApplication::translate("MainWindow", "send", Q_NULLPTR));
        pushButton_setconfig->setText(QApplication::translate("MainWindow", "set config", Q_NULLPTR));
        pushButton_recive->setText(QApplication::translate("MainWindow", "clear", Q_NULLPTR));
        lineEdit_addcam->setText(QApplication::translate("MainWindow", "rtsp://192.168.1.95:554/av0_1", Q_NULLPTR));
        pushButton_delcam->setText(QApplication::translate("MainWindow", "del cam", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("MainWindow", "search", Q_NULLPTR));
        pushButton_addcam->setText(QApplication::translate("MainWindow", "add cam", Q_NULLPTR));
        lineEdit_delcam->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        lineEdit_default_url->setText(QApplication::translate("MainWindow", "rtsp://192.168.1.95:554/av0_1", Q_NULLPTR));
        labe_default_url->setText(QApplication::translate("MainWindow", "default url", Q_NULLPTR));
        pushButton_connect->setText(QApplication::translate("MainWindow", "connect", Q_NULLPTR));
        lineEdit_fixedip->setText(QApplication::translate("MainWindow", "16.208.21.86", Q_NULLPTR));
        groupBox_video->setTitle(QApplication::translate("MainWindow", "video_box", Q_NULLPTR));
        pushButton_stop->setText(QApplication::translate("MainWindow", "stop all", Q_NULLPTR));
        pushButton_start->setText(QApplication::translate("MainWindow", "start all", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
