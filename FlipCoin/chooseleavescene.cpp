#include "chooseleavescene.h"
#include<QPixmap>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QLabel>
#include<QString>
#include<QSound>

ChooseLeaveScene::ChooseLeaveScene(QWidget *parent) : QMainWindow(parent)
{

    this->setWindowTitle("游戏关卡");
    this->setFixedSize(320,588);
    //创建菜单
    QMenuBar *bar =new QMenuBar(this);
    setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu =bar->addMenu("开始");
    //创建退出 菜单项
    QAction * quitAction=startMenu->addAction("退出");
    //点击退出 实现退出
    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });
    backBtn =new myPushButton(":/resource/BackButton.png/",":/resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //音乐
    QSound *chosesceneSound=new QSound(":/resource/TapButtonSound.wav",this);
    QSound *backSound=new QSound(":/resource/BackButtonSound.wav",this);
    connect(backBtn,&myPushButton::clicked,[=](){
   //     qDebug()<<"点击了呀";
        backSound->play();
        emit  this->sendBackSignal(this->num);//触发自定义信号
    });
    //制作关卡
    for ( int i=0;i<20;i++)
    {
        myPushButton*  menuBtn= new myPushButton(":/resource/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+ i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(menuBtn,&myPushButton::clicked,[=](){
            //播放音乐
            chosesceneSound->play();
            QString str = QString("您选择的是第 %1 关卡").arg(i+1);
            this->num=i+1;
           qDebug()<<str;

           playscene=new PlayScene(this->num);
           //设置游戏场景的初始位置
           playscene->setGeometry(this->geometry());
           this->hide();
           playscene->show();
           connect(playscene,&PlayScene::sendBack,[=](){
               this->setGeometry(playscene->geometry());
               backSound->play();
               delete playscene;
               playscene=nullptr;
               this->show();
           });
        });

        QLabel * label =new QLabel(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4 *70,130+i/4*70);
        //设置居中方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }


}

void ChooseLeaveScene::paintEvent(QPaintEvent *ev)
{
    QPainter painter (this);
    QPixmap pix ;
    pix.load(":/resource/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/resource/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
