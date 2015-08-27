#ifndef RATING
#define RATING

#include <QtGui>
#include "base.h"

class Base;

class Rating
{
public:
    ~Rating();
    void Click(int x, int y);
    void Paint(QPainter *painter);
    Rating(QWindow *parent, Base *base);
private:
    Base *_base;
    QWindow *_parent;
    QRect _back, _ramka1, _ramka1_capt;
};

#endif // RATING
