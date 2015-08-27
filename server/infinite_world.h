#ifndef INFINITE_WORLD
#define INFINITE_WORLD

#include <QChar>
#include <QVector>

class InfiniteWorld
{
public:
    InfiniteWorld();
    ~InfiniteWorld();
    QVector <QChar> _map;
    InfiniteWorld *_left, *_right, *_top, *_bottom, *_in_front, *_behind;
};

#endif // INFINITE_WORLD
