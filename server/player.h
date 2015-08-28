#ifndef PLAYER
#define PLAYER

#include <QtSql>
#include "infinite_world.h"

class Player
{
public:
    Player();
    ~Player();
    void Search();
    int _player_id;
    int _player_id_vk;
private:
    InfiniteWorld *_player_map;
};

#endif // PLAYER
