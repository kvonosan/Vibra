#ifndef BASE
#define BASE

#include <QtGui>
#include "grid.h"
#include "frame.h"
#include "magazine.h"
#include "hero.h"

class Magazine;
class Hero;

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
    QRect _generator, _news, _improvement;
    QFont _font;
    Frame *_frame;
    QWindow *_parent;
    Magazine *_magazine_obj;
    Hero *_hero_obj;
};

#endif // BASE
