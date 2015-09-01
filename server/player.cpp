#include "player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Search()
{
    QSqlQuery q;
    q.prepare("SELECT count(player_id),player_id FROM player WHERE vk_id=:id");
    q.bindValue(":id", _player_id_vk);
    q.exec();
    int count = 0;
    if (q.next())
    {
        count = q.value(0).toInt();
        _player_id = q.value(1).toInt();
    }
    if (count == 0)
    {
        QSqlQuery q1;
        q1.prepare("INSERT INTO player (vk_id) VALUES(:id)");
        q1.bindValue(":id", _player_id_vk);
        q1.exec();
        q.bindValue(":id", _player_id_vk);
        q.exec();
        if (q.next())
        {
            _player_id = q.value(1).toInt();
            qDebug() << "Added new player with id = " + _player_id;
        }
    } else
    {
        qDebug() << "player_id = " + QString(_player_id);
    }
}

void Player::newPlayer()
{
    QSqlQuery q;
    q.prepare("SELECT level FROM player WHERE player_id=:id");
    q.bindValue(":id", _player_id);
    q.exec();
    int level = 0;
    if (q.next())
    {
        level = q.value(0).toInt();
    }
    if (level == 0)
    {
        QSqlQuery q1;
        q1.prepare("INSERT INTO ship(player_id, engine, fuel_tank, yotanet, generator,"
                   " cartograph, ship_body, radar, scaner, chinilka, grab, "
                   "weapons, improvement, accelerator) VALUES(:id, 1, 1, 0, 0, 0, 0"
                   ", 0, 0, 0, 0, 0, 0, 0)");
        q1.bindValue(":id", _player_id);
        q1.exec();
        QSqlQuery q2;
        q1.prepare("INSERT INTO rating(player_id, exp, kills, death, mission, credits"
                   "fights) VALUES(:id,0,0,0,0,0,0)");
        q2.bindValue(":id", _player_id);
        q2.exec();
        QSqlQuery q3;
        q3.prepare("SELECT ship_id FROM ship WHERE player_id=:id");
        q3.bindValue(":id", _player_id);
        int ship_id = 0;
        if (q3.next())
        {
            ship_id = q.value(0).toInt();
        }
        if (ship_id == 0)
        {
            qDebug() << "Error ship_id = 0.";
            return;
        }
        QSqlQuery q4;
        q4.prepare("SELECT rating_id FROM rating WHERE player_id=:id");
        q4.bindValue(":id", _player_id);
        int rating1 = 0;
        if (q4.next())
        {
            rating1 = q.value(0).toInt();
        }
        if (rating1 == 0)
        {
            qDebug() << "Error rating1 = 0.";
            return;
        }
        QSqlQuery q5;
        q5.prepare("UPDATE player SET race=1, ship_id=:ship, spec=1, rating=:rating1,"
                   " level=1 WHERE player_id = :id");
        q5.bindValue(":ship", ship_id);
        q5.bindValue(":rating1", rating1);
        q5.bindValue(":id", _player_id);
        AddToMap();
    } else
    {
        qDebug() << "player_id = " + QString(_player_id) + "already on map";
    }
}

void Player::AddToMap()
{
    //
}
