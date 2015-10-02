#ifndef FLY
#define FLY

#include <QTime>
#include "net.h"
#include <QtGui>
#include "base.h"
#include "grid.h"
#include "popup.h"
#include "symbol.h"

class Base;
class Net;

class Fly
{
public:
    ~Fly();
    void KeyPress(int key);
    void Click(int x, int y);
    void Paint(QPainter *painter);
    void NextTime(QPainter *painter);
    Fly(Net *net, QWindow *parent, Base *base);
    Grid *_grid;
private:
    float _posX, _posY;
    Net *_net;
    QTime _time;
    Base *_base;
    Popup *_popup;
    Symbol *_current;
    QWindow *_parent;
    QVector<int> _firecoords, _mycoords;
    bool _menu, _compute, _attack;
    QRect _state, _exp, _energy, _radar, _cartograph, _scaner, _hold, _quit,
    _attack_menu, _duel_menu;
};

#endif // FLY
