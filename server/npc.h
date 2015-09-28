#ifndef NPC
#define NPC

#include "player.h"
#include "loader.h"

class Npc
{
public:
    Npc(Player *player, Loader *loader);
    ~Npc();
    bool fireToNpc(int pos);
    bool _killed, _found, _levelup;
    int _id;
    Player *_player;
    Loader *_loader;
};

#endif // NPC
