#ifndef PLAYER
#define PLAYER

#include <QtSql>

class Player
{
public:
    Player();
    ~Player();
    void Search();
    int _player_id;
    int _player_id_vk;
    int _bufferizeMap;
    int _pos, _map;
    void newPlayer();
    void AddToMap();
};

#endif // PLAYER
