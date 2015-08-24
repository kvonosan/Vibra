#ifndef PLAYER
#define PLAYER

#include "infinite_world.h"

class Player
{
public:
    Player();
    ~Player();
    int _player_id;
private:
    InfiniteWorld *_player_map;
};

#endif // PLAYER
