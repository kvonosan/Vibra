#ifndef NEWS
#define NEWS

#include <QtGui>
#include "base.h"

class Base;

class News
{
public:
    News(QWindow *parent, Base *base);
    ~News();
    void Click(int x, int y);
    void Paint(QPainter *painter);
private:
    Base *_base;
    QWindow *_parent;
    QRect _back, _ramka1, _ramka1_capt;
};

#endif // NEWS
