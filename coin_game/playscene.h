#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"MyCoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levenum);
    int levelIndex;
    void paintEvent(QPaintEvent*);
    int game_arry[4][4];
    MyCoin *coinBtn[4][4];
    //判断胜利
    bool isWin;
signals:
    void choose_back_scene();
};

#endif // PLAYSCENE_H
