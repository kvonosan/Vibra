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
