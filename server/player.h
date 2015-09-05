#ifndef PLAYER
#define PLAYER

class Player
{
public:
    Player();
    ~Player();
    void Search();
    void AddToMap();
    void newPlayer();
    int _player_id;
    int _player_id_vk;
    int _pos, _map;
};

#endif // PLAYER
