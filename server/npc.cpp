#include "npc.h"
#include <QtSql>
#include <QDebug>

Npc::Npc(Player *player)
{
    if (player == NULL)
    {
        qDebug() << "Error player == NULL.";
        exit(-1);
    }
    _player = player;
    _found = false;
}

Npc::~Npc()
{}

bool Npc::fireToNpc(int pos)
{
    if (!_found)
    {
        QSqlQuery q1;
        q1.prepare("SELECT data FROM map WHERE map_id=:map_id");
        q1.bindValue(":map_id", _player->_map);
        q1.exec();
        QString data = "";
        if (q1.next())
        {
            data = q1.value(0).toString();
        }
        if (data == "")
        {
            return false;
        }
        QChar fireToClass = data[pos];
        QSqlQuery q2;
        q2.prepare("SELECT life FROM ship_body WHERE class=:fireclass");
        q2.bindValue(":fireclass", fireToClass);
        q2.exec();
        int life = 0;
        if (q2.next())
        {
            life = q2.value(0).toInt();
        }
        if (life == 0)
        {
            return false;
        }
        life = (life - 100) + rand()%100;
        q6.prepare("INSERT INTO ship_point(ship_id, life, energy, armor, fuel, life_gen, "
                   "energy_gen, armor_gen, net_speed, cartograph_link, grab_points, "
                   "radar_ships, scaner_predm, fire, fire_speed, fire_link) VALUES("
                   ":ship_id, :life, 0, 0, :fuel, 0, 0,0,0,0,0,0,0,0,0,0)");
        q6.bindValue(":ship_id", 0);
        q6.bindValue(":life", life);
        q6.bindValue(":fuel", 25);
        q6.exec();
        QSqlQuery q5;
        q5.prepare("SELECT ship_id FROM ship_point ORDER BY ship_id DESC LIMIT 1");
        q5.exec();
        _id = 0;
        if (q5.next())
        {
            _id = q5.value(0).toInt();
        }
        if (_id == 0)
        {
            return false;
        }
        _found = true;
    }
    QSqlQuery q3;
    q3.prepare("SELECT ship_id FROM ship WHERE player_id=:player_id");
    q3.bindValue(":player_id", _player->_player_id);
    q3.exec();
    int ship_id = 0;
    if (q3.next())
    {
        ship_id = q3.value(0).toInt();
    }
    if (ship_id == 0)
    {
        return false;
    }
    QSqlQuery q4;
    q4.prepare("SELECT fire FROM ship_point WHERE ship_id=:ship_id");
    q4.bindValue(":ship_id", ship_id);
    q4.exec();
    int fire = 0;
    if (q4.next())
    {
        fire = q4.value(0).toInt();
    }
    if (fire == 0)
    {
        return false;
    }
    QSqlQuery q7;
    q7.prepare("SELECT life FROM ship_point WHERE ship_id=:ship_id");
    q7.bindValue(":ship_id", ship_id);
    q7.exec();
    int npc_life = 0;
    if (q7.next())
    {
        npc_life = q7.value(0).toInt();
    }
    if (npc_life == 0)
    {
        return false;
    }
    npc_life -= fire;
    int opit = 0, kills = 0;
    if (npc_life <= 0)
    {
        QSqlQuery q9;
        q9.prepare("DELETE FROM ship_point WHERE ship_id=:ship_id");
        q9.exec();
        opit = 20;
        kills = 1;
        _killed = true;
    } else
    {
        QSqlQuery q8;
        q8.prepare("UPDATE ship_point SET life=:life WHERE ship_id=:ship_id");
        q8.bindValue(":ship_id", ship_id);
        q8.bindValue(":life", npc_life);
        q8.exec();
        opit = 10;
    }
    QSqlQuery q10;
    q10.prepare("SELECT exp, kills FROM rating WHERE player_id=:player_id");
    q10.bindValue(":player_id", _player->_player_id);
    q10.exec();
    int exp = 0, kills_base = 0;
    if (q10.next())
    {
        exp = q10.value(0).toInt();
        kills_base = q10.value(1).toInt();
    }
    QSqlQuery q11;
    q11.prepare("UPDATE rating SET exp=:exp, kills=:kills WHERE player_id=:player_id");
    q11.bindValue(":exp", exp + opit);
    q11.bindValue(":kills", kills_base + kills);
    q11.exec();
    return true;
}
