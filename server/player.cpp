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
