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
    void ListenPlayers();
    void DatabaseConnect();
private:
    void LoadData();
    void GenerateMap();
    void AddPlayerToMap();
    void GenerateTables();
    void GenerateTop(InfiniteWorld *map);
    void Generate768d(InfiniteWorld *map);
    void GenerateLeft(InfiniteWorld *map);
    void GenerateRight(InfiniteWorld *map);
    void GenerateBehind(InfiniteWorld *map);
    void GenerateBottom(InfiniteWorld *map);
    void GenerateInFront(InfiniteWorld *map);
    int BufferizeTop(int map_id, int radius);
    int BufferizeLeft(int map_id, int radius);
    void SaveMapToDatabase(InfiniteWorld *map);
    int BufferizeRight(int map_id, int radius);
    int BufferizeBottom(int map_id, int radius);
    int BufferizeBehind(int map_id, int radius);
    int BufferizeInFront(int map_id, int radius);
    int _sector_len;
    QSqlDatabase _db;
    QVector<InfiniteWorld* > _map;
};

#endif // LOADER
