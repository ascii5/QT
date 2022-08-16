#include "login_scene.h"
#include <QApplication>

#include<QSpacerItem>
#include<QMessageBox>
using namespace std;

login_scene::login_scene(QWidget *parent)
    : QWidget{parent}

{

    setFixedSize(457,307);
    this->setWindowIcon(QIcon(":/picture/5.png"));
    this->setWindowTitle(QString("用户登录"));
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
    connect(show_password,&QCheckBox::clicked,this,&login_scene::password_slot);
    connect(login,&QPushButton::clicked,this,[=]()
    {
        QString qstr_user = line_user->text();
        QString qstr_password = line_password->text();
        string str_user =qstr_user.toStdString();
        string str_password =qstr_password.toStdString();
        if(str_user.compare("12345") == 0 && str_password.compare("12345") == 0 )
        {
            //创建下棋页面
            this->hide();
            w.setGeometry(this->geometry());
            w.show();

        }
        else
            QMessageBox::information(this,"用户登录","登录失败!");
    });
    connect(exit,&QPushButton::clicked,this,&login_scene::exit_slot);

}
void login_scene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix(":/picture/1.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


}
void login_scene::password_slot(bool x)
{
    if(x)
    line_password->setEchoMode(QLineEdit::Normal);
    else
    {
        line_password->setEchoMode(QLineEdit::Password);
    }
}
//void login_scene::login_slot()
//{

//}
void login_scene::exit_slot()
{
    this->close();
}
login_scene::~login_scene()
{

}
