#ifndef FLY
#define FLY

#include <QtGui>
#include "base.h"
#include "grid.h"
#include "frame.h"

class Base;

class Fly
{
public:
    Fly(QWindow *parent, Base *base);
    ~Fly();
    void Paint(QPainter *painter);
    void Click(int x, int y);
    void KeyPress(int key);
private:
    Base *_base;
    QWindow *_parent;
    bool _menu, _compute;
    Grid *_grid;
    QRect _state, _exp, _energy, _radar, _cartograph, _scaner, _hold, _quit;
    Frame *_frame;
};

#endif // FLY
