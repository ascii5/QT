#include "chooselevescene.h"
#include<QMenuBar>
#include<QMessageBox>
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include<QTimer>
#include<QPushButton>
#include<QLabel>
#include<QSoundEffect>
ChooseLeveScene::ChooseLeveScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币游戏");
    QMenuBar* bar = menuBar();
    setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("菜单");
    QAction* button1 = startMenu->addAction("退出");
    connect(button1,&QAction::triggered,[=]()
    {
        this->close();
    }
);
    QAction* button2 = startMenu->addAction("帮助");
    connect(button2,&QAction::triggered,[=]()
    {
        QMessageBox::information(this,"帮助","翻金币游戏：当你翻动一枚金币时周围金币也会翻动，试着将它们全部翻成金币");
    }
    );
    QAction* button3 = startMenu->addAction("关于作者");
    connect(button3,&QAction::triggered,[=]()
    {
        QMessageBox::information(this,"关于作者","ascii-");
    }
    );
    //返回音效
    QSoundEffect* back_sound = new QSoundEffect;
    back_sound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    back_sound->setLoopCount(1);
    back_sound->setVolume(0.75f);
    //返回按钮
    MyPushButton* back_button = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    back_button->setParent(this);
    back_button->move(this->width()-back_button->width(),this->height()-back_button->height());
    //实现返回功能
    connect(back_button,&QPushButton::clicked,[=]()
    {
        //按钮音效
        back_sound->play();
        QTimer::singleShot(200,this,[=]()
        {
             emit this->choose_back_scene();
        });

    });
    //创建关卡选择按钮音效
    QSoundEffect* start_sound = new QSoundEffect;
    start_sound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    start_sound->setLoopCount(1);
    start_sound->setVolume(0.75f);
    //关卡选择按钮
    for(int i = 0;i < 20;i++)
    {
        MyPushButton* menu_button = new MyPushButton(":/res/LevelIcon.png");
        menu_button->setParent(this);
        menu_button->move(25 + i%4*70,130+i/4*70);
        //监听每个按钮点击
        connect(menu_button,&MyPushButton::clicked,[=]()
        {
            menu_button->zoom1();
            menu_button->zoom2();
            start_sound->play();
            //进入游戏主场景
            QTimer::singleShot(500,this,[=]()
            {
                this->hide();
                play = new PlayScene(i+1);
                //记录坐标
                play->setGeometry(this->geometry());
                play->show();


                //监听返回信号
                connect(play,&PlayScene::choose_back_scene,this,[=]()
                {
                    this->setGeometry(play->geometry());
                    play->hide();
                    this->show();
                });

            });

        });
        QLabel* label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menu_button->width(),menu_button->height());
        label->setText(QString::number(i+1));
        label->move(25 + i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}
void ChooseLeveScene::paintEvent(QPaintEvent*)
{
    //加载背景
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
