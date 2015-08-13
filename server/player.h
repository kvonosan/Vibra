#ifndef PLAYER
#define PLAYER

#include "infinite_world.h"

class Player
{
public:
    Player();
    ~Player();
private:
    InfiniteWorld *_player_map;
};

#endif // PLAYER
