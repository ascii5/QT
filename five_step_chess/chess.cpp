#include "chess.h"

chess::chess()
{

}
chess::chess(QPoint point,bool chess_color)
{
    _point = point;
    _chess_color = chess_color;
}
