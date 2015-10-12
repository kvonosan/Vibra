#ifndef PLAYER
#define PLAYER

#include "loader.h"
class Loader;

class Player
{
public:
    Player(Loader *loader);
    ~Player();
    void Search();
    void AddToMap();
    void newPlayer();
    int _player_id;
    int _player_id_vk;
    int _pos, _map, _level, _bonus;
    Loader *_loader;
};

#endif // PLAYER
