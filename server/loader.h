#ifndef LOADER
#define LOADER

#include <QtSql>
#include "player.h"

class Player;

class Loader
{
public:
    Loader();
    ~Loader();
    void GenerateTables();
    void DatabaseConnect();
    QString Generate768d();
    void GenerateStartMap();
    QString Bufferize(Player *player);
    void GenerateTopMap(Player *player);
    void GenerateLeftMap(Player *player);
    void GenerateRightMap(Player *player);
    void GenerateBottomMap(Player *player);
    QSqlDatabase _db;
    QString _settingsFile;
};

#endif // LOADER
