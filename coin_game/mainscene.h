#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"chooselevescene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent*);
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    ChooseLeveScene* choose = NULL;

private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
