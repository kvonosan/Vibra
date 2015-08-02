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
private:
    Grid *_grid;
    QWindow *_parent;
    QPainter *_painter;
    QFont _font;
};

#endif // FRAME
