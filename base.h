#ifndef BASE
#define BASE

#include <QtGui>
#include "net.h"
#include "fly.h"
#include "grid.h"
#include "bank.h"
#include "hero.h"
#include "rating.h"
#include "honors.h"
#include "magazine.h"
#include "mainwindow.h"
#include "news.h"

class News;
class Net;
class Fly;
class Bank;
class Hero;
class Honors;
class Rating;
class Magazine;
class MainWindow;

class Base
{
public:
    ~Base();
    void KeyPress(int key);
    void Click(int x, int y);
    void MouseMove(int x, int y);
    void Paint(QPainter *painter);
    Base(QWindow *parent, Net *net, MainWindow *mainwindow);
    Fly *_fly;
    int _state;
    Hero *_hero_obj;
    MainWindow *_mainwindow;
    Net *_net;
private:
    QFont _font;
    Bank *_bank_obj;
    QWindow *_parent;
    Honors *_honors_obj;
    Rating *_rating_obj;
    Magazine *_magazine_obj;
    News *_news_obj;
    QRect _bank, _magazine, _hero, _bar, _honors, _rating, _flight, _quit,
    _generator, _news, _improvement;
};

#endif // BASE
