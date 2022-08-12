#ifndef MYCOIN_H
#define MYCOIN_H

#include <QWidget>
#include<QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString btnImg);
    //金币的属性
    int posX;
    int posY;
    bool flag;
    //改变标志
    void changeFlag();
    QTimer* timer1;
    QTimer* timer2;
    int min = 1;
    int max = 8;
    bool isWin;
    //执行动画标志
    bool isAnimation = false;
    //重写按下
    void mousePressEvent(QMouseEvent*e);
    //判断胜利

signals:

};

#endif // MYCOIN_H
