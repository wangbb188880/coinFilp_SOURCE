#include "mainscene.h"
#include "ui_mainscene.h"
#include<QAction>
#include<QPainter>
#include"mypushbutton.h"
#include<QString>
#include<QPushButton>
#include<QDebug>
#include<QPainter>
#include<QTimer>
#include<QThread>
#include<QSound>

MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));
    this->setWindowTitle("王爸爸带你翻金币");
    leaveScene =new ChooseLeaveScene(this);
    connect(leaveScene,&ChooseLeaveScene::sendBackSignal,[=](){
//        QTimer::singleShot(500,this,[=](){
//            leaveScene->hide();
//            this->show();
//        });
        this->setGeometry(leaveScene->geometry());
        QThread::msleep(300);
        leaveScene->hide();
        this->show();
    });
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    myPushButton * startBnt=new myPushButton(":/resource/MenuSceneStartButton.png");
    QTimer * time1= new QTimer(this);
    startBnt->setParent(this);
    startBnt->move(this->width()/2-startBnt->width()/2,this->height()*0.7);
    QSound *mainsceneSound=new QSound(":/resource/TapButtonSound.wav",this);
    connect(startBnt,&myPushButton::clicked,[=](){
        //播放音乐
        mainsceneSound->play();
        startBnt->zoom1();//弹跳
        startBnt->zoom2();
        time1->start(500);
        connect(time1,&QTimer::timeout,[=](){
            //设置选择关卡场景的位置
            leaveScene->setGeometry(this->geometry());
            this->hide();
            leaveScene->show();
            time1->stop();

        });

    });


}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *event)
{
    //重写画图事件
    QPainter  painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/resource/PlayLevelSceneBg.png"));
    QPixmap pix(":/resource/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,35,pix);


}
