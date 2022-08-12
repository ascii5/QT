#include "mycoin.h"
#include<QPixmap>
#include"playscene.h"//.h
MyCoin::MyCoin(QString btnImg)
{
    this->isWin = false;
    QPixmap pix(btnImg);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    connect(timer1,&QTimer::timeout,this,[=]()
    {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min > this->max)
        {
            this->min = 1;
            isAnimation = false;//动画停止
            timer1->stop();

        }
    });
    connect(timer2,&QTimer::timeout,this,[=]()
    {
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->max < this->min)
        {
            this->max = 8;
            isAnimation = false;//动画停止
            timer2->stop();
        }
    });
}
void MyCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        isAnimation = true;//动画开始
        this->flag = false;

    }
    else
    {
        timer2->start(30);
        isAnimation = true;//动画开始
        this->flag = true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent*e)//禁止翻转动画打断
{

    if(this->isAnimation || this->isWin == true )
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
