#ifndef HERO
#define HERO

#include <QtGui>
#include "base.h"

class Base;

class Hero
{
public:
    Hero(QWindow *parent, Base *base);
    ~Hero();
    void Paint(QPainter *painter);
    void Click(int x, int y);
    void SetParams();
    QString _name, _experience, _gold, _credits, _race, _ship, _specialty,
    _rank, _squadron, _rating;
private:
    Base *_base;
    QWindow *_parent;
    QRect _ramka, _back;
    QString _string;
};

#endif // HERO
