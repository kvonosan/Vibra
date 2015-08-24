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
    void Generate768d(InfiniteWorld *map);
    void GenerateMap();
    void GenerateTables();
    void SaveMapToDatabase(InfiniteWorld *map);
    void LoadToBuffer(int map_id, int radius);
    int BufferizeLeft(int map_id, int radius);
    int BufferizeRight(int map_id, int radius);
    int BufferizeTop(int map_id, int radius);
    int BufferizeBottom(int map_id, int radius);
    int BufferizeInFront(int map_id, int radius);
    int BufferizeBehind(int map_id, int radius);
    void LoadData();
    void AddPlayerToMap();
    QSqlDatabase _db;
    int _sector_len;
};

#endif // LOADER
