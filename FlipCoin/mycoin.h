#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QString>
#include<QDebug>
#include<QTimer>
#include<QMouseEvent>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinImg);
    void changeFlag();
    QTimer * time1;
    QTimer* time2;
    int posX,posY;
    bool flag;
    int min=1,max=8;
    bool isAnimation=false;
    void mousePressEvent(QMouseEvent *e);
    bool  isWin=false;

signals:

public slots:
};

#endif // MYCOIN_H
