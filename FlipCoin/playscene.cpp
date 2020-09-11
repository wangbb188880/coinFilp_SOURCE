#include "playscene.h"
#include<QDebug>
#include"mycoin.h"
#include<QLabel>
#include<QPropertyAnimation>
#include<QSound>
PlayScene::PlayScene(int num)
{
    this->num=num;
    this->setWindowTitle("游戏场景");
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/resource/Coin0001"));

    myPushButton * backBtn =new myPushButton(":/resource/BackButton.png/",":/resource/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //音乐制作
    QSound *backSound=new QSound(":/resource/BackButtonSound.wav",this);
    QSound *flipSound=new QSound(":/resource/ConFlipSound.wav",this);
    QSound *winSound=new QSound(":/resource/TapButtonSound.wav",this);

    connect(backBtn,&myPushButton::clicked,[=](){
        backSound->play();
        emit this->sendBack();
    });
    QLabel* label=new QLabel(this);
    QString str =QString("Leave : %1").arg(this->num);
    label->setText(str);
    label->setGeometry(30,this->height()-50,120,50);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);

    dataconfig =new dataConfig;
    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=dataconfig->mData[this->num][i][j];
        }
    }
    //做胜利的图片
    QLabel * winLabel = new QLabel(this);
    QPixmap supix;
    supix.load(":/resource/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,supix.width(),supix.height());
    winLabel->setPixmap(supix);
    winLabel->move((this->width()-supix.width())*0.5,-supix.height());

    //显示金币图案
    for (int i=0;i<4;i++)
    {
        for(int j=0 ;j<4 ;j++)
        {
            //绘制背景图片
            QLabel * bglabel = new  QLabel(this);
            QPixmap pix = QPixmap(":/resource/BoardNode.png");
            bglabel->setPixmap(pix);
            bglabel->setGeometry(0,0,pix.width(),pix.height());
            bglabel->move(57+i*50,200+j*50);

            QString str;
            if(gameArray[i][j]==1)
            {
                //显示金币
               str=":/resource/Coin0001.png";
            }
            else
            {
                str=":/resource/Coin0008.png";
            }

            //创建金币
            MyCoin* coin =new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];//1正面  0反面
            //将金币放到金币的二维数据中 以便于后期的维护
            coinBtn[i][j]=coin;
            //点击金币  进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //音乐
                flipSound->play();
                //禁用所有按钮图片
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        this->coinBtn[i][j]->isWin=true;
                    }
                }
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0? 1:0;
                //翻转周围硬币
                //延时翻转
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX +1 <=3)//右侧金币翻转
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0? 1:0;
                    }
                    //左侧周围金币翻转
                    if(coin->posX -1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0? 1:0;
                    }
                    //周围上测金币翻转
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0? 1:0;
                    }
                    //周围下侧金币翻转
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0? 1:0;
                    }
                    //翻完金币解掉禁用
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            this->coinBtn[i][j]->isWin=false;
                        }
                    }

                    //判断是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin)
                    {
                        qDebug()<<"胜利了";
                        winSound->play();
                        //将所有的按钮的胜利改为true
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                               coinBtn[i][j]->isWin=true;
                            }
                        }
                        //将胜利图片移动下来
                        QPropertyAnimation* animation =new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }

                });

            });

        }
    }


}

void PlayScene::paintEvent(QPaintEvent *ev)
{
    QPainter  painter(this);
    QPixmap pix;
    pix.load(":/resource/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/resource/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
