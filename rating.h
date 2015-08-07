#ifndef RATING
#define RATING

#include <QtGui>
#include "base.h"

class Base;

class Rating
{
public:
    Rating(QWindow *parent, Base *base);
    ~Rating();
    void Paint(QPainter *painter);
    void Click(int x, int y);
private:
    Base *_base;
    QWindow *_parent;
    QRect _back, _ramka1, _ramka1_capt;
};

#endif // RATING
