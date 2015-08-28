#ifndef BASE
#define BASE

#include <QtGui>
#include "fly.h"
#include "grid.h"
#include "bank.h"
#include "hero.h"
#include "frame.h"
#include "rating.h"
#include "honors.h"
#include "magazine.h"

class Fly;
class Bank;
class Hero;
class Honors;
class Rating;
class Magazine;

class Base
{
public:
    ~Base();
    Base(QWindow *parent);
    void KeyPress(int key);
    void Click(int x, int y);
    void MouseMove(int x, int y);
    void Paint(QPainter *painter);
    int _state;
    Hero *_hero_obj;
private:
    Fly *_fly;
    QFont _font;
    Frame *_frame;
    Bank *_bank_obj;
    QWindow *_parent;
    Honors *_honors_obj;
    Rating *_rating_obj;
    Magazine *_magazine_obj;
    QRect _bank, _magazine, _hero, _bar, _honors, _rating, _flight, _quit,
    _generator, _news, _improvement;
};

#endif // BASE
