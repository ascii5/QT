#include "mypushbutton.h"
#include<QPushButton>
#include<QPixmap>
#include<QDebug>
#include<QPropertyAnimation>
MyPushButton::MyPushButton(QString normalImg,QString pressedImg)
{
    //参数初始化
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressedImg;
    //按钮效果实现
    QPixmap pix;
    bool ret = pix.load(this->normalImgPath);
    if(!ret)
    {
        qDebug()<<"打开图片失败";
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

}
void MyPushButton::zoom1()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2()
{
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent*e)
{
    if(this->pressedImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressedImgPath);
        if(!ret)
        {
            qDebug()<<"打开图片失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent*e)
{
    if(this->pressedImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"打开图片失败";
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
