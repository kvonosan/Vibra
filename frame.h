#ifndef FRAME
#define FRAME

#include "grid.h"
#include <QtGui>

class Frame
{
public:
    Frame(QWindow *parent);
    ~Frame();
    void Paint(QPainter *painter);
    QString _action, _target, _view, _rank, _ship;
private:
    Grid *_grid;
    QWindow *_parent;
    QPainter *_painter;
    void SetAction();
    void SetTarget();
    void SetView();
    void SetRank();
    void SetShip();
};

#endif // FRAME
