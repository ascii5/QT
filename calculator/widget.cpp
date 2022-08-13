#include "widget.h"
#include "./ui_widget.h"
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QLineEdit>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //控件
    //数字按钮
    for(int i = 0;i < 10;i++)
    {
        num_button[i] = new QPushButton(QString::number(i));
    }
    //运算符按钮
     add_button = new QPushButton("+");
     sub_button = new QPushButton("-");
     mul_button = new QPushButton("*");
     div_button = new QPushButton("/");
     //计算键
     cal_button = new QPushButton("=");
     cal_button->setMinimumHeight(100);
     //cal_button->height();
     //删除键
     del_button = new QPushButton("c");
     //计算框
     output = new QLineEdit;




     //布局
     qhboxlayout = new QHBoxLayout;
     qvboxlayout = new QVBoxLayout;
     qgrilayout = new QGridLayout;
     int j = 0;
     for(int i = 1;i < 10;i++)
     {
         qgrilayout->addWidget(num_button[i],j,(i - 1)%3,1,1);
         if(i%3 == 0)
             j++;

     }
     qhboxlayout->addWidget(output);
     qgrilayout->addWidget(add_button,0,3,1,1);
     qgrilayout->addWidget(sub_button,1,3,1,1);
     qgrilayout->addWidget(mul_button,2,3,1,1);
     qgrilayout->addWidget(del_button,0,4,1,1);
     qgrilayout->addWidget(cal_button,1,4,3,1);
     qgrilayout->addWidget(num_button[0],3,1,1,2);
     qgrilayout->addWidget(div_button,3,3,1,1);
     qvboxlayout->addLayout(qhboxlayout);

     qvboxlayout->addLayout(qgrilayout);
     setLayout(qvboxlayout);





     //槽函数连接
     //数字处理
     for(int i = 0;i < 10;i++)
     {
         connect(num_button[i],&QPushButton::clicked,this,&Widget::number_slot);
     }
     //操作符处理
     connect(add_button,&QPushButton::clicked,this,&Widget::op_slot);
     connect(sub_button,&QPushButton::clicked,this,&Widget::op_slot);
     connect(mul_button,&QPushButton::clicked,this,&Widget::op_slot);
     connect(div_button,&QPushButton::clicked,this,&Widget::op_slot);
     //计算键
     connect(cal_button,&QPushButton::clicked,this,&Widget::cal_solt);
     //c键
     connect(del_button,&QPushButton::clicked,[=]()
     {
            output->clear();
            data1 =0;
            data2 = 0;
            judge = true;
     });





}
void Widget::op_slot()
{
   output->clear();
   QPushButton *btx = static_cast<QPushButton *>(sender());
   op = btx->text();
   judge_op = false;
};
void Widget::number_slot()
{


    QPushButton* btx = (QPushButton*)sender();
    if(judge)
    data1 = btx->text().toInt();
    output->setText(btx->text());
    judge = false;

}
void Widget::cal_solt()
{
    data2 = output->text().toInt();
    output->clear();

    switch(op.toStdString().c_str()[0])
    {
    case '+': sum = data1+data2; break;
    case '-': sum = data1-data2; break;
    case '*': sum = data1*data2; break;
    case '/': sum = data1/data2; break;
    }
    if(!judge_op)
    output->setText(QString::number(sum));
    else
        output->setText(QString::number(data1));

}
Widget::~Widget()
{
    delete ui;
}

