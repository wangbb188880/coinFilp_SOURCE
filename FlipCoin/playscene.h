#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QWidget>
#include<QPainter>
#include<mypushbutton.h>
#include<QLabel>
#include"dataconfig.h"
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
   // explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int num);
    MyCoin * coinBtn[4][4];


signals:
    void sendBack();
private:
    int num;
    dataConfig * dataconfig;
    int gameArray[4][4];
    bool isWin;

public slots:
protected:
    void paintEvent(QPaintEvent * ev);
};

#endif // PLAYSCENE_H



















