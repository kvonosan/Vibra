#ifndef FLY
#define FLY

#include "net.h"
#include <QtGui>
#include "base.h"
#include "grid.h"
#include "frame.h"

class Base;
class Net;

class Fly
{
public:
    ~Fly();
    void KeyPress(int key);
    void Click(int x, int y);
    void Paint(QPainter *painter);
    Fly(Net *net, QWindow *parent, Base *base);
    Grid *_grid;
private:
    Net *_net;
    Base *_base;
    Frame *_frame;
    QWindow *_parent;
    bool _menu, _compute;
    QRect _state, _exp, _energy, _radar, _cartograph, _scaner, _hold, _quit;
};

#endif // FLY
