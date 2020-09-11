#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include<QPushButton>
#include<QPropertyAnimation>
#include<QString>
#include<QEvent>
#include<QMouseEvent>

#include <QObject>
#include <QWidget>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    myPushButton(QString normal_path,QString press_path="");
    void zoom1();
    void zoom2();
private:
    QString normal_path;
    QString press_path;
    QPropertyAnimation* animation;
protected:
    void mousePressEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent * e);
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
