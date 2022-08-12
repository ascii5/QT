#ifndef CHOOSELEVESCENE_H
#define CHOOSELEVESCENE_H

#include <QMainWindow>
#include<QLabel>
#include"playscene.h"
class ChooseLeveScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLeveScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    QLabel* label;
    PlayScene* play = NULL;
signals:
    void choose_back_scene();
};

#endif // CHOOSELEVESCENE_H
