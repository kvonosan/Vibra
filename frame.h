#ifndef FRAME
#define FRAME

#include "grid.h"
#include <QtGui>

class Frame
{
public:
    ~Frame();
    Frame(QWindow *parent);
    void Paint(QPainter *painter);
    int GetWidth(){return _grid->GetSizeX();}
    int GetHeight(){return _grid->GetSizeY();}
    QString _action, _target, _view, _rank, _ship;
private:
    void SetView();
    void SetRank();
    void SetShip();
    void SetAction();
    void SetTarget();
    Grid *_grid;
    QWindow *_parent;
    QPainter *_painter;
};

#endif // FRAME
