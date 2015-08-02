#ifndef BASE
#define BASE

#include <QtGui>
#include "grid.h"
#include "frame.h"

class Base
{
public:
    Base(QWindow *parent);
    ~Base();
    void Paint(QPainter *painter);
private:
    QRect _bank, _magazine, _hero, _bar, _honors, _rating, _flight, _quit;
    QFont _font;
    Frame *_frame;
    QWindow *_parent;
};

#endif // BASE
