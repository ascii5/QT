#ifndef CHESS_H
#define CHESS_H
#include<QPoint>

class chess
{
public:
    chess();
    chess(QPoint point,bool chess_color);
    QPoint _point;
    bool _chess_color;
    bool operator==(const chess&ch1)const
    {
         return ((_point == ch1._point) && (_chess_color == ch1._chess_color));
    }
};

#endif // CHESS_H
