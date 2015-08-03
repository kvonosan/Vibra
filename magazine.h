#ifndef MAGAZINE
#define MAGAZINE

#include <QtGui>
#include "base.h"

class Base;

class Magazine
{
public:
    Magazine(QWindow *parent, Base *base);
    ~Magazine();
    void Paint(QPainter *painter);
    void Click(int x, int y);
    QString _gold_num, _credits_num;
private:
    QRect _one, _two, _three, _four, _next, _prev, _back;
    QRect _capt_one, _capt_two, _capt_three, _capt_four;
    QRect _credits, _gold;
    int _state;
    QWindow *_parent;
    Base *_base;
};

#endif // MAGAZINE
