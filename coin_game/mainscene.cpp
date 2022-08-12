#include "mainscene.h"
#include "./ui_mainscene.h"
#include<QMessageBox>
#include<QPainter>
#include<QTimer>
#include"mypushbutton.h"
#include"chooselevescene.h"
#include<QSoundEffect>
#include<QMediaPlayer>
#include<QAudioOutput>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //退出按钮
    connect(ui->actionnewButton,&QAction::triggered,[=]()
    {
        this->close();
    }
    );
    //帮助文档
    connect(ui->actionnewButton2,&QAction::triggered,[=]()
    {
        QMessageBox::information(this,"帮助","翻金币游戏：当你翻动一枚金币时周围金币也会翻动，试着将它们全部翻成金币");
    }
    );
    //关于作者
    connect(ui->actionnewButton3,&QAction::triggered,[=]()
    {
        QMessageBox::information(this,"关于作者","ascii-");
    }
    );
    //创建开始按钮音效
    QSoundEffect* start_sound = new QSoundEffect;
    start_sound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    start_sound->setLoopCount(1);
    start_sound->setVolume(0.75f);

    //创建背景音效
    QMediaPlayer* bk_ground = new QMediaPlayer;
    QAudioOutput* audioOutput = new  QAudioOutput;
    bk_ground->setAudioOutput(audioOutput);
    connect(bk_ground, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    bk_ground->setSource(QUrl::fromLocalFile("qrc:/bkground.mp3"));
    //bk_ground->setLoops(1000);
    //bk_ground->setParent(this);
    audioOutput->setVolume(75);

    bk_ground->play();
    //创建开始按钮
    MyPushButton* start_button = new MyPushButton(":/res/MenuSceneStartButton.png");
    start_button->setParent(this);
    start_button->move(this->width()*0.5-start_button->width()*0.5,this->height()*0.7);
    choose = new ChooseLeveScene;
    connect(start_button,&MyPushButton::clicked,[=]()//弹起特效
    {
        start_button->zoom1();
        start_button->zoom2();
        //播放声音
        start_sound->play();
       //进入选择关卡界面
        QTimer::singleShot(500,this,[=]()
        {
            //记录坐标位置
            choose->setGeometry(this->geometry());
            //隐藏主界面
            this->hide();
            //显示场景页面
            choose->show();
        });

    });
    //监听返回信号
    connect(choose,&ChooseLeveScene::choose_back_scene,this,[=]()
    {
        choose->hide();
        this->show();
        this->setGeometry(choose->geometry());

    });


}
void MainScene::paintEvent(QPaintEvent*)
{
    //加载背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/1.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}

MainScene::~MainScene()
{
    delete ui;
}

