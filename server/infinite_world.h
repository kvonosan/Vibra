#ifndef INFINITE_WORLD
#define INFINITE_WORLD

#include <QVector>

class InfiniteWorld
{
public:
    InfiniteWorld();
    ~InfiniteWorld();
    InfiniteWorld *_left, *_right, *_top, *_bottom, *_in_front, *_behind;
    QVector <QChar> _map;
};

#endif // INFINITE_WORLD
