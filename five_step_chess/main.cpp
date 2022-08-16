
#include"login_scene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //加载登录界面
    login_scene* login = new login_scene;
    login->show();

    return a.exec();



}
