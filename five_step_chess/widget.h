#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"chess.h"
#define BOARD_W 20
#define BOARD_H 20
#define CHESS_X 40
#define CHESS_Y 40

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QVector<chess> chess_vector;
    bool chess_color;
    void chessboard();
    void draw_board();
    void draw_chess();
    void draw_bd_chess();
    int count_chess(chess temp, QPoint pt);

    void draw(QPainter&painter,QPoint&point);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
};
#endif // WIDGET_H
