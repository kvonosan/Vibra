#ifndef HONORS
#define HONORS

#include <QtGui>
#include "base.h"

class Base;

class Honors
{
public:
    Honors(QWindow *parent, Base *base);
    ~Honors();
    void Paint(QPainter *painter);
    void Click(int x, int y);
private:
    Base *_base;
    QWindow *_parent;
    QRect _ramka1, _ramka2, _ramka3, _back;
    QRect _ramka1_capt, _ramka2_capt, _ramka3_capt;
};

#endif // HONORS
