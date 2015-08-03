#ifndef BASE
#define BASE

#include <QtGui>
#include "grid.h"
#include "frame.h"
#include "magazine.h"

class Magazine;

class Base
{
public:
    Base(QWindow *parent);
    ~Base();
    void Paint(QPainter *painter);
    void MouseMove(int x, int y);
    void Click(int x, int y);
    int _state;
private:
    QRect _bank, _magazine, _hero, _bar, _honors, _rating, _flight, _quit;
    QFont _font;
    Frame *_frame;
    QWindow *_parent;
    Magazine *_magazine_obj;
};

#endif // BASE
