#include "playscene.h"
#include<QMenu>
#include<QMenuBar>
#include<QMessageBox>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QPixmap>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSoundEffect>
PlayScene::PlayScene(int levenum)
{
    //基本场景配置
    this->levelIndex = levenum;
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
    });
    //返回音效
    QSoundEffect* back_sound = new QSoundEffect;
    back_sound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    back_sound->setLoopCount(1);
    back_sound->setVolume(0.75f);
    //翻金币音效
    QSoundEffect* coin_sound = new QSoundEffect;
    coin_sound ->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    coin_sound ->setLoopCount(1);
    coin_sound ->setVolume(0.75f);
    //胜利音效
    QSoundEffect* win_sound = new QSoundEffect;
    win_sound ->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    win_sound ->setLoopCount(1);
    win_sound ->setVolume(0.75f);
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
    //初始化金币排列数组
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            dataConfig fig;
            this->game_arry[i][j] = fig.mData[levelIndex ][i][j];
        }
    }
    //显示关卡数
    QLabel* label = new QLabel;
    label->setParent(this);
    label->move(30,this->height()-50);
    label->setFixedSize(120,50);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("LEVEL: %1 ").arg(this->levelIndex);
    label->setText(str);
    //成功图片预加载
    QLabel* win_label = new QLabel;
    QPixmap pix;
    win_label->setParent(this);
    pix.load(":/res/LevelCompletedDialogBg.png");
    win_label->setPixmap(pix);
    win_label->setFixedSize(QSize(pix.width(),pix.height()));
    win_label->setGeometry(0,0,pix.width(),pix.height());
    win_label->move((this->width()-pix.width())*0.5,-pix.height());
    //实现金币背景
    for(int i = 0;i < 4;i++)
    {
        for(int j = 0;j < 4;j++)
        {

            QLabel* label_coin_bk = new QLabel;
            label_coin_bk->setGeometry(0,0,50,50);
            label_coin_bk->setParent(this);
            QPixmap pix(":/res/BoardNode(1).png");
            label_coin_bk->setPixmap(pix);
            label_coin_bk->move(57+i*50,200+j*50);
            //创建金币
            if(game_arry[i][j] == 1)
            {
                MyCoin* coin = new MyCoin(":/res/Coin0001.png");
                coin->setParent(this);
                coin->move(59+i*50,204+j*50);
                coin->posX= i;
                coin->posY= j;
                coin->flag = 1;
                //初始化数组
                coinBtn[i][j]= coin;
                //金币翻转
                connect(coin,&QPushButton::clicked,[=]()
                {
                     coin->MyCoin::changeFlag();
                     this->game_arry[i][j] = this->game_arry[i][j] == 0 ? 1 : 0;
                     //翻金币音效播放
                      coin_sound->play();
                     //禁用按钮
                     for(int i = 0;i < 4; i++)
                     {
                           for(int j = 0;j < 4; j++)
                           {
                              coinBtn[i][j]->isWin = true;
                           }
                     }
                     //翻转周围
                     QTimer::singleShot(300,this,[=](){
                         if(coin->posX + 1 <= 3)//右
                         {
                             coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                             this->game_arry[coin->posX + 1][coin->posY] = this->game_arry[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                         }
                         if(coin->posX - 1 >= 0)//左
                         {
                             coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                             this->game_arry[coin->posX - 1][coin->posY] = this->game_arry[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                         }
                         if(coin->posY - 1 >= 0)//上
                         {
                             coinBtn[coin->posX ][coin->posY-1]->changeFlag();
                             this->game_arry[coin->posX][coin->posY-1] = this->game_arry[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                         }
                         if(coin->posY + 1 <= 3)//下
                         {
                             coinBtn[coin->posX ][coin->posY + 1 ]->changeFlag();
                             this->game_arry[coin->posX][coin->posY + 1 ] =  this->game_arry[coin->posX][coin->posY + 1 ] == 0 ? 1 : 0;
                         }
                         //禁用按钮
                         for(int i = 0;i < 4; i++)
                         {
                               for(int j = 0;j < 4; j++)
                               {
                                  coinBtn[i][j]->isWin = false;
                               }
                         }
                         //判断胜利
                         isWin = true;
                         for(int i = 0;i < 4; i++)
                         {
                             for(int j = 0;j < 4; j++)
                             {
                                 if(coinBtn[i][j]->flag == false)
                                 {
                                     isWin = false;
                                     break;
                                 }
                             }
                         }
                         if(isWin == true)
                         {

                             //禁用按钮
                             for(int i = 0;i < 4; i++)
                             {
                                 for(int j = 0;j < 4; j++)
                                 {
                                     coinBtn[i][j]->isWin = true;
                                 }
                             }
                             //成功的动画
                             QPropertyAnimation* animation = new QPropertyAnimation(win_label,"geometry");
                             animation->setDuration(1000);
                             animation->setStartValue(QRect(win_label->x(),win_label->y(),win_label->width(),win_label->height()));
                             animation->setEndValue(QRect(win_label->x(),win_label->y()+114,win_label->width(),win_label->height()));
                             animation->setEasingCurve(QEasingCurve::OutBounce);
                             animation->start();
                             //胜利音效
                             //win_sound->play();
                         }
                     });

                });

            }
            if(game_arry[i][j] == 0)
            {
                MyCoin* coin = new MyCoin(":/res/Coin0008.png");
                coin->setParent(this);
                coin->move(59+i*50,204+j*50);
                coin->posX= i;
                coin->posY= j;
                coin->flag = 0;
                coinBtn[i][j]= coin;
                //银币翻转
                connect(coin,&QPushButton::clicked,[=]()
                {
                     coin->MyCoin::changeFlag();
                     this->game_arry[i][j] = this->game_arry[i][j] == 0 ? 1 : 0;
                     //翻金币音效播放
                      coin_sound->play();
                     //禁用按钮
                     for(int i = 0;i < 4; i++)
                     {
                           for(int j = 0;j < 4; j++)
                           {
                              coinBtn[i][j]->isWin = true;
                           }
                     }
                     //翻转周围
                      QTimer::singleShot(300,this,[=](){
                          if(coin->posX + 1 <= 3)//右
                          {
                              coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                              this->game_arry[coin->posX + 1][coin->posY] = this->game_arry[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                          }
                          if(coin->posX - 1 >= 0)//左
                          {
                              coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                              this->game_arry[coin->posX - 1][coin->posY] = this->game_arry[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                          }
                          if(coin->posY - 1 >= 0)//上
                          {
                              coinBtn[coin->posX ][coin->posY-1]->changeFlag();
                              this->game_arry[coin->posX][coin->posY-1] = this->game_arry[coin->posX][coin->posY-1] == 0 ? 1 : 0;
                          }
                          if(coin->posY + 1 <= 3)//下
                          {
                              coinBtn[coin->posX ][coin->posY + 1 ]->changeFlag();
                              this->game_arry[coin->posX][coin->posY + 1 ] =  this->game_arry[coin->posX][coin->posY + 1 ] == 0 ? 1 : 0;
                          }
                          //恢复按钮
                          for(int i = 0;i < 4; i++)
                          {
                                for(int j = 0;j < 4; j++)
                                {
                                   coinBtn[i][j]->isWin = false;
                                }
                          }
                          //判断胜利
                          isWin = true;
                          for(int i = 0;i < 4; i++)
                          {


                              for(int j = 0;j < 4; j++)
                              {
                                  if(coinBtn[i][j]->flag == false)
                                  {
                                      isWin = false;
                                      break;
                                  }
                              }
                          }
                          if(isWin == true)
                          {
                              //禁用按钮
                              for(int i = 0;i < 4; i++)
                              {
                                  for(int j = 0;j < 4; j++)
                                  {
                                      coinBtn[i][j]->isWin = true;
                                  }
                              }
                              //胜利音效
                             // win_sound->play();
                              //成功的动画
                              QPropertyAnimation* animation = new QPropertyAnimation(win_label,"geometry");
                              animation->setDuration(1000);
                              animation->setStartValue(QRect(win_label->x(),win_label->y(),win_label->width(),win_label->height()));
                              animation->setEndValue(QRect(win_label->x(),win_label->y()+114,win_label->width(),win_label->height()));
                              animation->setEasingCurve(QEasingCurve::OutBounce);
                              animation->start();
                          }
                      });



                });
           }
        }
    }
}
//重写绘图
void PlayScene::paintEvent(QPaintEvent*)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}
