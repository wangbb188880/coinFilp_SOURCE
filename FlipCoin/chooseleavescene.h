#ifndef CHOOSELEAVESCENE_H
#define CHOOSELEAVESCENE_H

#include <QMainWindow>
#include<QEvent>
#include<QPainter>
#include"mypushbutton.h"
#include"playscene.h"

class ChooseLeaveScene : public QMainWindow
{
    Q_OBJECT
signals:
    void sendBackSignal(int num);
public:
    explicit ChooseLeaveScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev);
private:

    myPushButton*  backBtn;
    PlayScene* playscene;
    int  num ;


public slots:
};

#endif // CHOOSELEAVESCENE_H
