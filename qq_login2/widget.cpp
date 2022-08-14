#include "widget.h"
#include "./ui_widget.h"
#include<QSpacerItem>
#include<QMessageBox>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(457,307);
    this->setWindowIcon(QIcon(":/QQ.png"));
    this->setWindowTitle(QString("QQ登录"));
    //控件实现

    username = new QLabel("用户名");
    password = new QLabel("密码");
    login = new QPushButton("登录");
    //login->setParent(this);
    exit = new QPushButton("退出");
   //exit->setParent(this);
    show_password = new QCheckBox("显示");
    line_user = new QLineEdit;
    line_password = new QLineEdit;
    line_password->setEchoMode(QLineEdit::Password);
    QSpacerItem* space1 = new QSpacerItem(50,0,QSizePolicy::Fixed);
    QSpacerItem* space2 = new QSpacerItem(10,0,QSizePolicy::Fixed);
    //布局



    hbox1 = new QHBoxLayout;
    hbox1->addItem(space1);
    hbox1->addWidget(username);
    hbox1->addWidget(line_user);
    hbox1->addItem(space1);
    hbox2 = new QHBoxLayout;
    hbox2->addItem(space1);
    hbox2->addWidget(password);
     hbox2->addItem(space2);
    hbox2->addWidget(line_password);
    hbox2->addWidget(show_password);
    hbox3 = new QHBoxLayout;
    hbox3->addItem(space1);
    hbox3->addWidget(login);
    hbox3->addItem(space1);
    hbox3->addWidget(exit);
    hbox3->addItem(space1);
    vbox = new QVBoxLayout;

    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addLayout(hbox3);
//    vbox->addItem(hbox1);
    setLayout(vbox);





    //槽函数处理
    connect(show_password,&QCheckBox::clicked,this,&Widget::password_slot);
    connect(login,&QPushButton::clicked,this,&Widget::login_slot);
    connect(exit,&QPushButton::clicked,this,&Widget::exit_slot);
}
void Widget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix(":/20220814125422.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
void Widget::password_slot(bool x)
{
    if(x)
    line_password->setEchoMode(QLineEdit::Normal);
    else
    {
        line_password->setEchoMode(QLineEdit::Password);
    }
}
void Widget::login_slot()
{
    QString qstr_user = line_user->text();
    QString qstr_password = line_password->text();
    string str_user =qstr_user.toStdString();
    string str_password =qstr_password.toStdString();
    if(str_user.compare("admin") == 0 && str_password.compare("password") == 0 )
        QMessageBox::information(this,"QQ","登录成功!");
    else
        QMessageBox::information(this,"QQ","登录失败!");
}
void Widget::exit_slot()
{
    this->close();
}
Widget::~Widget()
{
    delete ui;
}

