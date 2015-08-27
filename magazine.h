#ifndef MAGAZINE
#define MAGAZINE

#include <QtGui>
#include "base.h"

class Base;

class Magazine
{
public:
    ~Magazine();
    void Click(int x, int y);
    void Paint(QPainter *painter);
    Magazine(QWindow *parent, Base *base);
    QString _gold_num, _credits_num;
private:
    int _state;
    Base *_base;
    QWindow *_parent;
    QRect _one, _two, _three, _four, _next, _prev, _back, _capt_one, _capt_two,
    _capt_three, _capt_four, _credits, _gold;
};

#endif // MAGAZINE
