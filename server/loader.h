#ifndef LOADER
#define LOADER

#include <QtSql>
#include <QVector>
#include "infinite_world.h"

class Loader
{
public:
    Loader();
    ~Loader();
    void DatabaseConnect();
    void ListenPlayers();
private:
    QVector<InfiniteWorld* > _map;
    void GenerateLeft(InfiniteWorld *map);
    void GenerateRight(InfiniteWorld *map);
    void GenerateTop(InfiniteWorld *map);
    void GenerateBottom(InfiniteWorld *map);
    void GenerateInFront(InfiniteWorld *map);
    void GenerateBehind(InfiniteWorld *map);
    void Generate(InfiniteWorld *map);
    void BufferizeLeft();
    void BufferizeRight();
    void BufferizeTop();
    void BufferizeBottom();
    void BufferizeInFront();
    void BufferizeBehind();
    void AddPlayerToMap();
    QSqlDatabase _db;
};

#endif // LOADER
