#include "npc.h"
#include <QtSql>
#include <QDebug>

Npc::Npc(Player *player, Loader *loader)
{
    if (player == NULL)
    {
        qDebug() << "Ошибка: player == NULL.";
        exit(-1);
    }
    _player = player;
    if (loader == NULL)
    {
        qDebug() << "Ошибка: loader == NULL.";
        exit(-1);
    }
    _loader = loader;
    _found = false;
    _killed = false;
}

Npc::~Npc()
{}

bool Npc::fireToNpc(int pos)
{
    if (!_loader->_db.isOpen())
    {
        if (!_loader->_db.open())
        {
            qDebug() << "Ошибка соединения к базе данных:" << _loader->_db.lastError();
            exit(-1);
        }
    }
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
        qDebug() << "[" << _player->_player_id << "]" << "огонь по " << fireToClass << " убит.";
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
        QSqlQuery q17;
        int mission_id = 0;
        q17.prepare("SELECT params_json, id FROM mission WHERE player_id=:id");
        q17.bindValue(":id", _player->_player_id);
        q17.exec();
        while (q17.next())
        {
            QString json = q17.value(0).toString();
            mission_id = q17.value(1).toInt();
            QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
            QJsonObject obj = doc.object();
            QJsonObject::iterator it = obj.begin();
            QJsonObject obj1;
            while (it!= obj.end())
            {
                QString str = QString::fromUtf8(it.key().toStdString().c_str());
                if (str.contains("kill") && fireToClass == it.value().toString().at(0))
                {
                    //nothing to do..
                } else
                {
                    obj1.insert(it.key(), it.value());
                }
                it++;
            }
            if (obj1.count() == 1)
            {
                QString priz = obj1.value("priz").toString();
                QSqlQuery q21;
                q21.prepare("SELECT ship_id FROM ship WHERE player_id=:id");
                q21.bindValue(":id", _player->_player_id);
                q21.exec();
                int ship_bonus_id=0;
                if (q21.next())
                {
                    ship_bonus_id = q21.value(0).toInt();
                }
                if (priz == "cartograph")
                {
                    QSqlQuery q20;
                    q20.prepare("UPDATE ship SET cartograph=1 WHERE player_id=:id");
                    q20.bindValue(":id", _player->_player_id);
                    q20.exec();
                    int link = rand()%10;
                    QSqlQuery q22;
                    q22.prepare("UPDATE ship_point SET cartograph_link=:link WHERE ship_id=:id");
                    q22.bindValue(":link", link);
                    q22.bindValue(":id", ship_bonus_id);
                    q22.exec();
                    qDebug() << "[" << _player->_player_id << "] " << "Выигран бонус картограф!";
                    _player->_bonus = 1;
                } else if (priz == "droid")
                {
                    QSqlQuery q23;
                    int time = rand()%10;
                    int points = rand()%10;
                    q23.prepare("INSERT INTO droid(player_id, class, time, points) VALUES(:id, :class, :time, :points)");
                    q23.bindValue(":id", _player->_player_id);
                    q23.bindValue(":class", "A");
                    q23.bindValue(":time", QDateTime::currentDateTime().addDays(time));
                    q23.bindValue(":points", points);
                    q23.exec();
                    qDebug() << "[" << _player->_player_id << "] " << "Выигран бонус дроид!";
                    _player->_bonus = 2;
                }
                QSqlQuery q24;
                q24.prepare("DELETE FROM mission WHERE id=:id");
                q24.bindValue(":id", mission_id);
                q24.exec();
            }
            QJsonDocument doc1(obj1);
            QSqlQuery q25;
            QString str = QString::fromUtf8(doc1.toJson(QJsonDocument::Compact).toStdString().c_str());
            q25.prepare("UPDATE mission SET params_json=:str WHERE id=:id");
            q25.bindValue(":id", mission_id);
            q25.bindValue(":str", str);
            q25.exec();
        }
    } else
    {
        QSqlQuery q8;
        q8.prepare("UPDATE ship_point SET life=:life WHERE map=:map AND pos=:pos");
        q8.bindValue(":map", _player->_map);
        q8.bindValue(":pos", pos);
        q8.bindValue(":life", npc_life);
        q8.exec();
        opit = 10;
        qDebug() << "[" << _player->_player_id << "]" << "огонь по " << fireToClass << " урон = " << fire;
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
        qDebug() << "Ошибка level поврежден.";
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
        qDebug() << "Игрок с id = " << QString::number(_player->_player_id) << " Повышение уровня. "
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
