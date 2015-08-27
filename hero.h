#ifndef HERO
#define HERO

#include <QtGui>
#include "base.h"

class Base;

class Hero
{
public:
    ~Hero();
    void SetParams();
    void Click(int x, int y);
    void Paint(QPainter *painter);
    Hero(QWindow *parent, Base *base);
    QString _name, _experience, _gold, _credits, _race, _ship, _specialty,
    _rank, _squadron, _rating;
private:
    Base *_base;
    QString _string;
    QWindow *_parent;
    QRect _ramka, _back;
};

#endif // HERO
