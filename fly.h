#ifndef FLY
#define FLY

#include <QtGui>
#include "base.h"

class Base;

class Fly
{
public:
    Fly(QWindow *parent, Base *base);
    ~Fly();
    void Paint(QPainter *painter);
    void Click(int x, int y);
private:
    Base *_base;
    QWindow *_parent;
};

#endif // FLY
