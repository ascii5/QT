#include "widget.h"
#include "./ui_widget.h"
#include "qevent.h"
#include "qpainter.h"
#include<QPalette>
#include<QPoint>
#include<QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/picture/5.png"));
    this->setWindowTitle("五子棋");

    //初始化棋盘

    chessboard();


}
void Widget::chessboard()
{
    //绘制背景色
    QPalette palette;
    palette.setColor(backgroundRole(),QColor("#CD8500"));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    //定义棋盘大小
    this->setFixedSize((BOARD_W+1)*CHESS_X,(BOARD_H+1)*CHESS_Y);
    chess_color = false;
}
void Widget::paintEvent(QPaintEvent* event)
{
    //画棋盘
    draw_board();
    //画棋子
    draw_chess();
    //棋盘上的棋子
    draw_bd_chess();
    //更新界面
    update();
}
void Widget::draw_board()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::black));
    for(int i = 0; i < BOARD_W;i++)
    {
        for(int j = 0;j < BOARD_H;j++)
        {
            painter.drawRect((i+0.5)*CHESS_X,(j+0.5)*CHESS_Y,CHESS_X,CHESS_Y);
        }
    }

}
void Widget::draw_bd_chess()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    painter.setBrush(Qt::black);

    for(int i = 0; i < chess_vector.size();i++)
    {
        chess temp = chess_vector[i];
        if(temp._chess_color)
        {
            painter.setBrush(Qt::black);
        }
        else
        {
            painter.setBrush(Qt::white);
        }       
        draw(painter,temp._point);
    }

}
void Widget::draw_chess()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    if(chess_color)
    {
        painter.setBrush(QBrush(QColor(Qt::black)));
    }
    else
    {
        painter.setBrush(QBrush(QColor(Qt::white)));
    }

    painter.drawEllipse(mapFromGlobal(QCursor::pos()),CHESS_X/2-1,CHESS_Y/2-1);
}
void Widget::draw(QPainter&painter,QPoint&point)
{
    QPoint point1((point.x()+0.5)*CHESS_X,(point.y()+0.5)*CHESS_Y);
    painter.drawEllipse(point1,CHESS_X/2-1,CHESS_Y/2-1);

}
void Widget::mousePressEvent(QMouseEvent *event)
{
    QPoint pt;
    pt.setX(event->pos().x()/CHESS_X);
    pt.setY(event->pos().y()/CHESS_Y);
    for(int i = 0;i < chess_vector.size();i++)
    {
        chess temp = chess_vector[i];
        if(temp._point == pt)
        {
            return;
        }
    }
    chess temp(pt,chess_color);
    chess_vector.append(temp);

    int up = count_chess(temp, QPoint(0, 1));//上
    int down = count_chess(temp,QPoint(0, -1));//下
    int left = count_chess(temp,QPoint(-1,0));//左
    int right = count_chess(temp,QPoint(1,0));//右
    int left_up = count_chess(temp,QPoint(-1,1));//左上
    int left_down = count_chess(temp,QPoint(-1,-1));//左下
    int right_up = count_chess(temp,QPoint(1,1));//右上
    int right_down = count_chess(temp,QPoint(1,-1));//右下

    //判断胜利
    if((up+down) >=4||(left+right)>=4||(left_up+right_down) >=4||(left_down+right_up) >=4)
    {
        if(chess_color)
        {
            QMessageBox::information(this,NULL,"黑方胜利");

        }
        else            
            QMessageBox::information(this,NULL,"白方胜利");
        chess_vector.clear();

    }
    chess_color = !chess_color;
}
int Widget::count_chess(chess temp, QPoint pt)
{
    int count = 0;
    temp._point += pt;

    while(chess_vector.contains(temp))
    {
        count++;
        temp._point +=pt;
    }
    return count;
}


Widget::~Widget()
{
    delete ui;
}

