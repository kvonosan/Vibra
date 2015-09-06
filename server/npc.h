#ifndef NPC
#define NPC

#include "player.h"
#include <QtNetwork>

class Npc
{
public:
    Npc(Player *player, );
    ~Npc();
    bool fireToNpc(int pos);
    bool _killed, _found;
    int _id;
    Player *_player;
    QTcpSocket *_socket;
};

#endif // NPC

