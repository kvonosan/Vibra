#ifndef LOADER
#define LOADER

#include <QtSql>
#include <QVector>
#include "player.h"

class Loader
{
public:
    Loader();
    ~Loader();
    void DatabaseConnect();
    QString Generate768d();
    void GenerateStartMap();
    void GenerateTables();
    QString Bufferize(Player *player);
    void GenerateLeftMap(Player *player);
private:
    QSqlDatabase _db;
};

#endif // LOADER
