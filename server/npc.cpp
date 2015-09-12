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
    _killed = false;
}

Npc::~Npc()
{}

bool Npc::fireToNpc(int pos)
{
    QChar fireToClass = ' ';
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
    fireToClass = data[pos];
    QSqlQuery q12;
    q12.prepare("SELECT count(map) FROM ship_point WHERE map=:map AND pos=:pos");
    q12.bindValue(":map", _player->_map);
    q12.bindValue(":pos", pos);
    q12.exec();
    _found = false;
    if (q12.next())
    {
        if (q12.value(0).toInt() == 1)
        {
            _found = true;
        }
    }
    if (!_found)
    {
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
        QSqlQuery q6;
        q6.prepare("INSERT INTO ship_point(ship_id, life, energy, armor, fuel, life_gen, "
                   "energy_gen, armor_gen, net_speed, cartograph_link, grab_points, "
                   "radar_ships, scaner_predm, fire, fire_speed, fire_link, map, pos) VALUES("
                   ":ship_id, :life, 0, 0, :fuel, 0, 0,0,0,0,0,0,0,0,0,0,:map,:pos)");
        q6.bindValue(":ship_id", 0);
        q6.bindValue(":life", life);
        q6.bindValue(":fuel", 25);
        q6.bindValue(":map", _player->_map);
        q6.bindValue(":pos", pos);
        q6.exec();
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
    q7.prepare("SELECT life FROM ship_point WHERE map=:map AND pos=:pos");
    q7.bindValue(":map", _player->_map);
    q7.bindValue(":pos", pos);
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
        q9.prepare("DELETE FROM ship_point WHERE map=:map AND pos=:pos");
        q9.bindValue(":map", _player->_map);
        q9.bindValue(":pos", pos);
        q9.exec();
        opit = 20;
        kills = 1;
        _killed = true;
        qDebug() << "[" << _player->_player_id << "]" << "fire to " << fireToClass << " killed.";
        QSqlQuery q13;
        q13.prepare("SELECT data FROM map WHERE map_id=:id");
        q13.bindValue(":id", _player->_map);
        q13.exec();
        QString data;
        if (q13.next())
        {
            data = q13.value(0).toString();
        }
        data[pos] = ' ';
        QSqlQuery q16;
        q16.prepare("UPDATE map SET data=:data WHERE map_id=:id");
        q16.bindValue(":id", _player->_map);
        q16.bindValue(":data", data);
        q16.exec();
    } else
    {
        QSqlQuery q8;
        q8.prepare("UPDATE ship_point SET life=:life WHERE map=:map AND pos=:pos");
        q8.bindValue(":map", _player->_map);
        q8.bindValue(":pos", pos);
        q8.bindValue(":life", npc_life);
        q8.exec();
        opit = 10;
        qDebug() << "[" << _player->_player_id << "]" << "fire to " << fireToClass << " damage = " << fire;
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
    exp+=opit;
    kills_base+=kills;
    QSqlQuery q11;
    q11.prepare("UPDATE rating SET exp=:exp, kills=:kills WHERE player_id=:player_id");
    q11.bindValue(":exp", exp);
    q11.bindValue(":kills", kills_base);
    q11.bindValue(":player_id", _player->_player_id);
    q11.exec();
    QSqlQuery q13;
    q13.prepare("SELECT level FROM player WHERE player_id=:id");
    q13.bindValue(":id", _player->_player_id);
    q13.exec();
    int level = 0;
    if (q13.next())
    {
        level = q13.value(0).toInt();
    }
    if (level == 0)
    {
        qDebug() << "Error level corrupted.";
        exit(-1);
    }
    _levelup = false;
    if (level >= 1 && level <=10)
    {
        if (exp >=1300000)
        {
            _levelup = true;
        }
    }
    if (level >= 11 && level <=20)
    {
        if (exp >=2100000)
        {
            _levelup = true;
        }
    }
    if (level >= 21 && level <=30)
    {
        if (exp >=3300000)
        {
            _levelup = true;
        }
    }
    if (level >= 31 && level <=40)
    {
        if (exp >=4400000)
        {
            _levelup = true;
        }
    }
    if (level >= 41 && level <=50)
    {
        if (exp >=5500000)
        {
            _levelup = true;
        }
    }
    if (level >= 51 && level <=60)
    {
        if (exp >=7700000)
        {
            _levelup = true;
        }
    }
    if (_levelup)
    {
        level++;
        qDebug() << "player with id = " << QString::number(_player->_player_id) << " levelup. level "
                 << level;
        QSqlQuery q14;
        q14.prepare("UPDATE rating SET exp=:exp WHERE player_id=:player_id");
        q14.bindValue(":player_id", _player->_player_id);
        q14.bindValue(":exp", 0);
        q14.exec();
        QSqlQuery q15;
        q15.prepare("UPDATE player SET level=:level WHERE player_id=:player_id");
        q15.bindValue(":player_id", _player->_player_id);
        q15.bindValue(":level", level);
        q15.exec();
        _player->_level = level;
    }
    return true;
}
