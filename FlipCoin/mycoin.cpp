#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString coinImg)
{
    QPixmap pix;
    bool ret = pix.load(coinImg);
    if(!ret)
    {
        QString str =QString("加载图片路径：%1失败").arg(coinImg);
        return ;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //定时器初始化
    time1 =new QTimer(this);
    time2 =new QTimer(this);

    //监听正反面的信号，并且翻转金币
    connect(time1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str =QString(":/resource/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;
            time1->stop();
        }
    });

    //监听反面--正面 的信号，并且翻转金币
    connect(time2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str =QString(":/resource/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了   将max 重置
        if(this->max<this->min)
        {
            this->max=8;
            isAnimation=false;
            time2->stop();
        }

    });
}

void MyCoin::changeFlag()
{
    if(this->flag)//正面翻反面
    {
        time1->start(30);
        this->isAnimation=true;//开始做动画
        this->flag=false;
    }
    else //反面执行下面代码
    {
        time2->start(30);
        this->isAnimation=true;//开始做动画
        this->flag=true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation|| this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}


















