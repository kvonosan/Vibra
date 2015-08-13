#ifndef INFINITE_WORLD
#define INFINITE_WORLD

#include <QVector>

class InfiniteWorld
{
public:
    InfiniteWorld();
    ~InfiniteWorld();
private:
    QVector <QVector <QChar> > map;
    InfiniteWorld *left, *right, *top, *bottom, *in_front, *behind;
    void BufferizeLeft(int *num);
    void BufferizeRight(int *num);
    void BufferizeTop(int *num);
    void BufferizeBottom(int *num);
    void BufferizeInFront(int *num);
    void BufferizeBehind(int *num);
    void GenerateLeft(int *num);
    void GenerateRight(int *num);
    void GenerateTop(int *num);
    void GenerateBottom(int *num);
    void GenerateInFront(int *num);
    void GenerateBehind(int *num);
};

#endif // INFINITE_WORLD
