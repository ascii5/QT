#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QMouseEvent>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
   MyPushButton(QString normalImg,QString pressedImg = "");
   QString normalImgPath;
   QString pressedImgPath;
   //弹跳特效
   void zoom1();//下
   void zoom2();//上
   //按钮的按下和释放
   void mousePressEvent(QMouseEvent*e);
   void mouseReleaseEvent(QMouseEvent*e);
signals:

};

#endif // MYPUSHBUTTON_H
