#ifndef BANK
#define BANK

#include <QtGui>
#include "base.h"

class Base;

class Bank
{
public:
    ~Bank();
    void Click(int x, int y);
    void Paint(QPainter *painter);
    Bank(QWindow *parent, Base *base);
private:
    Base *_base;
    QWindow *_parent;
    QRect _credit500, _credit300, _credit100, _gold500, _exp2, _exp3, _exp5, _back;
};

#endif // BANK
