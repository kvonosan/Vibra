#ifndef PLAYER
#define PLAYER

#include <QtSql>
#include "infinite_world.h"

class Player
{
public:
    Player();
    ~Player();
    int _player_id;
    int _player_id_vk;
    bool Search();
private:
    InfiniteWorld *_player_map;
    QSqlDatabase _db;
};

#endif // PLAYER
