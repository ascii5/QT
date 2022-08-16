#ifndef LOGIN_SCENE_H
#define LOGIN_SCENE_H
#include <QWidget>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QCheckBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPainter>
#include<QPaintEvent>
#include"widget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class login_scene : public QWidget
{
    Q_OBJECT

public:
    //控件
    QLabel* username;
    QLabel* password;
    QPushButton* login;
    QPushButton* exit;
    QCheckBox* show_password;
    QLineEdit* line_user;
    QLineEdit* line_password;
    QHBoxLayout* hbox1 ;
    QHBoxLayout* hbox2 ;
    QHBoxLayout* hbox3;
    QVBoxLayout* vbox;
    void paintEvent(QPaintEvent*);



//    void login_slot();
    void exit_slot();
    void password_slot(bool x);
   login_scene(QWidget *parent = nullptr);
    ~login_scene();


   //登录判断
   bool login_judge = false;
   Widget w;

private:
    Ui::Widget *ui;
};






#endif // LOGIN_SCENE_H


